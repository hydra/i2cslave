/*
 Copyright (c) 2012-2013 Dominic Clifton.  All right reserved.
 */

#ifndef DigitalInputGroup_h
#define DigitalInputGroup_h

#include "Input.h"
#include "InputGroup.h"

class DigitalInputGroup: public InputGroup {
public:
  DigitalInputGroup();
  virtual void read(void);
  virtual void addInput(Input *input);
  virtual Input **getInputs(void);
  virtual unsigned int getTotalInputs(void);

private:
  unsigned int inputsAdded;
  Input *inputs[MAX_INPUTS_PER_GROUP];
};

#endif
