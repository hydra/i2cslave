/*
 Copyright (c) 2012-2013 Dominic Clifton.  All right reserved.
 */

#ifndef ArduinoDigitalInput_h
#define ArduinoDigitalInput_h

#include "DigitalInput.h"

class ArduinoDigitalInput : public DigitalInput {
public:
  virtual void read(void);
  void configure(unsigned int hardwarePin);
private:
  unsigned int hardwarePin;
};

#endif
