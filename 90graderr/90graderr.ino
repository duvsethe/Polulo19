#include <Zumo32U4.h> // including zumo library

// naming variables
Zumo32U4LCD lcd;
Zumo32U4Motors motors;
Zumo32U4ButtonA buttonA;


void setup() {
  // writes to LCD
  lcd.clear();
  lcd.gotoXY(0, 0);
  lcd.print("Press A");
  lcd.gotoXY(0, 1);
  lcd.print("to start");
}

void loop() {
  // boolean variable buttonPress
  bool buttonPress = buttonA.getSingleDebouncedPress();

  // if - function that runs if buttonPress = true
  if(buttonPress) {
    delay (1000); // delay to give user time to remove finger from button
    for(int i=0;i<4;i++){
      motors.setSpeeds(200, 200); // drives forward
      delay(500);
      motors.setSpeeds(0, 0); // stops car
      delay(500);
      motors.setSpeeds(-150, 150); // turns car 90 degrees to the left
      delay(470);
      motors.setSpeeds(0,0);
      delay(500);
    }
  }
}
