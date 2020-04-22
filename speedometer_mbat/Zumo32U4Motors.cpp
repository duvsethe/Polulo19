/*
  Zumo32U4Motors.cpp - Library for spoofing a Zumo32U4.
  Created by Even JC, March 2020.
*/

#include "Arduino.h"
#include "Zumo32U4Motors.h"

Zumo32U4Motors::Zumo32U4Motors()
{    

}

void Zumo32U4Motors::setSpeeds(int16_t left, int16_t right)
{ 
    leftSpeed = left;
    rightSpeed = right;
    Serial.print("Setting motor speeds to: ");
    Serial.print(left);
    Serial.print(", ");
    Serial.println(right);
}
void Zumo32U4Motors::setLeftSpeed(int16_t speed)
{ 
    leftSpeed = speed;
    Serial.print("Setting left motor speed to: ");
    Serial.println(speed);
}
void Zumo32U4Motors::setRightSpeed(int16_t speed)
{ 
    rightSpeed = speed;
    Serial.print("Setting right motor speed to: ");
    Serial.println(speed);
}
void Zumo32U4Motors::flipLeftMotor(bool flip)
{ 
    Serial.print("Setting left motor flip to: ");
    Serial.println(flip);
}
void Zumo32U4Motors::flipRightMotor(bool flip)
{ 
    Serial.print("Setting right motor flip to: ");
    Serial.println(flip);
}
