#include <Zumo32U4.h> //Including Zumo library

//Calling motors, buttonA og LCD
Zumo32U4Motors motors;
Zumo32U4ButtonA buttonA;
Zumo32U4LCD lcd;

void setup() {
  // writing to LCD
  lcd.clear();
  lcd.print("Press A");
  lcd.gotoXY(0,1);
  lcd.print("to start");
  //wait for the button to be pressed
  buttonA.waitForButton();
  //waiting for the user to get away
  delay(1000);
  //clearing the LCD
  lcd.clear();
}

void loop() {
  //turning on the green led
  ledGreen(1);
  //making the robot drive forward
  motors.setSpeeds(200, 200);//Forward
  delay(500);
  motors.setSpeeds(0, 0);
  delay(20);
  motors.setSpeeds(-200, 200);//Left turn
  delay(302);
  motors.setSpeeds(0, 0);
  delay(20);
  motors.setSpeeds(200, 200);//Forward
  delay(500);
  motors.setSpeeds(0,0);
  delay(20);
  motors.setSpeeds(200,-200);//Right turn
  delay(302);
  motors.setSpeeds(0, 0);
  delay(20);
  motors.setSpeeds(-200, -200);//Reverse
  delay(500);
  motors.setSpeeds(0, 0);
  delay(20);
  motors.setSpeeds(-200, 200);//Left turn
  delay(302);
  motors.setSpeeds(0, 0);
  delay(20);
  motors.setSpeeds(-200,-200);//Reverse
  delay(500);
  motors.setSpeeds(0, 0);
  delay(20);
  motors.setSpeeds(200, -200);
  delay(302);
  motors.setSpeeds(0, 0);
  delay(500);

 }
