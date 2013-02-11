/*
 Copyright (c) 2012-2013 Dominic Clifton.  All right reserved.
 */

#ifndef OutputPin_h
#define OutputPin_h

class DigitalOutput {
public:
  virtual void enable(void) = 0;
  virtual void disable(void) = 0;
  virtual boolean isConfigured(void) = 0;

  virtual void enableInversion(void) = 0;
  virtual void disableInversion(void) = 0;
  virtual boolean isInverted(void) = 0;
};

#endif
