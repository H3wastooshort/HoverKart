class input : public component {
  //type = "Input";

protected:
  void calc_crc(hover_command& cmd) {
    cmd.checksum = (uint16_t)(cmd.start ^ cmd.steer ^ cmd.speed);
  }

public:
  hover_command get() {
    hover_command empty;
    return empty;
  }
};

class inputs_c final {
  std::vector<input*> list = {};

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
    hover_command sum;

    for (const auto& i : list) {
      hover_command cmd = i->get();
      sum.speed += cmd.speed;
      sum.steer += cmd.steer;
    }

    sum.speed = constrain(sum.speed, -MAX_SPEED, MAX_SPEED);
    sum.steer = constrain(sum.steer, -MAX_STEER, MAX_STEER);

    return sum;
  }
} inputs;
