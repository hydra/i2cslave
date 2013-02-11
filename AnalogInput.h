/*
 Copyright (c) 2012-2013 Dominic Clifton.  All right reserved.
 */

#ifndef AnalogInput_h
#define AnalogInput_h

#include "Input.h"

class AnalogInput: public Input {
public:
  virtual void read(void) = 0;
  bool getBoolValue(void) {
/*
    Serial.print("int: ");
    Serial.print(value, DEC);
    Serial.print(" bool: ");
    Serial.println((bool)value, DEC);
*/
    return (value >= threshold);
  }
  int getIntValue(void) {
    return value;
  }
  void setThreshold(int threshold) {
    this->threshold = threshold;
  }
protected:
  int value;
  int threshold;
};

#endif
