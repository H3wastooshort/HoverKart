class lights_n_sound_c final : public component {
  std::vector<input*> list = {};

  uint64_t last_update_millis = 0;
public:
  void activate(input* in) {
    list.push_back(in);
  }

  void setup() override {
    pinMode(HORN_PIN, OUTPUT);
    pinMode(LIGHTS_PIN, OUTPUT);
  }

  void loop() override {
    if (millis() - last_update_millis > HOVER_CTRL_INTERVAL * 2) {
      last_update_millis = millis();

      lns_command sum;
      for (const auto& i : list) {
        lns_command cmd = i->get_lns();
        sum.horn |= cmd.horn;
        sum.lights |= cmd.lights;
      }

      digitalWrite(HORN_PIN, sum.horn);
      digitalWrite(LIGHTS_PIN, sum.lights);
    }
  }
} lights_n_sound;
