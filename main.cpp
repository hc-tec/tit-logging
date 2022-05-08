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
#include "base/process.h"

#include "log/logging.h"

using namespace tit::base;

void threadFunc() {
  for (int i = 0; i < 10; ++i) {
    std::cout << i << " ";
  }
  std::cout << std::endl;
}

int main(int argc, char* argv[]) {
  Init(argc, argv);
//  std::string cmd_line = CurrentCommandLine();
//
//  ArgValueParser<int> int_parser;
//  LOG(INFO) << CurrentDirectory();
//  LOG(INFO) << CurrentExecuteName();
//  int data = int_parser("handlesr");
//  LOG(INFO) << data;
//  LOG(INFO) << cmd_line;
//  LOG(INFO) << "hello world";
//
//  LOG(WARN) << "hello world" << 1.2f;
//
//
//  LOG(DEBUG) << "hello world" << 99999;
//
//  LOG(TRACE) << "hello world" << 99999;
//
//  LOG(FATAL) << "hello world" << 99999;

//  for (int i = 0; i < 100; ++i) {
//    std::cout << i << " ";
//    tit::base::SimpleThread t(threadFunc);
//    t.Start();
//    t.Join();
//  }
//  std::cout << "Hello World" << std::endl;
  if (argc > 1) {
    LOG(INFO) << "Launch success";
    return 0;
  }
  std::string argument("-handler=");
  argument.append(std::to_string(123));
  char* argument_list[] = {
      const_cast<char*>(CurrentExecuteName().data()),
      const_cast<char*>(argument.data()), NULL};
  Process* child_process = Process::LaunchProcess(argument_list);
  delete child_process;
  while (1);
}
