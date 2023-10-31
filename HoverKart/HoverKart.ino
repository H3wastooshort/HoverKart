//libs (component specific ones are in respective files)
#include <vector>
#include <memory>
#include <cmath>
#include "soc/soc.h"
#include "soc/rtc_cntl_reg.h"

//components
#include "types.h"
#include "config.h"
#include "utils.h"
#include "component.h"
#include "logger.h"
#include "input.h"
#include "output.h"
#include "debug_serial.h"
#include "hover.h"
#include "lights_n_sound.h"
#include "chuck.h"
//#include "oled_disp.h"
//#include "wifi_control.h"

void setup() {
  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0);

  //only registers components
  components.activate(&debug_serial);
  components.activate(&hover);
  components.activate(&chuck_input);
  //components.activate(&oled_disp);
  //components.activate(&wifi_control);
  components.activate(&lights_n_sound);

  logger.activate(&debug_serial);
  outputs.activate(&debug_serial);
  inputs.activate(&chuck_input);
  lights_n_sound.activate(&chuck_input);
  /*outputs.activate(&oled_disp);
  inputs.activate(&wifi_control);
  outputs.activate(&wifi_control);
  logger.activate(&wifi_control);
  lights_n_sound.activate(&wifi_control);*/

  components.setup();
}


void loop() {
  components.loop();
}
