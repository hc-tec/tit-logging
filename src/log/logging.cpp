// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: Titto (2598772546@qq.com)

#include "logging.h"

#include <sys/utsname.h>

#include <iostream>

#include "base/mutex.h"
#include "base/noncopyable.h"

namespace tit {

namespace log {

const int MIN_LOG_LEVEL = 0;

// Counts of messages sent at each level:
static int64_t num_messages_[Logging::kNumOfLevels];

const char* const_basename(const char* filepath) {
  const char* base = strrchr(filepath, '/');
  return base ? (base+1) : filepath;
}

static const char* DefaultLogDir() {
  return "";
}

static int DefaultLogLevel() {
  return Logging::LogLevel::kInfo;
}

static void GetHostName(std::string* hostname) {
  struct utsname buf;
  if (uname(&buf) < 0) {
    // ensure null termination on failure
    *buf.nodename = '\0';
  }
  *hostname = buf.nodename;
}

static MutexLock g_log_mutex;

const char* LogLevelName[Logging::kNumOfLevels] =
    {
        "TRACE ",
        "DEBUG ",
        "INFO  ",
        "WARN  ",
        "ERROR ",
        "FATAL ",
};

class Logging::LogMessageData {
 public:
  LogMessageData(const char* file,
                 int line,
                 int level)
      : level_(level),
        basename_(const_basename(file)),
        fullname_(file),
        line_(line),
        has_been_flushed_(false) {}

  LogStream& stream() {
    return stream_;
  }

  bool has_been_flushed() const {
    return has_been_flushed_;
  }

  void set_flush(bool flushed) {
    has_been_flushed_ = flushed;
  }

  int level () const {
    return level_;
  }

  const char* basename () {
    return basename_;
  }

  const char* fullname () {
    return fullname_;
  }

  int line () const {
    return line_;
  }

 private:

  DISALLOW_COPY_AND_ASSIGN(LogMessageData);

  int level_;
  const char* basename_;
  const char* fullname_;
  int line_;

  LogStream stream_;
  bool has_been_flushed_;

};

Logging::Logging(const char* file, int line) {
  Init(file, line, DefaultLogLevel());
}

Logging::Logging(const char* file, int line, int level) {
  Init(file, line, level);
}

Logging::~Logging() {
  Flush();
}

void Logging::Init(const char* file, int line, int level) {

  data_ = new LogMessageData(file, line, level);


}
LogStream& Logging::stream() { return data_->stream(); }

void Logging::Flush() {

  if (data_->has_been_flushed() || data_->level() < MIN_LOG_LEVEL) {
    return;
  }

  {
    MutexLockGuard guard(g_log_mutex);
    SendToLog();
    ++num_messages_[static_cast<int>(data_->level())];
  }

  data_->set_flush(true);
}

void Logging::SendToLog() {
  g_log_mutex.AssertLocked();

  std::cout << "Log is ready to write" << std::endl;

}

}  // namespace log

}  // namespace tit
