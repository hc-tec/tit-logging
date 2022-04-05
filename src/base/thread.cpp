// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: Titto (2598772546@qq.com)

#include "thread.h"

#include <iostream>
#include <utility>

namespace tit {

namespace base {


void Thread::start()
{
  {
    MutexLockGuard guard(thread_lock_);
    bool success = PlatformThread::create(this);
  }
}

Thread::Thread(const std::string& name)
    : stopping_(false),
      running_(false),
      joinable_(false),
      pthreadId_(kInvalidThreadId),
      tid_(0),
      name_(name) {
  setDefaultName();
}

Thread::~Thread() {
//  if (running_ && !joined_) {
//    pthread_detach(pthreadId_);
//  }
}

int Thread::join() {
//  joined_ = true;
  return pthread_join(pthreadId_, nullptr);
}

void Thread::setDefaultName() {
  int num = 1; // numCreated_.incrementAndGet();
  if (name_.empty())
  {
    char buf[32];
    snprintf(buf, sizeof buf, "Thread%d", num);
    name_ = buf;
  }
}
void Thread::threadMain() {
  std::cout  << "Running Thread" << std::endl;
}

pthread_t Thread::pthread() {
  MutexLockGuard guard(thread_lock_);
  return pthreadId_;
}

bool Thread::isJoinable() {
  MutexLockGuard guard(joinable_lock_);
  return joinable_;
}

}  // namespace base

}  // namespace tit
