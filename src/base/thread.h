// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: Titto (2598772546@qq.com)

#ifndef TIT_BASE_THREAD_H
#define TIT_BASE_THREAD_H

#include <pthread.h>

#include <functional>
#include <memory>
#include <string>

#include "atomic.h"
#include "platform_thread.h"
#include "mutex.h"

namespace tit {

namespace base {

class Thread : PlatformThread::Delegate {
 public:

  explicit Thread(const std::string& name = std::string());

  Thread(const Thread&) = delete;
  Thread& operator=(const Thread&) = delete;

  ~Thread() override;

  void start();
  int join(); // return pthread_join()

  bool isRunning() const {
    MutexLockGuard guard(running_lock_);
    return running_;
  }
  pid_t tid() const { return tid_; }
  const std::string& name() const { return name_; }

  static int numCreated() { return numCreated_.get(); };

  void threadMain() override;

  pthread_t pthread() override;

  bool isJoinable() override;

 private:
  void setDefaultName();

  bool stopping_;

  mutable MutexLock running_lock_;
  bool running_ GUARDED_BY(running_lock_);

  mutable MutexLock joinable_lock_;
  bool joinable_ GUARDED_BY(joinable_lock_);

  mutable MutexLock thread_lock_;
  pthread_t pthreadId_ GUARDED_BY(thread_lock_);

  pid_t tid_;
  std::string name_;

  static AtomicInt32 numCreated_;
};

}  // namespace base

}  // namespace tit

#endif //TIT_BASE_THREAD_H
