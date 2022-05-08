//
// Created by titto on 2022/5/7.
//

#include "process.h"

namespace tit {
namespace base {

Process* g_process = nullptr;
std::string g_dir;
std::string g_execute_file;

void Init(int argc, char* argv[]) {
  g_process = new Process();
  g_process->Init(argc, argv);
  std::string execute_file(argv[0]);
  int end_idx = execute_file.size();
  int last_split_idx = execute_file.find_last_of('/');
  g_dir = execute_file.substr(0, last_split_idx);
  g_execute_file = execute_file.substr(last_split_idx+1, end_idx);
}

Process* CurrentProcess() {
  return g_process;
}

std::string CurrentCommandLine() {
  return g_process->command_line();
}
std::string CurrentDirectory() {
    return g_dir;
}
std::string CurrentExecuteName() {
    return g_execute_file;
}

std::string _ArgValueParser(const std::string& arg) {
  std::string cmd_line = CurrentCommandLine();
  int index = cmd_line.find(arg);
  if (index != -1) {
    int val_idx = index + arg.size() + 1;
    int end_idx = cmd_line.find(' ', val_idx);
    end_idx = end_idx == -1 ? cmd_line.size() : end_idx;
    return cmd_line.substr(val_idx, end_idx - val_idx);
  }
  return "";
}



}  // namespace base
}  // namespace tit