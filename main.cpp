// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: Titto (2598772546@qq.com)


#include <iostream>

#include <functional>

#include "base/thread.h"
#include "base/simple_thread.h"
#include "base/mutex.h"

void ThreadFunc() {
  for (int i = 0; i < 10; ++i) {
    std::cout << i << " ";
  }
  std::cout << std::endl;
}

int main() {
  tit::base::SimpleThread t(ThreadFunc);
  t.Start();
  std::cout << "Hello World" << std::endl;
}
