//levels: Error Warning Info Debug
class log_out : component {
  type = "Logging Output";
  void activate() {
    logger::list.push_back(this);
  }
  void setup() {
    activate();
  }
  void print(String& str) {
  }
}

static class logger {
  log_out null_log;
  std::vector<log_out*> list = { null_log };

  void setup() {
  }
  void log(component& comp, char level, String& msg) {
  }
}