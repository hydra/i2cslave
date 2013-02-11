/*
 Copyright (c) 2012-2013 Dominic Clifton.  All right reserved.
 */

#ifndef Global_h
#define Global_h

#include "DebouncedInput.h"

#ifdef USE_DIGITAL_BUTTONS
#include "ArduinoDigitalInput.h"
extern ArduinoDigitalInput backInput;
extern ArduinoDigitalInput upInput;
extern ArduinoDigitalInput downInput;
extern ArduinoDigitalInput selectInput;
#else
#include "ArduinoAnalogInput.h"
extern ArduinoAnalogInput backInput;
extern ArduinoAnalogInput upInput;
extern ArduinoAnalogInput downInput;
extern ArduinoAnalogInput selectInput;
#endif

extern DebouncedInput backButton;
extern DebouncedInput upButton;
extern DebouncedInput downButton;
extern DebouncedInput selectButton;


#include "ArduinoDigitalOutput.h"

extern ArduinoDigitalOutput statusLedOutput;
extern ArduinoDigitalOutput redLedOutput;
extern ArduinoDigitalOutput yellowLedOutput;
extern ArduinoDigitalOutput greenLedOutput;

#endif
