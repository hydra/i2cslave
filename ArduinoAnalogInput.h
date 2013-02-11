/*
 Copyright (c) 2012-2013 Dominic Clifton.  All right reserved.
 */

#ifndef ArduinoAnalogInput_h
#define ArduinoAnalogInput_h

#include "AnalogInput.h"

class ArduinoAnalogInput : public AnalogInput {
public:
  virtual void read(void);
  void configure(unsigned int hardwarePin);
private:
  unsigned int hardwarePin;
};

#endif
