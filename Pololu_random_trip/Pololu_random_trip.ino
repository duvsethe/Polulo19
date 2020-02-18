#include <Zumo32U4.h> //Including Zumo library

//Calling motors, buttonA og LCD
Zumo32U4Motors motors;
Zumo32U4ButtonA buttonA;
Zumo32U4LCD lcd;

int randomDir = 0;
int randomDur = 0;

void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(0));
  // writing to LCD
  lcd.clear();
  lcd.print("Press A");
  lcd.gotoXY(0,1);
  lcd.print("to start");
  //wait for the button to be pressed
  buttonA.waitForButton();
  randomDir = random(1, 5);
  randomDur = random(2000);
  //waiting for the user to get away
  delay(1000);
  //clearing the LCD
  lcd.clear();
}

void loop() {
  //turning on the green led
  ledGreen(1);
  speed(randomDir);
  motors.setSpeeds(0,0);
  delay(30);
  randomDir = random(1, 5);
  randomDur = random(300,1000);
 }

 void speed(int x){
  if( x == 1){
    motors.setSpeeds(200, 200);
    delay(randomDur);
  }
  if( x == 2){
    motors.setSpeeds(-200, -200);
    delay(randomDur);    
  }
  if( x == 3){
    motors.setSpeeds(-100, 100);
    delay(795);
  }  
  if( x == 4){
    motors.setSpeeds(100, -100);
    delay(795);
  }
 }
