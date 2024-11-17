#include <chrono>
#include <colorsensor.hpp>
#include <iostream>
#include <thread>
int main() {
  colorsensor leftcolor(1), rightcolor(2);
  while (true) {
    rgb a = leftcolor.get_rgb(), b = rightcolor.get_rgb();
    std::cout << a.r << " " << a.g << " " << a.b << " " << b.r << " " << b.g
              << " " << b.b << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  }
  return 0;
}
