#include <Zumo32U4.h> //Including Zumo library

//Calling motors, buttonA og LCD
Zumo32U4Motors motors;
Zumo32U4ButtonA buttonA;
Zumo32U4LCD lcd;
Zumo32U4LineSensors linesensor;

unsigned int linesensorValues[5];

void setup() {
  linesensor.initFiveSensors();
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
  lcd.gotoXY(0,0);
  //Calibrating linesensors for 10 sek
  int i = 0;
  while(i < 500){
    linesensor.calibrate();
    motors.setSpeeds(200, -200);
    i++;
  }
  //Clears lcd and stops motor
  lcd.clear();
  motors.setSpeeds(0,0);
}

void loop() {
  //Reads linesensor value
   int position = linesensor.readLine(linesensorValues);
   //Prints linesensors on lcd
   lcd.print(position);
   delay(1000);
   lcd.clear();
   lcd.gotoXY(0,0);

 }
