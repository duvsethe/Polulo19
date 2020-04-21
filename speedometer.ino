#include <Zumo32U4.h>

Zumo32U4Motors motors;
Zumo32U4LCD lcd;
Zumo32U4Encoders encoders;  
 
unsigned long last_time = 0;
unsigned long last_minute = 0;
unsigned long one_second = 1000;
unsigned long one_minute = 60000;

float meters = 0;
float meters_per_second = 0;
float average_speed = 0;
float meters_per_minute = 0;

float maxSpeed = 0;

int left_speed = 400; 
int right_speed = 400;

void setup() {  
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
  if((millis()-last_time) >= one_second){
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
    
    last_time = millis();

// if funksjon som går inn hvert minutt
  if((millis()-last_minute) >= one_minute){

    unsigned long my_time = millis()-last_minute;

    meters_per_minute = meters;
    
    average_speed = (meters_per_minute/my_time)*1000; // regner ut gjennomsnittshastighet i m/s

    lcd.clear();
    lcd.gotoXY(0,0);
    lcd.print("M:" + String(maxSpeed) + "m/s"); // printer ut maks hastighet hvert minutt
    lcd.gotoXY(0,1);
    lcd.print("A:" + String(average_speed) + "m/s"); // printer ut gjennomsnittshastighet hvert minutt 

    meters_per_minute = 0;

    maxSpeed = 0;
    
    last_minute = millis();
  }
/*  
  }
  if (millis() >= 15000 && millis() < 20000 ) 
  { 
    motors.setSpeeds(0, 0);
  }
  if (millis() >= 20000 ) 
  { 
    motors.setSpeeds(100, 100);
  }
 */
}
} 
