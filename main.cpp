#include <iostream>
#include <motor.hpp>
#include <colorsensor.hpp>
/*#define _DEBUG*/
int default_speed = 140, white_threshold = 100, black_threshold = 50; // TODO: FIX NUMBERS
long double default_proportion = 1.1, default_i = 0.00055, default_d = 15;
lmotor LMOTOR('C'), RMOTOR('D');
  colorsensor LCOLOR(1), RCOLOR(2);
int main() {

  return 0;
}
