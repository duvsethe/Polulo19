#include <Zumo32U4.h> //Including Zumo library
#include<math.h>  //Including math library

//Calling motors, buttonA, LCD and linesensor
Zumo32U4Motors motors;
Zumo32U4ButtonA buttonA;
Zumo32U4LCD lcd;
Zumo32U4LineSensors linesensor;
Zumo32U4Buzzer buzzer;
Zumo32U4Encoders encoder;

//Creating variables
float count;
float meters = 0;  
float batteryLife = 52.0;
bool forward = false;
bool backward = false;
float lastBattery = batteryLife;
float mySpeed;

unsigned long speedTime = 1000;
unsigned long lastTime = millis();


void setup() {
  //Buzzer sound for when upload is finished
  buzzer.play(">g32>>c32");
  // writing to LCD
  lcd.clear();
  lcd.print("Press A");
  lcd.gotoXY(0,1);
  lcd.print("to start");
  //wait for the button to be pressed
  buttonA.waitForButton();
  //waiting for the user to get away
  delay(1000);
  lcd.clear();
  encoder.init();

}

void loop() {

  //Calling function
  count = distanceCounter();
  meters += count;
  batteryDrain();
  batteryCharge();
  motors.setSpeeds(100,100);
  if (  (millis()-lastTime) >= speedTime){
    mySpeed = speedoMeter();
    
  }
  //Printing meters
  lcd.gotoXY(0,0);
  lcd.print(mySpeed);
  lcd.gotoXY(0,1);
  lcd.print("m/s");
  delay(10);

  }
  


float distanceCounter(){
  //Measuring CPR count 
  int leftCPR = encoder.getCountsAndResetLeft();
  int rightCPR = encoder.getCountsAndResetRight();
  //Converting CPR count to meters
  float leftCounter = leftCPR * 0.000125;
  float rightCounter = rightCPR * 0.000125;
  //Calculating the average of both motors 
  float distance = (leftCounter + rightCounter) / 2;

  return distance;
}

float batteryDrain(){
  //Draining battery life
  if(count > 0) batteryLife = batteryLife - count;  
}
 
float batteryCharge(){
  //Recharging battery life
  if(count < 0 ) batteryLife = batteryLife - count;

}

float speedoMeter(){

  float deltaBatt = (lastBattery - batteryLife)*(-1);
  lastBattery = batteryLife;
  lastTime = millis();


  return deltaBatt;
  
}
