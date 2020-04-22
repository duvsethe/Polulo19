#include <Zumo32U4.h>
//#include "Zumo32U4Dummy.h" 

#include "math.h"
//#include "wire.h"
Zumo32U4Motors motors;
Zumo32U4LCD lcd;
Zumo32U4Encoders encoders;

//Zumo32U4Encoders encoders(&motors); 


int yellowLed = 13;
int redLed = 17;
 
unsigned long last_time = 0;
unsigned long last_ten_sec = 0;
unsigned long last_minute = 0;
unsigned long one_second = 1000;
unsigned long ten_seconds = 10000; 
unsigned long one_minute = 60000;

int left_speed = 400; 
int right_speed = 400;

float motorSpeed = (left_speed + right_speed) / 2;
float batteryLevel = 100;
 
float meters = 0;
float meters_per_second = 0;
float average_speed = 0;
float meters_per_minute = 0;

float maxSpeed = 0; 

int batteryCalc(float batteryLevel, float motorSpeed)
{ 
  const int batteryDrain = 10;
  const int topSpeed = 400; 

  float actBatteryDrain = (motorSpeed / topSpeed)* batteryDrain; 

  if (fmod(meters, 1.0) >= 0.0 && fmod(meters, 1.0) < 0.5) 
  { 
    if (batteryLevel > 0) 
    { 
      batteryLevel -= actBatteryDrain; 
      if (batteryLevel <= 0) 
      { 
        batteryLevel = 0; 
      }
    }
  }

  return batteryLevel;
}


void setup() {  

//  pinMode(yellowLed, OUTPUT);
//  pinMode(redLed, OUTPUT);
  
  Serial.begin(9600);
  motors.setSpeeds(left_speed, right_speed);
}
void loop() {
  
  delay(10);
//  Serial.println();
  //lcd.clear();
  //lcd.write(String(meters_since_start));
  //lcd.display(); 
    
  //int time_count = millis(); 
//if funksjon som går inn hvert sekund
  if((millis()-last_time) >= one_second)
  {
    int leftCount = encoders.getCountsAndResetLeft(); 
    int rightCount = encoders.getCountsAndResetRight();
    float averageCount = (leftCount+rightCount)/2;
    float this_meter = averageCount/8000.0;
    meters += this_meter; //teller antall meter kjørt
    unsigned long myTime = millis()-last_time; //får tiden når programmet går inn i if funksjonen
    meters_per_second = (this_meter/myTime)*1000; //regner ut meter per sekund 
    if(maxSpeed < meters_per_second) { //lagrer maks hastighet til en variabel 
      maxSpeed = meters_per_second;
    }
    lcd.clear();
    lcd.gotoXY(0,0);
    lcd.print(String(meters) + "m"); 
    lcd.gotoXY(0,1);
    lcd.print(String(meters_per_second) + "m/s"); 
    //lcd.display();

    last_time = millis(); 
  }

          //BatteryLevelCode: 
    //last_ten_sec = millis(); 
    if((millis()-last_ten_sec) >= ten_seconds)
    { 
      //unsigned long bTime = millis()-last_ten_sec;
      batteryLevel = batteryCalc(batteryLevel, motorSpeed);
      // Serial.println(String(batteryLevel)); 
      
      lcd.clear();
      lcd.gotoXY(0,0);
      lcd.print(String(batteryLevel) + "%"); 
      //lcd.display();

      delay(1000);
    
      last_ten_sec = millis();
    }
      
// if funksjon som går inn hvert minutt
  if((millis()-last_minute) >= one_minute)
  {
    unsigned long my_time = millis()-last_minute;
  
    meters_per_minute = meters;
  
    average_speed = (meters/my_time)*1000; // regner ut gjennomsnittshastighet i m/s
    average_speed = (meters_per_minute/my_time)*1000; // regner ut gjennomsnittshastighet i m/s
  
    lcd.clear();
    lcd.gotoXY(0,0);
    lcd.print("M:" + String(maxSpeed) + "m/s"); // printer ut maks hastighet hvert minutt
    lcd.gotoXY(0,1);
    lcd.print("A:" + String(average_speed) + "m/s"); // printer ut gjennomsnittshastighet hvert minutt 
    //lcd.display();

    delay(1000);
  
    meters_per_minute = 0;
  
    maxSpeed = 0;
  
    last_minute = millis(); 
  }

    
if (batteryLevel >= 90) 
  { 
 //digitalWrite(yellowLed, LOW);
 //digitalWrite(redLed, HIGH); 
 ledYellow(0);
 ledRed(0);
 ledGreen(1);
  }

else if (batteryLevel >= 80)
  {
 //digitalWrite(yellowLed, HIGH);
// digitalWrite(redLed, HIGH);
 ledYellow(1);
 ledRed(0);
 ledGreen(0);
  }

else if (batteryLevel >= 70) 
  { 
 //digitalWrite(yellowLed, LOW);
 //digitalWrite(redLed, LOW);
 ledYellow(0);
 ledRed(1);
 ledGreen(0);
  }
else if (batteryLevel == 0 )
  { 
    motors.setSpeeds(0 , 0); 
  //digitalWrite(yellowLed, LOW);
  //digitalWrite(redLed, HIGH);
  ledYellow(0);
  ledRed(0);
  ledGreen(0)
  }
      
}
