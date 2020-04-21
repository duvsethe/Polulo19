/*
  Zumo32U4Button.cpp - Library for spoofing a Zumo32U4.
  Created by Even JC, March 2020.
*/

#include "Arduino.h"
#include "Zumo32U4Button.h"

Zumo32U4Button::Zumo32U4Button(int pin)
{    
  _pin = pin;
  pinMode(_pin, INPUT);
}

static void Zumo32U4Button::waitForPress() {
  Serial.print("Waiting for press on pin ");
  Serial.println(_pin);
  while(!digitalRead(_pin));
  Serial.print("User pressed button on pin ");
  Serial.println(_pin);
}

static void Zumo32U4Button::waitForRelease() {
  Serial.print("Waiting for release on pin ");
  Serial.println(_pin);
  while(digitalRead(_pin));
  Serial.print("User released button on pin ");
  Serial.println(_pin);
}

static void Zumo32U4Button::waitForButton() {
  waitForPress();
  waitForRelease();
}

bool Zumo32U4Button::isPressed() {
  return digitalRead(_pin);
}
