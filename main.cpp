#include <iostream>
#include <ports.hpp>
int main () {
  std::cout << get_type_for_sensor(1) << std::endl;
  std::cout<< get_type_for_sensor(2) << std::endl;
  std::cout<< get_type_for_sensor(3) << std::endl;
  std::cout<< get_type_for_sensor(4) << std::endl;
  return 0;
}
