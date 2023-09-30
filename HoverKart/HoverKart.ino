//libs (component specific ones are in respective files)
#include <vector>

//components
#include "types.h"
#include "config.h"
#include "component.h"
#include "logger.h"
#include "input.h"
#include "output.h"
#include "debug_serial.h"
#include "hover.h"
#include "chuck.h"
#include "display.h"
#include "web.h"

void setup() {
  //only registers components
  logger.activate(&debug_serial);
  inputs.activate(&chuck_input);
  outputs.activate(&debug_serial);
  outputs.activate(&oled_disp);

  logger.setup();
  hover.setup();
  inputs.setup();
  outputs.setup();
}

void loop() {
  logger.loop();
  inputs.loop();
  hover.loop();
  outputs.loop();
  yield();
}
