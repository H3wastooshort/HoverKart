//input
#include <Wire.h>
#include <WiiChuck.h>  //https://github.com/madhephaestus/WiiChuck
class chuck_input_c final : public input, public component {
  Accessory chuck;

#define DEADZONE 4
  uint8_t do_deadzone(uint8_t n) {
    if (n < DEADZONE + 127 and 127 - DEADZONE > n) n = 0;
    return n;
  }

public:
  void setup() {
    name = "Nunchuck";
    type = "Input";
    Wire.begin(I2C_PINS);
    chuck.begin();
    chuck.type = NUNCHUCK;
    if (chuck.readData()) logger.log(this, 'I', "OK");
    else logger.log(this, 'W', "Not Found");
  }

  hover_command get() {
    hover_command cmd;
    if (chuck.readData()) {
      cmd.speed = map(do_deadzone(chuck.getJoyY()), 0, 255, -MAX_SPEED, MAX_SPEED);
      cmd.steer = map(do_deadzone(chuck.getJoyX()), 0, 255, -MAX_STEER, MAX_STEER);
    } else {
      static uint8_t retry_count = 0;
      if (retry_count == 0) this->setup();  //try setting chuck up for next time
      retry_count++;
    }
    calc_crc(cmd);
    return cmd;
  }
} chuck_input;
