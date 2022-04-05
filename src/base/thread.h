// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: Titto (2598772546@qq.com)

#ifndef TIT_BASE_THREAD_H
#define TIT_BASE_THREAD_H

#include <pthread.h>
#include <functional>
#include <memory>

#include "atomic.h"

namespace tit {

namespace base {

class Thread {
 public:
  typedef std::function<void()> ThreadFunc;

  explicit Thread(ThreadFunc, const std::string& name = std::string());
  ~Thread();

  void start();
  int join(); // return pthread_join()

  bool started() const { return started_; }
  pid_t tid() const { return tid_; }
  const std::string& name() const { return name_; }

  static int numCreated() { return numCreated_.get(); };

 private:
  void setDefaultName();

  bool started_;
  bool joined_;
  pthread_t pthreadId_;
  pid_t tid_;
  ThreadFunc func_;
  std::string name_;

  static AtomicInt32 numCreated_;
};

}  // namespace base

}  // namespace tit

#endif //TIT_BASE_THREAD_H
