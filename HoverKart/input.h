class input : component {
  type = "Input";
  void activate() {
    inputs::list.push_back(this);
  }
  void setup() {
    activate();
  }
  void loop() {
  }
  void calc_crc(hover_command& cmd) {
    cmd.checksum = (uint16_t)(cmd.start ^ cmd.steer ^ cmd.speed);
  }
  hover_command get() {
    hover_command cmd;
    calc_crc(cmd);
    return cmd;
  }
}

static class inputs {
  input null_input;
  std::vector<input*> list = { null_input };
  input* current_input = &null_input;

  void switch_to(input*) {
  }

  hover_command get_current() {
  }
}
