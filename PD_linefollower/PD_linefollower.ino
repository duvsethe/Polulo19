#include <Zumo32U4.h> //Including Zumo library

//Calling motors, buttonA, LCD and linesensor
Zumo32U4Motors motors;
Zumo32U4ButtonA buttonA;
Zumo32U4LCD lcd;
Zumo32U4LineSensors linesensor;
Zumo32U4Buzzer buzzer;

//Creating int value for sensvaluer
unsigned int linesensorValues[5];

const double P = 0.3;
const double D = 8;
double lastE = 0;
const unsigned char maxSpeed = 200;
int myTape = 0;


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
  //Reads linesensor value and "error"
   int position = linesensor.readLine(linesensorValues);
   int e = position - 2000; 
   //Calculating speed difference & setting speed
   int u = P * e + D *(e-lastE);
   lastE = e;
   int leftSpeed = (int)maxSpeed + u;
   int rightSpeed = (int)maxSpeed - u;
   //Contraining our motors between 0 and maxspeed
   leftSpeed = constrain(leftSpeed, 0, (int)maxSpeed);
   rightSpeed = constrain(rightSpeed, 0, (int)maxSpeed);
   //Motor output
   if ( linesensorValues[0] >= 800 && linesensorValues[1] >= 800 && linesensorValues[2] >= 800 && linesensorValues[3] >=800 && linesensorValues[4] >=800 ){
    blackTape();
    
   }
   motors.setSpeeds(leftSpeed, rightSpeed);
   //Prints linesensors on lcd
   lcd.print(myTape);
   lcd.gotoXY(0,0);
}

void blackTape(){
  if( myTape == 0 ){
    motors.setSpeeds(100,100);
    delay(2000);
    myTape = 1;
  }
  else if ( myTape == 1){
    motors.setSpeeds(0,0);
    delay(200);
    motors.setSpeeds(100, -100);
    delay(1800);
    motors.setSpeeds(100,100);
    delay(200);
    motors.setSpeeds(0,0);
    delay(20);
    motors.setSpeeds(100, -100);
    delay(900);
    motors.setSpeeds(0,0);
    delay(20);
    motors.setSpeeds(100,100);
    myTape = 0;
  }


  
}
