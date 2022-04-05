// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: Titto (2598772546@qq.com)

#ifndef TIT_BASE_CURRENTTHREAD_H
#define TIT_BASE_CURRENTTHREAD_H

namespace tit {

namespace base {

namespace current_thread {

// internal
extern __thread int t_cachedTid;
extern __thread char t_tidString[32];
extern __thread int t_tidStringLength;
extern __thread const char* t_threadName;
void cacheTid();

pid_t gettid();

inline int tid()
{
  if (__builtin_expect(t_cachedTid == 0, 0))
  {
    cacheTid();
  }
  return t_cachedTid;
}

inline const char* tidString() // for logging
{
  return t_tidString;
}

inline int tidStringLength() // for logging
{
  return t_tidStringLength;
}

inline const char* name()
{
  return t_threadName;
}

bool isMainThread();


}  // namespace CurrentThread

}  // namespace base

}  // namespace tit

#endif  // TIT_BASE_CURRENTTHREAD_H
