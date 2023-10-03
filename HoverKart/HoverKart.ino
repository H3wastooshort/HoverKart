//libs (component specific ones are in respective files)
#include <vector>
#include <memory>

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
#include "chuck.h"
#include "oled_disp.h"
//#include "wifi_control.h"

void setup() {
  //only registers components
  /*components.activate(&debug_serial);
  components.activate(&hover);
  components.activate(&chuck_input);
  components.activate(&oled_disp);
  components.activate(&wifi_control);*/

  logger.activate(&debug_serial);
  inputs.activate(&chuck_input);
  outputs.activate(&debug_serial);
  outputs.activate(&oled_disp);
  //outputs.activate(&wifi_control);
  //logger.activate(&wifi_control);

  debug_serial.setup();
  hover.setup();
  chuck_input.setup();
  oled_disp.setup();
  //wifi_control.setup();

  //components.setup();
}

void loop() {
  debug_serial.loop();
  chuck_input.loop();
  hover.loop();
  oled_disp.loop();
  //wifi_control.loop();

  //components.loop();
  yield();
}
