class output {
  //type = "Info Output";
public:
  virtual void set(const hover_feedback* fb_array) {}
};

class outputs_c final {
  std::vector<output*> list = {};

  static void check_sum(hover_feedback& fb) {  //replace checksum with true/false
    return;                             //TODO
  }

public:
  void activate(output* out) {
    list.push_back(out);
  }

  void set_all(const hover_feedback* fb_array) {
    //fb_array_all(fb_array, check_sum);
    for (const auto& o : list) {
      o->set(fb_array);
    }
  }
} outputs;
