/*
 Copyright (c) 2012-2013 Dominic Clifton.  All right reserved.
 */

#ifndef InputGroup_h
#define InputGroup_h

#include "Input.h"

class InputGroup {
public:
  virtual void read(void) = 0;
  virtual void addInput(Input *input) = 0;
  virtual Input **getInputs(void) = 0;
  virtual unsigned int getTotalInputs(void) = 0;
};

#endif
