#include "Zumo32U4Dummy.h"

Zumo32U4Motors motors;
Zumo32U4LCD lcd;

Zumo32U4Encoders encoders(&motors); 

int period = 1000; 
unsigned long time_now = 0; 

float prev_distance_count = 0;
 

int left_speed = 200; 
int right_speed = 200; 

void setup() {
  Serial.begin(9600);

  lcd.clear();
  lcd.write("Hey");
  lcd.display();
  motors.setSpeeds(left_speed, right_speed);
}

  
//Display average speed throughout the last second

void loop() {
  
  
  delay(50);
  long countLeft = encoders.getCountsLeft(); 
  long countRight = encoders.getCountsRight();

  float meters_since_start = ((countLeft + countRight)/2.0) / 8000.0;  //(Avereage of countLeft and countRight) Assuming zumo will turn left and right a near equal amount of the time.
  float distance_count = 0; 


//  Serial.println();
  //lcd.clear();
  //lcd.write(String(meters_since_start));
  //lcd.display(); 
    
  //int time_count = millis(); 

  //Distance traveled the last second
  if (left_speed == 0 && right_speed == 0)
  { 
    prev_distance_count = 0; 
  }
  //else if (left_speed > 0 || right_speed > 0 ) 
  { 
    if (millis() >= time_now + period)
    { 
      distance_count = meters_since_start - prev_distance_count; 
      prev_distance_count += distance_count; 
    }
  }
  
  
  if (millis() >= time_now + period) 
  { 
    time_now += period; 
    
    //meassure distance covered the last second, display as m/s 
    float zumo_speed = distance_count; 
    lcd.clear(); 
    lcd.gotoXY(0,0); 
    //lcd.write(String(countLeft));
    lcd.write(String(meters_since_start) + "m");
    lcd.gotoXY(0,1); 
    lcd.write(String(zumo_speed, 3) + "m/s"); 
    lcd.display(); 

    Serial.println(String(countLeft)); 
    Serial.println(String(prev_distance_count));
    
   
  }
  if (millis() >= 15000 && millis() < 20000 ) 
  { 
    motors.setSpeeds(0, 0);
  }
  if (millis() >= 20000 ) 
  { 
    motors.setSpeeds(50, 50);
  }
   
} 
