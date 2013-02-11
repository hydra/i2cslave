/*
 Copyright (c) 2012-2013 Dominic Clifton.  All right reserved.
 */

#ifndef DebouncedInput_h
#define DebouncedInput_h

#include "Input.h"

class DebouncedInput {
public:

  DebouncedInput() : previousTime(0), debounceDelay(50), previousValue(false), value(false) {
  }

  void setInput(Input *input) {
    this->input = input;
  }

  void setDebounceDelay(int debounceDelay) {
    this->debounceDelay = debounceDelay;
  }

  boolean getValue(void) {
    input->read();
    boolean rawValue = input->getBoolValue();

    if (rawValue != previousValue) {
      previousTime = millis();
    }

    if ((millis() - previousTime) >= debounceDelay) {
      value = rawValue;
    }

    previousValue = rawValue;

    return value;
  }

protected:
  Input *input;

  long previousTime;
  long debounceDelay;
  boolean previousValue;
  boolean value;
};

#endif
