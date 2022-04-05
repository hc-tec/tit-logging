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
//    pthread_t
}

Thread::Thread(Thread::ThreadFunc func, const std::string& name)
    : started_(false),
      joined_(false),
      pthreadId_(0),
      tid_(0),
      func_(std::move(func)),
      name_(name) {
  setDefaultName();
}

Thread::~Thread() {
  if (started_ && !joined_) {
    pthread_detach(pthreadId_);
  }
}

int Thread::join() {
  joined_ = true;
  return pthread_join(pthreadId_, nullptr);
}

void Thread::setDefaultName() {
  int num = numCreated_.incrementAndGet();
  if (name_.empty())
  {
    char buf[32];
    snprintf(buf, sizeof buf, "Thread%d", num);
    name_ = buf;
  }
}

}  // namespace base

}  // namespace tit
