#include <Zumo32U4.h> //Including Zumo library

// naming variables
Zumo32U4Motors motors;
Zumo32U4ButtonA buttonA;
Zumo32U4ButtonB buttonB;
Zumo32U4ButtonC buttonC;
Zumo32U4LCD lcd;
Zumo32U4Buzzer buzzer;

void setup() {
  // writes to LCD
  buzzer.play(">g32>>c32");
  lcd.clear();
  lcd.gotoXY(0, 0);
  lcd.print("Press ");
  lcd.gotoXY(0, 1);
  lcd.print("to start");
}

void loop() {
  //bolean variable buttonPress 
  bool buttonPress1 = buttonA.getSingleDebouncedPress();
  bool buttonPress2 = buttonB.getSingleDebouncedPress();
  bool buttonPress3 = buttonC.getSingleDebouncedPress();

  // if - function that runs if buttonPress = true 
  if(buttonPress1) {
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
  
  if(buttonPress2) {
    delay (1000); // delay to give user time to remove finger from button
  motors.setSpeeds(80, 200); //Begynne svingen
  delay(3900);
  motors.setSpeeds(0, 0); // stops car entirely
  }
  
  if (buttonPress3) {
    delay(1000);
    motors.setSpeeds(200, 200); // drives forward for 1 second
    delay(5000);
    motors.setSpeeds(0, 0); // stops car 1 ms to give motors a break
    delay(100);
    motors.setSpeeds(150, -150);// turning the car 180 degrees
    delay(950);
    motors.setSpeeds(0, 0); //stops car for 1 ms
    delay(100);
    motors.setSpeeds(200, 200); // drives back to start
    delay(5000);
    motors.setSpeeds(0, 0); // stops car
  }
}
