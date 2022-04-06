// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: Titto (2598772546@qq.com)

#ifndef TIT_LOG_LOGGING_H
#define TIT_LOG_LOGGING_H

#include <ostream>

#include "log_stream.h"

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

  LogStream& stream();

  ~Logging();

 private:
  void Init(const char* file, int line, int level);

  void Flush();

  void SendToLog();

  LogMessageData* data_;

  Logging(const Logging&);
  void operator=(const Logging&);

};


}  // namespace log


}  // namespace tit

#define TIT_LOG_INFO tit::log::Logging( \
    __FILE__, __LINE__)

#define TIT_LOG_TRACE tit::log::Logging( \
    __FILE__, __LINE__, tit::log::Logging::kTrace)

#define TIT_LOG_DEBUG tit::log::Logging( \
    __FILE__, __LINE__, tit::log::Logging::kDebug)

#define TIT_LOG_WARN tit::log::Logging( \
    __FILE__, __LINE__, tit::log::Logging::kWarn)

#define TIT_LOG_ERROR tit::log::Logging( \
    __FILE__, __LINE__, tit::log::Logging::kError)

#define TIT_LOG_FATAL tit::log::Logging( \
    __FILE__, __LINE__, tit::log::Logging::kFatal)

#define LOG(level) TIT_LOG_ ## level.stream()

#endif  // TIT_LOG_LOGGING_H
