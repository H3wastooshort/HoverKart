class component {
public:
  String name = "Unknown";
  String type = "Unknown";
  virtual void setup() {}
  virtual void loop() {}
};

class components_c final {
  std::vector<component*> list = {};

public:
  void activate(component* out) {
    list.push_back(out);
  }
  
  void setup() {
    for (const auto& c : list) c->setup();
  }

  void loop() {
    for (const auto& c : list) c->loop();
  }
} components;