/*
 Copyright (c) 2012-2013 Dominic Clifton.  All right reserved.
 */

#include <Arduino.h>

#include "Config.h"

#include "ArduinoAnalogInput.h"

void ArduinoAnalogInput::read(void) {
  int intValue = analogRead(hardwarePin);
  value = intValue;
}

void ArduinoAnalogInput::configure(unsigned int hardwarePin) {
  this->hardwarePin = hardwarePin;
  setThreshold(750);
}
