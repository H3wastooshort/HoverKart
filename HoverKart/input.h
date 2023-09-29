class input : public component {
  //type = "Input";

protected:
  void calc_crc(hover_command& cmd) {
    cmd.checksum = (uint16_t)(cmd.start ^ cmd.steer ^ cmd.speed);
  }

public:
  void setup() {
  }
  void loop() {
  }
  hover_command get() {
    hover_command cmd;
    calc_crc(cmd);
    return cmd;
  }
};

class inputs_c {
  input null_input;
  std::vector<input*> list = { null_input };
  input* current_input = &null_input;

public:
  void activate(input* in) {
    list.push_back(in);
  }

  void setup() {
    for (const auto& i : list) i->setup();
  }

  void loop() {
    for (const auto& i : list) i->loop();
  }

  void switch_to(input*) {
  }

  const hover_command get_current() {
    return current_input->get();
  }
} inputs;
