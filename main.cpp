// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: Titto (2598772546@qq.com)


#include <iostream>

#include "base/Thread.h"

int main()
{
  Thread t;
  t.start();
  std::cout << "Hello World" << std::endl;
}
