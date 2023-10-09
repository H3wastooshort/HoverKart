//input
#include <Wire.h>
#include <WiiChuck.h>  //https://github.com/madhephaestus/WiiChuck
class chuck_input_c final : public input, public component {
  Accessory chuck;

  //TODO autocal
  uint8_t chuck_max_x = 200;
  uint8_t chuck_min_x = 55;
  uint8_t chuck_max_y = 200;
  uint8_t chuck_min_y = 55;

#define CHUCK_DEADZONE 50
  uint8_t do_deadzone(int16_t n) {
    if (abs(n) < CHUCK_DEADZONE) n = 0;
    return n;
  }

public:
  void setup() override {
    name = "Nunchuck";
    type = "Input";
    Wire.begin(I2C_PINS);
    chuck.begin();
    chuck.type = NUNCHUCK;
    if (chuck.readData()) logger.log(this, 'I', "OK");
    else logger.log(this, 'W', "Not Found");
  }

  tank_command get() override {
    vector_command cmd;
    static uint8_t retry_count = 0;
    if (chuck.readData()) {  //data ok
      retry_count = 0;
      if (chuck.getButtonZ()) {  //sw pressed
        cmd.speed = constrain(do_deadzone(map(chuck.getJoyY(),
                                              chuck_min_y, chuck_max_y,
                                              -MAX_SPEED, MAX_SPEED)),
                              -MAX_SPEED, MAX_SPEED);
        cmd.steer = constrain(do_deadzone(map(chuck.getJoyX(),
                                              chuck_min_x, chuck_max_x,
                                              -MAX_STEER, MAX_STEER)),
                              -MAX_STEER, MAX_STEER);
      } else {  //sw released
        cmd.speed = 0;
        cmd.steer = 0;
      }
    } else {  //data bad
      cmd.speed = 0;
      cmd.steer = 0;
      if (retry_count >= 200) {
        logger.log(this, 'E', "Nunchuck error! Retrying setup.");
        this->setup();  //try setting chuck up for next time
        retry_count = 0;
      }
      retry_count++;
    }


    tank_command tcmd = vec_to_tank(cmd);

    char buf[64];
    to_cstr(buf, 64, cmd);
    logger.log(this, 'D', buf);
    to_cstr(buf, 64, tcmd);  //different overload
    logger.log(this, 'D', buf);

    return tcmd;
  }
} chuck_input;
