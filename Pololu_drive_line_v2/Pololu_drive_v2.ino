#include <Zumo32U4.h> //Including Zumo library

//Calling motors, buttonA, LCD and linesensor
Zumo32U4Motors motors;
Zumo32U4ButtonA buttonA;
Zumo32U4LCD lcd;
Zumo32U4LineSensors linesensor;
Zumo32U4Buzzer buzzer;

//Creating int value for sensvaluer
unsigned int linesensorValues[5];
int16_t lastError = 0;
int16_t  error = 0;
int16_t speedDiff = 0;
const int16_t maxSpeed = 300;

void setup() {
  buzzer.play(">g32>>c32");
  linesensor.initFiveSensors();
  // writing to LCD
  lcd.clear();
  lcd.print("Press A");
  lcd.gotoXY(0,1);
  lcd.print("to Calib");
  //wait for the button nto be pressed
  buttonA.waitForButton();
  //waiting for the user to get away
  delay(1000);
  //clearing the LCD
  lcd.clear();
  lcd.gotoXY(0,0);
  lcd.print("Cali -");
  lcd.gotoXY(0,1);
  lcd.print("brating");
  //Calibrating linesensors for 5 sek
  int i = 0;
  while(i < 100){
    linesensor.calibrate();
    motors.setSpeeds(150, -150);
    i++;
  }
  //Clears lcd and stops motor
  lcd.clear();
  motors.setSpeeds(0,0);
  //Waiting for user to press button to start driving
  buzzer.play(">g32>>c32");
  lcd.print("Press A");
  lcd.gotoXY(0,1);
  lcd.print("to start");
  buttonA.waitForButton();
  lcd.clear();

}

void loop() {
  //Reads linesensor value and "error"
   int position = linesensor.readLine(linesensorValues);
   error = position - 2000; 
   //Calculating speed difference & setting speed
   speedDiff = error / 2 + 8 *(error-lastError);
   lastError = error;
   int16_t leftSpeed = (int16_t)maxSpeed + speedDiff;
   int16_t rightSpeed = (int16_t)maxSpeed - speedDiff;
   //Contraining our motors between 0 and maxspeed
   leftSpeed = constrain(leftSpeed, 0, (int16_t)maxSpeed);
   rightSpeed = constrain(rightSpeed, 0, (int16_t)maxSpeed);
   //Motor output
   motors.setSpeeds(leftSpeed, rightSpeed);
   //Prints linesensors on lcd
   lcd.print(position);
   lcd.gotoXY(0,0);
   }
