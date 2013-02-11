/*
 Copyright (c) 2012-2013 Dominic Clifton.  All right reserved.
 */

#ifndef ArduinoDigitalOutput_h
#define ArduinoDigitalOutput_h

#include "DigitalOutput.h"

class ArduinoDigitalOutput : public DigitalOutput {
public:
  ArduinoDigitalOutput() : configured(false), inverted(false), enabled(false) {
  }

  void configure(const unsigned int hardwarePin) {
    this->hardwarePin = hardwarePin;
    pinMode(hardwarePin, OUTPUT);
    configured = true;
  }

  virtual void enable() {
    enabled = true;
    refreshHardware();
  }

  virtual void disable() {
    enabled = false;
    refreshHardware();
  }

  virtual boolean isConfigured(void) {
    return configured;
  }

  virtual void enableInversion(void) {
    inverted = true;
    refreshHardware();
  }

  virtual void disableInversion(void) {
    inverted = false;
    refreshHardware();
  }

  virtual boolean isInverted(void) {
    return inverted;
  }

private:
  void refreshHardware(void) {
    if (!configured) {
      return;
    }
    boolean outputValue = enabled;
    if (isInverted()) {
      outputValue = !outputValue;
    }
    digitalWrite(hardwarePin, outputValue ? HIGH : LOW);
  }

  unsigned int hardwarePin;
  boolean configured;
  boolean inverted;
  boolean enabled;
};

#endif
