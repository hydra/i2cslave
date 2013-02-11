/*
 Copyright (c) 2012-2013 Dominic Clifton.  All right reserved.
 */

#ifndef Input_h
#define Input_h

class Input {
public:
  virtual void read(void) = 0;
  virtual bool getBoolValue(void) = 0;
  virtual int getIntValue(void) = 0;
};

#endif
