//levels: Error Warning Info Debug
class log_out : component {
  type = "Logging Output";
public:
  void setup() {
  }
  void print(String& str) {
  }
};

static class logger {
  log_out null_log;
  std::vector<log_out*> list = { null_log };

public:
  void activate(log_out* lo) {
    list.push_back(lo);
  }
  void setup() {
  }
  void loop() {
  }
  void log(component& comp, char level, String& msg) {
  }
};