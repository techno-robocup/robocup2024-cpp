#include <iostream>
#include <colorsensor.hpp>
int main () {
  colorsensor leftcolor(1), rightcolor(2);
  while(true) {

  std::cout << leftcolor.get_rgb().r << " " << leftcolor.get_rgb().g << " " << leftcolor.get_rgb().b << std::endl;
  std::cout << rightcolor.get_rgb().r << " " << rightcolor.get_rgb().g << " " << rightcolor.get_rgb().b << std::endl;
  }
  return 0;
}
