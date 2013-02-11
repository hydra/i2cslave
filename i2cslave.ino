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

uint8_t rwRegister = 0;
uint8_t ledMask = 0;

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
  uint8_t output;

  output = output | (backButton.getValue() << 3);
  output = output | (upButton.getValue() << 2);
  output = output | (downButton.getValue() << 1);
  output = output | (selectButton.getValue() << 0);

  buffer[0] = output;
  bufferLength = 1;
}

// callback for received data
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
  while (Wire.available()>0) {
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

  Serial.print("Updating LEDs, ledMask: ");
  Serial.println(ledMask, BIN);

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

  debouceSwitches();
}

void debounceSwitches(void) {
  backButton.getValue();
  upButton.getValue();
  downButton.getValue();
  selectButton.getValue();
}
