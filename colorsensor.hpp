#ifndef __EV3DEV__COLORSENSOR__H
#define __EV3DEV__COLORSENSOR__H
#include <fstream>
#include <ports.hpp>
enum colorsensor_mode {
  COLOR_REFLECT = 0,
  COLOR_AMBIENT = 1,
  COLOR_COLOR = 2,
  REF_RAW = 3,
  RGB_RAW = 4,
  COL_CAL = 5,
  UNDEFINED = 6
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
    case COLOR_AMBIENT:
      modestream << "COL-AMBIENT\n";
    case COLOR_COLOR:
      modestream << "COL-COLOR\n";
    case REF_RAW:
      modestream << "REF-RAW\n";
    case RGB_RAW:
      modestream << "RGB-RAW\n";
    case COL_CAL:
      modestream << "COL-CAL\n";
    case UNDEFINED:
      abort();
    default:
      abort();
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
    if (_prev_mode != COLOR_COLOR) {
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
