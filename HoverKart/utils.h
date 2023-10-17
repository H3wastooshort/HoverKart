#include <math.h>
#include <cmath>
/*void fb_array_all(const hover_feedback* fb_array, void (*func)(hover_feedback&)) {
  for (uint8_t n = 0; n < 3; n++) func(fb_array[n]);
}*/

void to_cstr(char* buf, size_t len, vector_command cmd) {
  snprintf(buf, len - 1, "Gas: %+06.2f, Steer: %+06.2f", cmd.speed, cmd.steer);
}
void to_cstr(char* buf, size_t len, tank_command cmd) {
  snprintf(buf, len - 1, "Left: %+06.2f, Right: %+06.2f", cmd.left, cmd.right);
}
void to_cstr(char* buf, size_t len, hover_command cmd) {
  snprintf(buf, len - 1, "Start: 0x%04X, Left: %+04d, Right: %+04d, CRC: 0x%04X", cmd.start, cmd.left, cmd.right, cmd.checksum);
}

float mapf(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

tank_command vec_to_tank(vector_command vcmd) {
  tank_command tcmd;
  if (vcmd.speed == 0 and vcmd.steer == 0) return tcmd;

  float magnitude = (std::sqrt(std::pow(vcmd.speed, 2.0) + std::pow(vcmd.steer, 2.0)));

  if (vcmd.speed < 0) {
    if (vcmd.steer > 0) {
      tcmd.left = -magnitude;
      tcmd.right = -magnitude + (magnitude * 2 * vcmd.steer);
    } else {
      tcmd.left = -magnitude - (magnitude * 2 * vcmd.steer);
      tcmd.right = -magnitude;
    }
  } else {
    if (vcmd.steer > 0) {
      tcmd.left = magnitude - (magnitude * 2 * vcmd.steer);
      tcmd.right = magnitude;
    } else {
      tcmd.left = magnitude;
      tcmd.right = magnitude + (magnitude * 2 * vcmd.steer);
    }
  }

  return tcmd;
}
