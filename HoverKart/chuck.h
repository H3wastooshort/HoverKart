//input
#include <Wire.h>
#include <WiiChuck.h>  //https://github.com/madhephaestus/WiiChuck
class chuck_input_c final : public input, public component {
  Accessory chuck;

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
    if (chuck.readData()) {
      cmd.speed = do_deadzone(map(chuck.getJoyY(), 0, 255, -MAX_SPEED, MAX_SPEED));
      cmd.steer = do_deadzone(map(chuck.getJoyX(), 0, 255, -MAX_STEER, MAX_STEER));
    } else {
      static uint8_t retry_count = 0;
      if (retry_count == 0) this->setup();  //try setting chuck up for next time
      retry_count++;
    }


    tank_command tcmd = vec_to_tank(cmd);

    char buf[64];
    to_cstr(buf, 64, cmd);
    logger.log(this, 'D', buf);
    to_cstr(buf, 64, tcmd); //different overload
    logger.log(this, 'D', buf);

    return tcmd;
  }
} chuck_input;
