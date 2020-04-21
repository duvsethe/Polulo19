/*
  Zumo32U4Encoders.cpp - Library for spoofing a Zumo32U4.
  Created by Even JC, March 2020.
*/

#include "Arduino.h"
#include "Zumo32U4Encoders.h"

Zumo32U4Encoders::Zumo32U4Encoders(Zumo32U4Motors* motor)
{    
  _motor = motor;
  _leftEncoderCount = 0;
  _lastLeftCount = millis();
  _rightEncoderCount = 0;
  _lastRightCount = millis();

}

unsigned long Zumo32U4Encoders::getCountsLeft() {
  _leftEncoderCount += (float((float(millis()-_lastLeftCount))/1000))*_motor->leftSpeed;
  _lastLeftCount = millis();
  return _leftEncoderCount;
}
unsigned long Zumo32U4Encoders::getCountsRight() {
  _rightEncoderCount += (float((float(millis()-_lastRightCount))/1000))*_motor->rightSpeed;
  _lastRightCount = millis();
  return _rightEncoderCount;
}
unsigned long Zumo32U4Encoders::getCountsAndResetLeft() {
  unsigned long c = getCountsLeft();
  _leftEncoderCount = 0;
  return c;
}
unsigned long Zumo32U4Encoders::getCountsAndResetRight() {
  unsigned long c = getCountsRight();
  _rightEncoderCount = 0;  
  return c;
}
