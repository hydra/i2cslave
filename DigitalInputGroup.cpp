/*
 Copyright (c) 2012-2013 Dominic Clifton.  All right reserved.
 */

#include <Arduino.h>

#include "Config.h"
#include "DigitalInputGroup.h"

DigitalInputGroup::DigitalInputGroup(void) :
    inputsAdded(0) {
}

void DigitalInputGroup::addInput(Input *input) {
  inputs[inputsAdded++] = input;
}

Input **DigitalInputGroup::getInputs(void) {
  return inputs;
}

unsigned int DigitalInputGroup::getTotalInputs(void) {
  return inputsAdded;
}

void DigitalInputGroup::read(void) {
  for (unsigned int index = 0; index < inputsAdded; index++) {
    inputs[index]->read();
  }
}
