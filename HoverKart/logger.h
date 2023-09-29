//levels: Error Warning Info Debug
class log_out : public component {
  //type = "Logging Output";
public:
  void setup() {}
  void print(String& str) {}
};

class logger_c {
  std::vector<log_out*> list = { };

public:
  void activate(log_out* lo) {
    list.push_back(lo);
  }
  void setup() {
  }
  void loop() {
  }
  void log(const component* comp, const char level, const String& msg) {
  }
} logger;