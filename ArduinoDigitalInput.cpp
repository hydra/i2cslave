/*
 Copyright (c) 2012-2013 Dominic Clifton.  All right reserved.
 */

#include <Arduino.h>

#include "Config.h"

#include "ArduinoDigitalInput.h"

void ArduinoDigitalInput::read(void) {
  int intValue = digitalRead(hardwarePin);
  value = intValue;
}

void ArduinoDigitalInput::configure(unsigned int hardwarePin) {
  this->hardwarePin = hardwarePin;
  pinMode(hardwarePin, INPUT);
}
