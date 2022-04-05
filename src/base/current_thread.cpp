// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: Titto (2598772546@qq.com)

#include "current_thread.h"

#include <cstdlib>
#include <type_traits>
#include <unistd.h>
#include <sys/syscall.h>
#include <linux/unistd.h>

namespace tit {

namespace base {

namespace current_thread {

__thread int t_cachedTid = 0;
__thread char t_tidString[32];
__thread int t_tidStringLength = 6;
__thread const char* t_threadName = "unknown";
static_assert(std::is_same<int, pid_t>::value, "pid_t should be int");

pid_t gettid() {
  return static_cast<pid_t>(::syscall(SYS_gettid));
}

bool isMainThread() {
  return tid() == ::getpid();
}

}  // namespace CurrentThread

}  // namespace base

}  // namespace tit