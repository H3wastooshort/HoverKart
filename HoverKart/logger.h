//levels: Error Warning Info Debug
class log_out {
  //type = "Logging Output";
public:
  virtual void log(const char* str, const char level) {}
};

class logger_c final : public component{
  std::vector<log_out*> list = {};

public:
  void activate(log_out* lo) {
    list.push_back(lo);
  }
  void log(const component* comp, const char level, const char* msg) {
    char buf[1024] = "";
    snprintf(buf, sizeof(buf) - 1, "[%d][%c][%s][%s] %s", millis(), level, comp->type.c_str(), comp->name.c_str(), msg);
    for (const auto& l : list) l->log(buf, level);
  }
} logger;