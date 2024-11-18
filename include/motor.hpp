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
  MOTOR_UNDEFINED
};
enum motor_stop_action { COAST, BRAKE, HOLD };
class lmotor {
private:
  char _portchar;
  std::string directory, commandfile, stopactionfile, duty_cyclefile,
      positionfile, ramp_downfile, ramp_upfile, speedfile, timefile;
  motor_command _prev_command;
  motor_stop_action _prev_action;
  void _SET_STOP_ACTION(motor_stop_action action) {
    if (_prev_action == action)
      return;
    std::ofstream actionstream(stopactionfile);
    switch (action) {
    case COAST:
      actionstream << "coast\n";
      break;
    case BRAKE:
      actionstream << "brake\n";
      break;
    case HOLD:
      actionstream << "hold\n";
      break;
    default:
      std::cerr << "Invalid Action" << std::endl;
      abort();
    }
    return;
  }
  void _SET_COMMAND(motor_command command) {
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
  lmotor(char portchar) : _portchar(portchar), _prev_command(MOTOR_UNDEFINED) {
    std::string mode = "lego-ev3-l-motor";
    if (get_type_for_tacho_motor(portchar) != mode) {
      std::cerr << "lmotor not connected for port " << _portchar << '\n';
      abort();
    }
    directory = get_directory_for_tacho_motor(portchar);
    commandfile = directory + "/command";
    stopactionfile = directory + "/stop_action";
    duty_cyclefile = directory + "/duty_cycle_sp";
    positionfile = directory + "/position_sp";
    ramp_downfile = directory + "/ramp_down_sp";
    ramp_upfile = directory + "/ramp_up_sp";
    speedfile = directory + "/speed_sp";
    timefile = directory + "/time_sp";
  }
  void run(int speed) {
    if (!(0 <= speed && speed <= 1050)) {
      std::cerr << "speed violation" << std::endl;
      abort();
    }
    {
      std::ofstream speedstream(speedfile);
      speedstream << speed << '\n';
    }
    _SET_COMMAND(RUN_FOREVER);
    return;
  }
  void coast() {
    _SET_STOP_ACTION(COAST);
    _SET_COMMAND(STOP);
    return;
  }
  void brake() {
    _SET_STOP_ACTION(BRAKE);
    _SET_COMMAND(STOP);
    return;
  }
  void hold() {
    _SET_STOP_ACTION(HOLD);
    _SET_COMMAND(STOP);
    return;
  }
};
#endif
