/*
  Zumo32U4Motors.h - Library for spoofing a Zumo32U4.
  Created by Even JC, March 2020.
*/
#ifndef Zumo32U4Motors_h
#define Zumo32U4Motors_h

#include "Arduino.h"

class Zumo32U4Motors
{
  public:
    Zumo32U4Motors();

    void setSpeeds(int16_t left, int16_t right);
    void setLeftSpeed(int16_t speed);
    void setRightSpeed(int16_t speed);
    static void flipLeftMotor(bool flip);
    static void flipRightMotor(bool flip);

    int leftSpeed, rightSpeed;
};

#endif
