// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: Titto (2598772546@qq.com)

#include "simple_thread.h"

#include <utility>

namespace tit {

namespace base {

SimpleThread::SimpleThread(
    SimpleThread::ThreadFunc func,
    const std::string& name)
    : func_(std::move(func)),
      Thread(name) {}

void SimpleThread::ThreadMain() {
  func_();
}

}  // namespace base

}  // namespace tit
