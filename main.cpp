#include <motor.hpp>
#include <colorsensor.hpp>
#include <touch.hpp>
/*#define _DEBUG*/
int default_speed = 140, white_threshold = 100, black_threshold = 50; // TODO: FIX NUMBERS
long double default_proportion = 1.1, default_i = 0.00055, default_d = 15;
lmotor LMOTOR('C'), RMOTOR('D');
colorsensor LCOLOR(1), RCOLOR(2);
touch LTOUCH(4), RTOUCH(3);
int main() {
  std::cout<<LCOLOR.get_rgb().r<<' '<<LCOLOR.get_rgb().g<<' '<<LCOLOR.get_rgb().b<<std::endl;
  std::cout<<RCOLOR.get_rgb().r<<' '<<RCOLOR.get_rgb().g<<' '<<RCOLOR.get_rgb().b<<std::endl;
  std::cout<<std::boolalpha<<LTOUCH.istouched() << ' '<<RTOUCH.istouched()<<std::endl;
  return 0;
}
