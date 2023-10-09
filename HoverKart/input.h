class input {
  //type = "Input";

public:
  virtual tank_command get() {
    tank_command empty;
    return empty;
  }
};

class inputs_c final {
  std::vector<input*> list = {};

  void calc_crc(hover_command& cmd) {
    cmd.start = 0xABCD;
    cmd.checksum = (uint16_t)(cmd.start ^ cmd.right ^ cmd.left);
  }

public:
  void activate(input* in) {
    list.push_back(in);
  }

  void switch_to(input*) {
  }

  const hover_command get_current() {
    hover_command sum;

    for (const auto& i : list) {
      tank_command cmd = i->get();
      sum.left += cmd.left;
      sum.right += cmd.right;
    }

    sum.left = constrain(sum.left, -MAX_SPEED, MAX_SPEED);
    sum.right = constrain(sum.right, -MAX_SPEED, MAX_SPEED);
    calc_crc(sum);

    return sum;
  }
} inputs;
