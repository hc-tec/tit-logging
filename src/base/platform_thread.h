// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: Titto (2598772546@qq.com)

#ifndef TIT_BASE_PLATFORM_THREAD_H
#define TIT_BASE_PLATFORM_THREAD_H

#include <pthread.h>

#include <atomic>


namespace tit {

namespace base {

extern __thread pid_t g_thread_id;
extern __thread const char* g_thread_name;
//extern __thread int g_name_len;
extern std::atomic<bool> g_main_thread_tid_cache_valid;
extern bool g_is_main_thread;

const pid_t kInvalidThreadId(0);

namespace internal {
void InvalidateTidCache();
}  // namespace internal

size_t GetDefaultThreadStackSize(const pthread_attr_t& attributes);

void* ThreadFunc(void* params);

// A namespace for low-level thread function.
class PlatformThread {

 public:
  // Implement this interface to run code on a background thread.
  // thread unsafe
  class Delegate {
   public:
    // ThreadMain method will be called on the newly created thread.
    virtual void threadMain() = 0;

    // get pthread_t when ready to start thread
    virtual pthread_t& pthread() = 0;

    virtual bool isJoinable() {
      return true;
    }

   protected:
    virtual ~Delegate() = default;

  };

  static pid_t currentId();

  static void sleep(int64_t sec);

  static const char* getName();

  static void setName(const char* name);

  static bool create(Delegate* delegate, size_t stack_size = 0);

  static void join(Delegate* delegate);


};


}  // namespace base

}  // namespace tit

#endif  // TIT_BASE_PLATFORM_THREAD_H
