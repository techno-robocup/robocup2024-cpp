#ifndef __EV3DEV__COLORSENSOR__H
#define __EV3DEV__COLORSENSOR__H
#include <fstream>
#include <ports.hpp>
enum colorsensor_mode {
  COLOR_REFLECT,
  COLOR_AMBIENT,
  COLOR_COLOR,
  REF_RAW,
  RGB_RAW,
  COL_CAL,
  UNDEFINED
};
struct rgb {
  int r, g, b;
  rgb operator=(const rgb &i) {
    r = i.r;
    g = i.g;
    b = i.b;
    return *this;
  }
};
class colorsensor {
private:
  int _portnum;
  std::string directory, modefile, rfile, gfile, bfile;
  colorsensor_mode _prev_mode;
  void _SET_MODE(colorsensor_mode mode) {
    std::ofstream modestream(modefile);
    switch (mode) {
    case COLOR_REFLECT:
      modestream << "COL-REFLECT\n";
      break;
    case COLOR_AMBIENT:
      modestream << "COL-AMBIENT\n";
      break;
    case COLOR_COLOR:
      modestream << "COL-COLOR\n";
      break;
    case REF_RAW:
      modestream << "REF-RAW\n";
      break;
    case RGB_RAW:
      modestream << "RGB-RAW\n";
      break;
    case COL_CAL:
      modestream << "COL-CAL\n";
      break;
    case UNDEFINED:
      std::cerr<<"UNDEFINED ABORTATION"<<std::endl;
      abort();
      break;
    default:
      abort();
      break;
    }
    return;
  }

public:
  colorsensor(int portnum) : _portnum(portnum), _prev_mode(UNDEFINED) {
    std::string mode = "lego-ev3-color";
    if (get_type_for_sensor(_portnum) != mode) {
      std::cerr << "colorsensor not connected for port " << _portnum << '\n';
      abort();
    }
    directory = get_directory_for_sensor(_portnum);
    modefile = directory + "/mode";
    rfile = directory + "/value0";
    gfile = directory + "/value1";
    bfile = directory + "/value2";
  }
  rgb get_rgb() {
    if (_prev_mode != RGB_RAW) {
      _SET_MODE(RGB_RAW);
      _prev_mode = RGB_RAW;
    }
    rgb ret;
    {
      std::ifstream redstream(rfile);
      std::string tmp;
      getline(redstream, tmp);
      ret.r = std::stoi(tmp);
    }
    {
      std::ifstream greenstream(gfile);
      std::string tmp;
      getline(greenstream, tmp);
      ret.g = std::stoi(tmp);
    }
    {
      std::ifstream bluestream(bfile);
      std::string tmp;
      getline(bluestream, tmp);
      ret.b = std::stoi(tmp);
    }
  }
};
#endif
