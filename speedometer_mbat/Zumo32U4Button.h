  /*
  Zumo32U4Button.h - Library for spoofing a Zumo32U4.
  Created by Even JC, March 2020.
*/
#ifndef Zumo32U4Button_h
#define Zumo32U4Button_h

#include "Arduino.h"

class Zumo32U4Button
{
  public:
    Zumo32U4Button(int pin);

    bool isPressed();
    void waitForPress();
    void waitForRelease();
    void waitForButton();
    
  private:
    int _pin;
};

#endif
