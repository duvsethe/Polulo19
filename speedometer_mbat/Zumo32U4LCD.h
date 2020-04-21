/*
  Zumo32U4LCD.h - Library for spoofing a Zumo32U4.
  Created by Even JC, March 2020.
*/
#ifndef Zumo32U4LCD_h
#define Zumo32U4LCD_h

#include "Arduino.h"

class Zumo32U4LCD
{
  public:
    Zumo32U4LCD();

    void gotoXY(int8_t x, int8_t y);
    void write(String string);
    void clear();
    void display();

    uint8_t xPos, yPos;

    String contents[8][2];
};

#endif
