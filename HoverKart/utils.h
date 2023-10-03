/*void fb_array_all(const hover_feedback* fb_array, void (*func)(hover_feedback&)) {
  for (uint8_t n = 0; n < 3; n++) func(fb_array[n]);
}*/


void to_cstr(char* buf, size_t len, hover_command cmd) {
  snprintf(buf, len - 1, "Gas: %+04d, Steer: %+04d, CRC: 0x%04X", cmd.speed, cmd.steer, cmd.checksum);
}
