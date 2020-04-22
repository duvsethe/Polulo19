/*
  Zumo32U4LCD.cpp - Library for spoofing a Zumo32U4.
  Created by Even JC, March 2020.
*/

#include "Arduino.h"
#include "Zumo32U4LCD.h"

Zumo32U4LCD::Zumo32U4LCD()
{    
  clear();
  xPos = 0;
  yPos = 0;
}

static void Zumo32U4LCD::gotoXY(int8_t x, int8_t y) {
  xPos = x;
  yPos = y;
	
}
static void Zumo32U4LCD::write(String string) {
  for (int i = xPos; i < string.length(); i++) {
   if (xPos + i > 7) {
      break;
    }
    contents[xPos+i][yPos] = string[i];
  }
}
static void Zumo32U4LCD::clear() {
  for (int y = 0; y < 2; y++) {
    for (int x = 0; x < 8; x++) {
      contents[x][y] = "";
    }
  } 
}
void Zumo32U4LCD::display() {
  Serial.println("\r\n##########");
  for (int y = 0; y < 2; y++) {
  Serial.print("#");
    for (int x = 0; x < 8; x++) {
      if (contents[x][y] == "") { 
        Serial.print(" ");
      } else { 
        Serial.print(contents[x][y]);
      }
    }
    Serial.println("#");
  } 
  Serial.println("##########\r\n");
}
