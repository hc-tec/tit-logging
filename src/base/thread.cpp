// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: Titto (2598772546@qq.com)

#include "thread.h"

namespace tit {

namespace base {


bool Thread::start()
{

  {
      MutexLockGuard guard(running_lock_);
      running_ = true;
  }

  {
    MutexLockGuard guard(thread_lock_);
    bool success = PlatformThread::create(this);
    if (!success) {
      return false;
    }
  }

  return true;
}

Thread::Thread(const std::string& name)
    : stopping_(false),
      running_(false),
      joinable_(true),
      pthread_(kInvalidThreadId),
      tid_(0),
      name_(name) {
  setDefaultName();
}

Thread::~Thread() {
  stop();
}

void Thread::setDefaultName() {
  int num = numCreated();
  if (name_.empty())
  {
    char buf[32];
    snprintf(buf, sizeof buf, "Thread%d", num);
    name_ = buf;
  }
}

void Thread::threadMain() {

}

pthread_t& Thread::pthread() {
  MutexLockGuard guard(thread_lock_);
  return pthread_;
}

bool Thread::isJoinable() {
  MutexLockGuard guard(joinable_lock_);
  return joinable_;
}

void Thread::stop() {

  {
    MutexLockGuard guard(thread_lock_);
    if (!pthread_) return;
  }

  PlatformThread::join(this);

  {
    MutexLockGuard guard(running_lock_);
    running_ = false;
  }
}

void Thread::setJoinable(bool joinable) {
  MutexLockGuard guard(joinable_lock_);
  joinable_ = joinable;
}

}  // namespace base

}  // namespace tit
