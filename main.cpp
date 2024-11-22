#include <algorithm>
#include <cstdlib>
#include <chrono>
#include <colorsensor.hpp>
#include <motor.hpp>
#include <thread>
#include <touch.hpp>
/*#define _DEBUG*/
int default_speed = 140, white_threshold = 100,
    black_threshold = 50; // TODO: FIX NUMBERS
constexpr long double default_proportion = 1.1, default_i = 0.00055,
                      default_d = 15;
lmotor LMOTOR('C'), RMOTOR('D');
colorsensor LCOLOR(1), RCOLOR(2);
touch LTOUCH(4), RTOUCH(3);
rgb colorlnum{0, 0, 0}, colorrnum{0, 0, 0};
int colorlsum = 0, colorrsum = 0, colorlbefsum = 0, colorrbefsum = 0,
    colorlhue = 0, colorrhue = 0, isum = 0, dsum = 0;
inline void runmotor(int l, int r) {
  LMOTOR.run(l), RMOTOR.run(r);
  return;
}
int calc_hue(rgb data) {
  long double r = data.r, g = data.g, b = data.b;
  if (r == g && g == b)
    return 0;
  long double maxnum = std::max({r, g, b}), minnum = std::min({r, g, b});
  if (maxnum == b)
    return 60 * ((r - g) / (maxnum - minnum)) + 240;
  if (maxnum == r)
    return 60 * ((g - b) / (maxnum - minnum));
  if (maxnum == g)
    return 60 * ((b - r) / (maxnum - minnum)) + 120;
}
void update_num() {
  colorlnum = LCOLOR.get_rgb();
  colorrnum = RCOLOR.get_rgb();
  colorlbefsum = colorlsum;
  colorrbefsum = colorrsum;
  colorlsum = colorlnum.r + colorlnum.g + colorlnum.b;
  colorrsum = colorrnum.r + colorrnum.g + colorrnum.b;
  colorlhue = calc_hue(colorlnum), colorrhue = calc_hue(colorrnum);
  isum = colorlsum - colorrsum;
  dsum = (colorlbefsum - colorrbefsum) - (colorlsum - colorrsum);
  return;
}
bool isblack_L() {
  if (colorlsum <= black_threshold)
    return true;
  else
    return false;
}
bool isblack_R() {
  if (colorrsum <= black_threshold)
    return true;
  else
    return false;
}
bool iswhite_L() {
  if (colorlsum >= white_threshold)
    return true;
  else
    return false;
}
bool iswhite_R() {
  if (colorrsum >= white_threshold)
    return true;
  else
    return false;
}
bool isgreen_L() {
  if (std::max({colorlnum.r, colorlnum.g, colorlnum.b}) -
      std::min({colorrnum.r, colorrnum.g, colorrnum.b}))
    return false;
  if (175 <= colorlhue && colorlhue <= 185 && !isblack_L() && !iswhite_L())
    return true;
  else
    return false;
}
bool isgreen_R() {
  if (std::max({colorrnum.r, colorrnum.g, colorrnum.b}) -
          std::min({colorrnum.r, colorrnum.g, colorrnum.b}) <=
      10)
    return false;
  if (135 <= colorrhue && colorrhue <= 145 && !isblack_R() && !iswhite_R())
    return true;
  else
    return false;
}
bool isred_L() {
  if (std::max({colorlnum.r, colorlnum.g, colorlnum.b}) -
          std::min({colorlnum.r, colorlnum.g, colorlnum.b}) <=
      10)
    return false;
  if ((330 <= colorlhue || colorlhue <= 30) && !isblack_L() && !iswhite_L())
    return true;
  else
    return false;
}
bool isred_R() {
  if (std::max({colorrnum.r, colorrnum.g, colorrnum.b}) -
          std::min({colorrnum.r, colorrnum.g, colorrnum.b}) <=
      10)
    return false;
  if ((330 <= colorrhue || colorrhue <= 30) && !isblack_R() && !iswhite_R())
    return true;
  else
    return false;
}
void avoid() {
  bool lblack = true, rblack = true;
  runmotor(-200, -200);
  std::this_thread::sleep_for(std::chrono::milliseconds(300));
  runmotor(200, -200);
  std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  while (true) {
    update_num();
    if (LTOUCH.istouched())
      runmotor(200, -200);
    else
      runmotor(70, 200);
    if (isblack_L())
      lblack = true;
    if (isblack_R())
      rblack = true;
    if (lblack && rblack)
      break;
  }
  while (!isblack_R()) {
    update_num();
    runmotor(200, 200);
  }
  runmotor(200, 200);
  std::this_thread::sleep_for(std::chrono::milliseconds(300));
  update_num();
  while (!isblack_R()) {
    update_num();
    runmotor(200, -200);
  }
  update_num();
  while (isblack_R()) {
    update_num();
    runmotor(200, -200);
  }
}
void uturn() {
  runmotor(200, -200);
  std::this_thread::sleep_for(std::chrono::milliseconds(500));
  while (!isblack_R()) {
    update_num();
    runmotor(200, -200);
  }
  update_num();
  while (isblack_R()) {
    update_num();
    runmotor(200, -200);
  }
  return;
}
void exitf() {
  LMOTOR.brake();
  RMOTOR.brake();
}
int main() {
  while(true){
    update_num();
    std::cout<<colorlnum.r<<' '<<colorlnum.g<<' '<<colorlnum.b<<std::endl;
    std::cout<<colorrnum.r<<' '<<colorrnum.g<<' '<<colorrnum.b<<std::endl;
  }
  while (true) {
    update_num();
    runmotor(
        default_speed+default_proportion*(colorlsum-colorrsum)+isum*default_i+dsum*default_d,
        default_speed+default_proportion*(colorrsum-colorlsum)-isum*default_i-dsum*default_d
        );
    std::atexit(exitf);
  }
  std::atexit(exitf);
  return 0;
}
