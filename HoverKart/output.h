class output : public component {
  //type = "Info Output";

protected:
  bool check_sum(hover_feedback& fb) {
    return true; //TODO
  }
public:
  void setup() {
  }
  void loop() {
  }
  void set(const hover_feedback* fb_array) {
  }
};

class outputs_c {
  output null_output;
  std::vector<output*> list = { null_output };

public:
  void activate(output* out) {
    list.push_back(out);
  }

  void setup() {
    for (const auto& o : list) o->setup();
  }

  void loop() {
    for (const auto& o : list) o->loop();
  }

  void set_all(const hover_feedback* fb_array) {
    for (const auto& o : list) {
      o->set(fb_array);
    }
  }
} outputs;
