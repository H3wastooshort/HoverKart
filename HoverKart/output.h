class output {
  type = "Info Output" void activate() {
    outputs::list.push_back(this);
  }
  void setup() {
    activate();
  }
  void loop() {
  }
  bool check_crc(hover_feedback& fb) {
  }
  void set(hover_feedback* fb_array) {
  }
}

static class outputs {
  output null_output;
  std::vector<output*> list = { null_output };

  void set_all(hover_feedback* fb_array) {

  }
}
