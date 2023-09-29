//libs (comonent specific ones are in respective files)
#include <vector>

//components
#include "types.h"
#include "config.h"
#include "component.h"
#include "logger.h"
#include "input.h"
#include "chuck.h"
#include "output.h"
#include "hover.h"
#include "web.h"

void setup() {
  //does not run anything else
  inputs.activate(&chuck_input);

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
}
