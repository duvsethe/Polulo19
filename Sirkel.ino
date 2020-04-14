#include <Zumo32U4.h> //Including Zumo library

//Calling motors, buttonC og LCD
Zumo32U4Motors motors;
Zumo32U4ButtonB buttonB;
Zumo32U4LCD lcd;

void setup() {
  // writing to LCD
  lcd.clear();
  lcd.print("Press B");
  lcd.gotoXY(0,1);
  lcd.print("to start");
}

void loop() {
     // boolean variable buttonPress
  bool buttonPress = buttonB.getSingleDebouncedPress();
   // if - function that runs if buttonPress = true
  if(buttonPress) {
    delay (1000); // delay to give user time to remove finger from button
  motors.setSpeeds(80, 200); //Begynne svingen
  delay(3750);
  motors.setSpeeds(0, 0); // stops car entirely
 }
}
