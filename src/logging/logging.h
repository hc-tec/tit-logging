// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: Titto (2598772546@qq.com)

#ifndef TIT_LOGGING_LOGGING_H
#define TIT_LOGGING_LOGGING_H

namespace tit {

class Logging {
 public:
  enum LogLevel {
    TRACE,
    DEBUG,
    INFO,
    WARN,
    ERROR,
    FATAL,
    NUM_LEVELs,
  };
};

}  // namespace tit

#endif  // TIT_LOGGING_LOGGING_H
