#ifndef __EV3DEV__TOUCH__H
#define __EV3DEV__TOUCH__H
#include <fstream>
#include <ports.hpp>
#include <string>
class touch {
private:
  int _portnum;
  std::string directory, valuefile;

public:
  touch(int portnum) : _portnum(portnum) {
    std::string target = "lego-ev3-touch";
    if (get_type_for_sensor(_portnum) != target) {
      std::cerr << "touch sensor not connected for port " << _portnum
                << std::endl;
      abort();
    }
    directory = get_directory_for_sensor(_portnum);
    valuefile = directory + "/value0";
  }
  bool istouched() {
    std::ifstream valuestream(valuefile);
    std::string value;
    getline(valuestream, value);
    if (value == "1")
      return true;
    return false;
  }
};
#endif
