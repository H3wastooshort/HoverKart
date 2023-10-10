class input {
  //type = "Input";

public:
  virtual tank_command get() {
    tank_command empty;
    return empty;
  }

  virtual lns_command get_lns() {
    lns_command empty;
    return empty;
  }
};

class inputs_c final : public component {
  std::vector<input*> list = {};

public:
  void activate(input* in) {
    list.push_back(in);
  }

  void switch_to(input*) {
  }

  const tank_command get_current() {
    tank_command sum;

    for (const auto& i : list) {
      tank_command cmd = i->get();
      sum.left += cmd.left;
      sum.right += cmd.right;
    }

    sum.left = constrain(sum.left, -MAX_SPEED, MAX_SPEED);
    sum.right = constrain(sum.right, -MAX_SPEED, MAX_SPEED);

    char buf[64];
    to_cstr(buf, 64, sum);
    logger.log(this, 'D', buf);

    return sum;
  }
} inputs;
