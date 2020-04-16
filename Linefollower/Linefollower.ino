#include <Zumo32U4.h> //Including Zumo library

//Calling motors, buttonA, LCD and linesensor
Zumo32U4Motors motors;
Zumo32U4ButtonA buttonA;
Zumo32U4LCD lcd;
Zumo32U4LineSensors linesensor;
Zumo32U4Buzzer buzzer;

//Creating int value for sensvaluer
unsigned int linesensorValues[5];
int tapeNum = 0;

void setup() {
  //Buzzer sound for when upload is finished
  buzzer.play(">g32>>c32");
  linesensor.initFiveSensors();
  // writing to LCD
  lcd.clear();
  lcd.print("Press A");
  lcd.gotoXY(0,1);
  lcd.print("to Calib");
  //wait for the button to be pressed
  buttonA.waitForButton();
  //waiting for the user to get away
  delay(1000);
  //clearing the LCD and telling the user that the cars is calibrating
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
  lcd.print("Press A");
  lcd.gotoXY(0,1);
  lcd.print("to start");
  buttonA.waitForButton();
  lcd.clear();

}

void loop() {
  //Reads linesensor value
   int position = linesensor.readLine(linesensorValues);
   bool myTape = false;
  
   
   if ( linesensorValues[0] >= 800 && linesensorValues[1] >= 800 && linesensorValues[2] >= 800 && linesensorValues[3] >=800 && linesensorValues[4] >=800 ){
    myTape = true;
   }
   
   //Prints linesensors value on lcd
   lcd.print(position);
   lcd.gotoXY(0,1);
   lcd.print(tapeNum);
   lcd.gotoXY(0,0);
   //Using function to choose motorpower
   direct(position, myTape, tapeNum);
   delay(50);
   }

//Function for choosing speed on motors
void direct(int x, bool myTape, bool tapeNum ){

  if ( myTape && tapeNum == 0 ){
    motors.setSpeeds(150,150);
    delay(400);
    tapeNum = 1;
  }
  else if ( myTape && tapeNum == 1 ){
    motors.setSpeeds(0,0);
    delay(200);
    motors.setSpeeds(100, -100);
    delay(1800);
    motors.setSpeeds(100,100);
    delay(200);
    tapeNum = 0;
  }
  //Turning motor to the right
  else if( x < 1500){
    motors.setSpeeds(-50,175);
  }
  //Turning motor to the left
  else if( x > 2500){
    motors.setSpeeds(175, -50);
  }
  //Straight forward
  else{
    motors.setSpeeds(150,150);
  }

}
