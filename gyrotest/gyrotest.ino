// Example on how to read from the gyrometer
// built into the Pololu Zumo 32U4 Arduino-based robot.

#include <Zumo32U4.h>
#include "TurnSensor.h"

L3G gyro;
Zumo32U4LCD lcd;
Zumo32U4Motors motors;
Zumo32U4ButtonA buttonA;
Zumo32U4ButtonB buttonB;


int stepNum = 0;
bool drive = false;


// --- Helper functions
int32_t getAngle() {
  // turnAngle is a variable defined in TurnSensor.cpp
  // This fancy math converts the number into degrees turned since the
  // last sensor reset.
  return (((int32_t)turnAngle >> 16) * 360) >> 16;
}

int32_t angle = getAngle();


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
  angle = getAngle();
  if ( buttonA.isPressed()){
    drive = true;
    stepNum = 0;
  }
  if ( buttonB.isPressed()){
    drive = false;
  }

  if ( drive){
    coneDrive();
  }
  // Update the display
  lcd.gotoXY(0, 0);
  lcd.print(angle);
  lcd.print(" ");
  
  
}



void coneDrive (){
  
  while ( stepNum == 0){
    motors.setSpeeds(-100, 100);
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

  if (stepNum == 1){
    motors.setSpeeds(200, 100);
    if ( angle <= -55){
      stepNum = 2;
    }
  }
  if (stepNum == 2){
    motors.setSpeeds(100,200);
    if (angle >= 55){
      stepNum = 1;
    }
  }
}
