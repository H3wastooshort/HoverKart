class output {
  type = "Info Output";

protected:
  bool check_crc(hover_feedback& fb) {
  }
public:
  void setup() {
  }
  void loop() {
  }
  void set(hover_feedback* fb_array) {
  }
};

static class outputs {
  output null_output;
  std::vector<output*> list = { null_output };

public:
  void activate(output* out) {
    list.push_back(out);
  }

  void setup() {
    for (const auto& o : list) o.setup();
  }

  void loop() {
    for (const auto& o : list) o.loop();
  }

  void set_all(hover_feedback* fb_array) for (const auto& o : list) {
    o.set(fb_array);
  }
};
