#include <Arduino.h>

#include "VortexGloveset.h"

VortexGloveset gloveset;

void setup()
{
  if (!gloveset.init()) {
    // uhoh
  }
}

void loop()
{
  gloveset.tick();
}
