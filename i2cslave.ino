/*
 Copyright (c) 2012-2013 Dominic Clifton.  All right reserved.
 */

#include <Arduino.h>
#include <Wire.h>

#include "ScheduledAction.h"

#include "Config.h"

#include "Global.h"

const unsigned int backPin = A3;
const unsigned int upPin = A2;
const unsigned int downPin = A1;
const unsigned int selectPin = A0;

const unsigned int statusLedPin = 13;
const unsigned int redLedPin = 5;
const unsigned int yellowLedPin = 6;
const unsigned int greenLedPin = 7;

ScheduledAction statusLedAction;
bool statusLedState = false;

volatile uint8_t rwRegister = 0;
volatile uint8_t ledMask = 0;
volatile uint8_t buttonMask = 0;

#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif

#define DEFAULT_LED_MASK 0x07

enum Registers {
  REG_READ_STATUS,
  REG_READ_LEDS,
  REG_READ_BUTTONS,
  REG_WRITE_LEDS,
};

// callback for sending data
void sendData(void) {

  uint8_t buffer[1];
  uint8_t bufferLength = 0;

  switch(rwRegister) {
    case REG_READ_STATUS:
      updateBufferWithStatus(buffer, bufferLength);
    break;
    case REG_READ_LEDS:
      updateBufferWithLedStatus(buffer, bufferLength);
    break;
    case REG_READ_BUTTONS:
      updateBufferWithButtonState(buffer, bufferLength);
    break;
  }

  if (!bufferLength) {
    return;
  }

  Wire.write(buffer, bufferLength);
}

void updateBufferWithStatus(uint8_t *buffer, uint8_t& bufferLength) {
  buffer[0] = 1;
  bufferLength = 1;
}

void updateBufferWithLedStatus(uint8_t *buffer, uint8_t& bufferLength) {
  buffer[0] = ledMask;
  bufferLength = 1;
}

void updateBufferWithButtonState(uint8_t *buffer, uint8_t& bufferLength) {
  buffer[0] = buttonMask;
  bufferLength = 1;
}

void receiveData(int byteCount) {

  int availableCount = Wire.available();

  if (!(byteCount && availableCount)) {
    return;
  }

  rwRegister = Wire.read();

  switch(rwRegister) {
    case REG_WRITE_LEDS:
      getIncomingDataAndUpdateLeds();
    break;
  }

  flushReceiveBuffer();
}

void flushReceiveBuffer(void) {
  while (Wire.available() > 0) {
    Wire.read();
  }
}

void getIncomingDataAndUpdateLeds(void) {
  int availableCount = Wire.available();

  if (availableCount != 1) {
    return;
  }

  uint8_t ledMask = Wire.read();

  setLeds(ledMask);
}

void setLeds(uint8_t newLedMask) {

  ledMask = newLedMask;

  if (ledMask & (1 << 2)) {
    redLedOutput.enable();
  } else {
    redLedOutput.disable();
  }

  if (ledMask & (1 << 1)) {
    yellowLedOutput.enable();
  } else {
    yellowLedOutput.disable();
  }

  if (ledMask & (1 << 0)) {
    greenLedOutput.enable();
  } else {
    greenLedOutput.disable();
  }

}

void setup() {
  Serial.begin(57600);
  Serial.println("\nI2C Slave");

  statusLedOutput.configure(statusLedPin);
  redLedOutput.configure(redLedPin);
  yellowLedOutput.configure(yellowLedPin);
  greenLedOutput.configure(greenLedPin);

  backInput.configure(backPin);
  backButton.setInput(&backInput);
  upInput.configure(upPin);
  upButton.setInput(&upInput);
  downInput.configure(downPin);
  downButton.setInput(&downInput);
  selectInput.configure(selectPin);
  selectButton.setInput(&selectInput);

  // define callbacks for i2c communication
  Wire.onRequest(sendData);
  Wire.onReceive(receiveData);

  // initialize i2c as slave
  Wire.begin(SLAVE_ADDRESS);

#if defined(__AVR_ATmega168__) || defined(__AVR_ATmega8__) || defined(__AVR_ATmega328P__)
   // deactivate internal pull-ups for twi
   // as per note from atmega8 manual pg167
   cbi(PORTC, 4);
   cbi(PORTC, 5);
 #else
   // deactivate internal pull-ups for twi
   // as per note from atmega128 manual pg204
   cbi(PORTD, 0);
   cbi(PORTD, 1);
 #endif

  statusLedAction.setDelayMillis(500L);
  statusLedAction.reset();

  setLeds(DEFAULT_LED_MASK);

  Serial.print("Waiting for data, I2C Address: 0x");
  Serial.println(SLAVE_ADDRESS, HEX);

}

void loop() {
  if (statusLedAction.isActionDue()) {
    statusLedState = !statusLedState;
    if (statusLedState) {
      statusLedOutput.enable();
    } else {
      statusLedOutput.disable();
    }
  }

  readButtons();
}

void updateButtonMask(DebouncedInput &input, uint8_t bit) {
  if (input.getValue()) {
    buttonMask |= (1 << bit);
  } else {
    buttonMask &= (uint8_t)~(1 << bit);
  }
}

void readButtons(void) {
  updateButtonMask(backButton, 3);
  updateButtonMask(upButton, 2);
  updateButtonMask(downButton, 1);
  updateButtonMask(selectButton, 0);
}
