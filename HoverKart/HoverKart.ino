//libs (comonent specific ones are in respective files)
#include <memory>
#include <vector>

//components
#include "config.h"
#include "component.h"
#include "logger.h"
#include "hover.h"
#include "input.h"
#include "output.h"
#include "chuck.h"
#include "web.h"

void setup() {
  logger::loop();
  hover::setup();
  inputs::setup();
  outputs::setup();
}

void loop() {
  logger::loop();
  inputs::loop();
  hover::loop();
  outputs::loop();
}
