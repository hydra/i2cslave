/*
 Copyright (c) 2012-2013 Dominic Clifton.  All right reserved.
 */

#include <Arduino.h>

#include "Config.h"

#include "Global.h"

#ifdef USE_DIGITAL_BUTTONS
ArduinoDigitalInput backInput;
ArduinoDigitalInput upInput;
ArduinoDigitalInput downInput;
ArduinoDigitalInput selectInput;
#else
ArduinoAnalogInput backInput;
ArduinoAnalogInput upInput;
ArduinoAnalogInput downInput;
ArduinoAnalogInput selectInput;
#endif

DebouncedInput backButton;
DebouncedInput upButton;
DebouncedInput downButton;
DebouncedInput selectButton;

ArduinoDigitalOutput statusLedOutput;
ArduinoDigitalOutput redLedOutput;
ArduinoDigitalOutput yellowLedOutput;
ArduinoDigitalOutput greenLedOutput;
