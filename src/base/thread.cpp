// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: Titto (2598772546@qq.com)

#include "thread.h"

namespace tit {

namespace base {


bool Thread::Start()
{

  {
      MutexLockGuard guard(running_lock_);
      running_ = true;
  }

  {
    MutexLockGuard guard(thread_lock_);
    bool success = PlatformThread::Create(this);
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
  SetDefaultName();
}

Thread::~Thread() {
  Stop();
}

void Thread::SetDefaultName() {
  int num = NumCreated();
  if (name_.empty())
  {
    char buf[32];
    snprintf(buf, sizeof buf, "Thread%d", num);
    name_ = buf;
  }
}

void Thread::ThreadMain() {

}

pthread_t& Thread::pthread() {
  MutexLockGuard guard(thread_lock_);
  return pthread_;
}

bool Thread::IsJoinable() {
  MutexLockGuard guard(joinable_lock_);
  return joinable_;
}

void Thread::Stop() {

  {
    MutexLockGuard guard(thread_lock_);
    if (!pthread_) return;
  }

  PlatformThread::Join(this);

  {
    MutexLockGuard guard(running_lock_);
    running_ = false;
  }
}

void Thread::set_joinable(bool joinable) {
  MutexLockGuard guard(joinable_lock_);
  joinable_ = joinable;
}

}  // namespace base

}  // namespace tit
