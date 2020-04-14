#include <Zumo32U4.h> //Including Zumo library

// naming variables
Zumo32U4Motors motors;
Zumo32U4ButtonC buttonC;
Zumo32U4LCD lcd;
Zumo32U4Buzzer buzzer;

void setup() {
  // writes to LCD
  buzzer.play(">g32>>c32");
  lcd.clear();
  lcd.gotoXY(0, 0);
  lcd.print("Press C");
  lcd.gotoXY(0, 1);
  lcd.print("to start");
}

void loop() {
  //bolean variable buttonPress 
  bool buttonPress = buttonC.getSingleDebouncedPress();

  // if - function that runs if buttonPress = true 
  if (buttonPress) {
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
