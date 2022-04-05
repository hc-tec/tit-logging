// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: Titto (2598772546@qq.com)

#include "platform_thread.h"

#include <iostream>
#include <cerrno>
#include <linux/unistd.h>
#include <unistd.h>

#include <memory>
#include <cstring>

#include "timestamp.h"

namespace tit {

namespace base {

namespace {

struct ThreadParams {
  ThreadParams()
      : delegate(nullptr),
        joinable(false) {}

  PlatformThread::Delegate* delegate;
  bool joinable;
};  // namespace

}

__thread pid_t g_thread_id = -1;
__thread const char* g_thread_name = "tit-default-name";
std::atomic<bool> g_main_thread_tid_cache_valid = false;
bool g_is_main_thread = true;


namespace internal {
void InvalidateTidCache() {
  g_main_thread_tid_cache_valid.store(false, std::memory_order_relaxed);
}
}  // namespace internal

class InitAtFork {
 public:
  InitAtFork() {
    pthread_atfork(nullptr, nullptr, internal::InvalidateTidCache);
  }
};

size_t GetDefaultThreadStackSize(const pthread_attr_t& attributes) {
  // ThreadSanitizer bloats the stack heavily. Evidence has been that the
  // default stack size isn't enough for some browser tests.
  return 2 * (1 << 23);  // 2 times 8192K (the default stack size on Linux).
}

void* ThreadFunc(void* params) {
  PlatformThread::Delegate* delegate = nullptr;

  {
    std::unique_ptr<ThreadParams> thread_params(
        static_cast<ThreadParams*>(params));
    delegate = thread_params->delegate;
  }

  delegate->threadMain();

  return nullptr;
}

pid_t PlatformThread::currentId() {
  static InitAtFork init_at_fork;
  if (g_thread_id == -1 ||
      (g_is_main_thread &&
       !g_main_thread_tid_cache_valid.load(std::memory_order_relaxed))) {
    // Update the cached tid.
    g_thread_id = syscall(__NR_gettid);
    // If this is the main thread, we can mark the tid_cache as valid.
    // Otherwise, stop the current thread from always entering this slow path.
    if (g_thread_id == getpid()) {
      g_main_thread_tid_cache_valid.store(true, std::memory_order_relaxed);
    } else {
      g_is_main_thread = false;
    }
  } else {

  }

  return g_thread_id;
}

void PlatformThread::sleep(int64_t usec) {

  struct timespec ts = { 0, 0 };
  ts.tv_sec = static_cast<time_t>(usec / Timestamp::kMicroSecondsPerSecond);
  ts.tv_nsec = static_cast<long>(usec % Timestamp::kMicroSecondsPerSecond * 1000);
  ::nanosleep(&ts, NULL);

}

const char* PlatformThread::getName() { return g_thread_name; }

void PlatformThread::setName(const char* name) {
  g_thread_name = name;
}
bool PlatformThread::create(PlatformThread::Delegate* delegate,
                            size_t stack_size) {
  pthread_attr_t attributes;
  memset(&attributes, 0, sizeof(attributes));
  pthread_attr_init(&attributes);

  bool joinable = delegate->isJoinable();

  if (!joinable) {
    pthread_attr_setdetachstate(&attributes, PTHREAD_CREATE_DETACHED);
  }

  if (stack_size == 0)
    stack_size = GetDefaultThreadStackSize(attributes);

  if (stack_size > 0)
    pthread_attr_setstacksize(&attributes, stack_size);

  std::unique_ptr<ThreadParams> params(new ThreadParams);
  params->delegate = delegate;
  params->joinable = joinable;

  pthread_t& handle = delegate->pthread();
  int err = pthread_create(&handle, &attributes, &ThreadFunc, params.get());
  bool success = !err;
  if (success) {
    // ThreadParams should be deleted on the created thread after used.
    std::ignore = params.release();
  } else {
    // Value of |handle| is undefined if pthread_create fails.
    handle = 0;
    errno = err;
//    PLOG(ERROR) << "pthread_create";
  }

  pthread_attr_destroy(&attributes);

  return success;
}

void PlatformThread::join(PlatformThread::Delegate* delegate) {
  pthread_join(delegate->pthread(), nullptr);
}


}  // namespace base

}  // namespace tit

