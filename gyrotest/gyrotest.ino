// Example on how to read from the gyrometer
// built into the Pololu Zumo 32U4 Arduino-based robot.

#include <Zumo32U4.h>
#include "TurnSensor.h"

L3G gyro;
Zumo32U4LCD lcd;
Zumo32U4Motors motors;
Zumo32U4ButtonA buttonA;

int stepNum = 0;

// --- Helper functions
int32_t getAngle() {
  // turnAngle is a variable defined in TurnSensor.cpp
  // This fancy math converts the number into degrees turned since the
  // last sensor reset.
  return (((int32_t)turnAngle >> 16) * 360) >> 16;
}

// --- Setup Method
void setup() {
  turnSensorSetup();
  delay(500);
  turnSensorReset();
  lcd.clear();
}

// --- Main program loop
void loop() {
  
  // Read the sensors
  turnSensorUpdate();
  int32_t angle = getAngle();
  
  // Update the display
  lcd.gotoXY(0, 0);
  lcd.print(angle);
  lcd.print(" ");

  if ( buttonA.isPressed()){
   while ( stepNum == 0){
    motors.setSpeeds(50, -50);
    turnSensorUpdate();
    angle = getAngle();
    lcd.gotoXY(0, 0);
    lcd.print(angle);
    lcd.print(" ");    
    if (angle >= 55){
      motors.setSpeeds(0,0);
      stepNum = 1;
      break;
    }
   }
   while ( stepNum == 1){
    motors.setSpeeds(100, 150);
    turnSensorUpdate();
    angle = getAngle();
    lcd.gotoXY(0, 0);
    lcd.print(angle);
    lcd.print(" ");
    if (angle <= -55){
      stepNum = 2;
      break;
      }
   }
   while ( stepNum == 2){
    motors.setSpeeds(150, 100);
    turnSensorUpdate();
    angle = getAngle();
    lcd.gotoXY(0, 0);
    lcd.print(angle);
    lcd.print(" ");
    if (angle >= 55){
      stepNum = 1;
      break;
    }
   }
  }
}
 
