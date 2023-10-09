/*void fb_array_all(const hover_feedback* fb_array, void (*func)(hover_feedback&)) {
  for (uint8_t n = 0; n < 3; n++) func(fb_array[n]);
}*/

void to_cstr(char* buf, size_t len, vector_command cmd) {
  snprintf(buf, len - 1, "Gas: %+04d, Steer: %+04d", cmd.speed, cmd.steer);
}
void to_cstr(char* buf, size_t len, tank_command cmd) {
  snprintf(buf, len - 1, "Left: %+04d, Right: %+04d", cmd.left, cmd.right);
}
void to_cstr(char* buf, size_t len, hover_command cmd) {
  snprintf(buf, len - 1, "Left: %+04d, Right: %+04d, CRC: 0x%04X", cmd.left, cmd.right, cmd.checksum);
}

tank_command vec_to_tank (vector_command vcmd) {
  tank_command tcmd;
  //TODO
  return tcmd;
}
