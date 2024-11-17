#ifndef __EV3DEV__MOTOR__H
#define __EV3DEV__MOTOR__H
#include <fstream>
#include <ports.hpp>
enum motor_command {
  RUN_FOREVER,
  RUN_TO_ABS_POS,
  RUN_TO_REL_POS,
  RUN_TIMED,
  RUN_DIRECT,
  STOP,
  RESET,
  UNDEFINED
};
class lmotor {
private:
  char _portchar;
  std::string directory, commandfile, duty_cyclefile, positionfile,
      ramp_downfile, ramp_upfile, speedfile, timefile;
  motor_command _prev_command;
  void _SET_MODE(motor_command command) {
    if (_prev_command == command)
      return;
    std::ofstream commandstream(commandfile);
    switch (command) {
    case RUN_FOREVER:
      commandstream << "run-forever\n";
      break;
    case RUN_TO_ABS_POS:
      commandstream << "run-to-abs-pos\n";
      break;
    case RUN_TO_REL_POS:
      commandstream << "run-to-rel-pos\n";
      break;
    case RUN_TIMED:
      commandstream << "run-timed\n";
      break;
    case RUN_DIRECT:
      commandstream << "run-direct\n";
      break;
    case STOP:
      commandstream << "stop\n";
      break;
    case RESET:
      commandstream << "reset\n";
      break;
    default:
      abort();
      break;
    }
    return;
  }

public:
  lmotor(char portchar) : _portchar(portchar), _prev_command(UNDEFINED) {
    std::string mode = "lego-ev3-l-motor";
    if (get_type_for_tacho_motor(portchar) != mode) {
      std::cerr << "lmotor not connected for port " << _portchar << '\n';
      abort();
    }
    directory = get_type_for_tacho_motor(portchar);
    commandfile = directory + "/command";
  }
  void run(int speed) {
    if (!(0 <= speed && speed <= 1050)) {
      std::cerr << "spped violation" << std::endl;
      abort();
    }
  }
};
class mmotor {};
#endif
