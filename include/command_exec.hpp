#ifndef __EV3DEV__COMMAND_EXEC_HPP
#define __EV3DEV_COMMAND_EXEC_HPP

#include <stdexcept>
#include <string>

std::string exec_command(std::string &command) {
  std::string result = "";
  char buffer[128];
  FILE *pipe = popen(command.c_str(), "r");
  if (!pipe) {
    throw std::runtime_error("popen failed");
  }
  while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
    result += buffer;
  }
  int returncode = pclose(pipe);
  return result;
}
#endif
