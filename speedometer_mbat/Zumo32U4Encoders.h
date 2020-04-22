/*
  Zumo32U4Encoders.h - Library for spoofing a Zumo32U4.
  Created by Even JC, March 2020.
*/
#ifndef Zumo32U4Encoders_h
#define Zumo32U4Encoders_h

#include "Arduino.h"
#include "Zumo32U4Motors.h"

class Zumo32U4Encoders
{
  public:
    Zumo32U4Encoders(Zumo32U4Motors* motor);

    unsigned long getCountsLeft();
    unsigned long getCountsRight();
    unsigned long getCountsAndResetLeft();
    unsigned long getCountsAndResetRight();

  private:
    Zumo32U4Motors* _motor;
    
    unsigned long _lastLeftCount;
    unsigned long _lastRightCount;
    unsigned long _leftEncoderCount;
    unsigned long _rightEncoderCount;

};

#endif
