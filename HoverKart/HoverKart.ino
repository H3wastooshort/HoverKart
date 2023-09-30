//libs (comonent specific ones are in respective files)
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
#include "web.h"

void setup() {
  //only registers components
  inputs.activate(&chuck_input);
  logger.activate(&dserial_log);
  outputs.activate(&dserial_out);

  debug_serial_setup();
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
