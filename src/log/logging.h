// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: Titto (2598772546@qq.com)

#ifndef TIT_LOGGING_LOGGING_H
#define TIT_LOGGING_LOGGING_H

#include <ostream>

namespace tit {

namespace log {


class Logging {
 public:

  enum LogLevel {
    kTrace,
    kDebug,
    kInfo,
    kWarn,
    kError,
    kFatal,
    kNumOfLevels,
  };

  Logging(const char* file, int line);

  Logging(const char* file, int line, int level);

  class LogMessageData;

  class LogStream : public std::ostream {
   public:
    LogStream();
  };

 private:

  // Counts of messages sent at each level:
  static int64_t num_messages_[kNumOfLevels];

  LogMessageData* data_;

  Logging(const Logging&);
  void operator=(const Logging&);

};


}  // namespace log


}  // namespace tit

#endif  // TIT_LOGGING_LOGGING_H
