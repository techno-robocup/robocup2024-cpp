#include <chrono>
#include <colorsensor.hpp>
#include <motor.hpp>
#include <iostream>
#include <thread>
int main() {
  colorsensor leftcolor(1), rightcolor(2);
  lmotor leftmotor('C'), rightmotor('D');
  for(int i=0; i < 1000; i++)leftmotor.run(i);
  leftmotor.brake();
  for(int i=0; i < 1000; i++)rightmotor.run(i);
  rightmotor.brake();
  return 0;
}
