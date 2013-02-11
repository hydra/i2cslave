/*
 Copyright (c) 2012-2013 Dominic Clifton.  All right reserved.
 */

#ifndef DigitalInput_h
#define DigitalInput_h

#include "Input.h"

class DigitalInput: public Input {
public:
  virtual void read(void) = 0;
  bool getBoolValue(void) {
    return value;
  }
  int getIntValue(void) {
    return value;
  }
protected:
  bool value;
};

#endif
