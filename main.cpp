// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: Titto (2598772546@qq.com)


#include <iostream>

#include <functional>
#include <vector>

#include "base/thread.h"
#include "base/simple_thread.h"
#include "base/mutex.h"

#include "log/logging.h"


void threadFunc() {
  for (int i = 0; i < 10; ++i) {
    std::cout << i << " ";
  }
  std::cout << std::endl;
}

int main() {

  LOG(INFO) << "hello world" << '\n';

//  for (int i = 0; i < 100; ++i) {
//    std::cout << i << " ";
//    tit::base::SimpleThread t(threadFunc);
//    t.Start();
//    t.Join();
//  }
//  std::cout << "Hello World" << std::endl;
}
