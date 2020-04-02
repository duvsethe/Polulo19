
/*
 * 31.03.20 - Fått til avlesning for max og min verdi hvert 30 sek 
 * for temp og photores
 * 
 *02.04.20 
 *- Fått til max og min verdi ultrasonic
 *- Fått til buzzer alarm
 *- Fått til reset av buzzer
 * 
 *NEXT
 *Få til blynk notify og servo motor
 */
#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <ESP32_Servo.h>
#include <analogWrite.h>


//Defining blynk modules
BlynkTimer timer;
WidgetLED led1 (V0);
WidgetLED led2 (V1);
WidgetTerminal terminal(V9);

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "4c6Lu1mnZD0FbMNK-95dckX85k7OEhlB";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Khuongs10";
char pass[] = "Kake1234";

//Defining pinnumber and global variables
const int pinTemp = 32;
const int pinPhoto = 33;
const int pinTilt = 14;
const int pinTrig = 0;
const int pinEcho = 4;
const int buzzer = 2;


bool valTilt;
float valTemp;
int valPhoto;
float valDistance;
int numReadings = 10;

int minPhoto = 1023;
int maxPhoto = 0;

unsigned long calTime = 5000;
unsigned long averageTime = 30000;
unsigned long startTime;

float readingsTemp[50];
int readingsPhoto[50];
int readingsTilt[50];
float readingsDistance[50];
int readIndexTemp = 0;
int readIndexPhoto = 0;
int readIndexTilt = 0;
int readIndexDistance = 0;
int lowTemp = 125;
int highTemp = -50;
int lowPhoto = 255;
int highPhoto = 0;
int boolTilt = false;

//Alarm limits
int tempAlarm_Limit = 30;
int photoAlarm_Limit = 100;
int tiltAlarm_Limit = 1;
int distanceAlarm_Limit = 200;

  


void myTimerEvent1()
{
  //Reading temp value and writing to Blynk
  valTemp = analogRead(pinTemp);
  float volt = (valTemp / 1023.0);
  float tempC = (volt - 0.5) * 100; // converting into Celsius
  readingsTemp[readIndexTemp] = tempC; //Saving the temp into an array
  Blynk.virtualWrite(V10, tempC); //Labeled value Temp
  Blynk.virtualWrite(V11, tempC); // Gauge value Temp
  Blynk.virtualWrite(V12, tempC); //Chart value Temp
  readIndexTemp += 1;
  if (readIndexTemp > 50) readIndexTemp = 0; // Resetting readIndexTemp

}

void myTimerEvent2() {
  //Reads, maps and constrains Fhotoresistor value
  valPhoto = analogRead(pinPhoto);
  valPhoto = map(valPhoto, minPhoto, maxPhoto, 0, 255);
  valPhoto = constrain(valPhoto, 0, 255);
  readingsPhoto[readIndexPhoto] = valPhoto; //Saving valPhoto into an array
  Blynk.virtualWrite(V20, valPhoto); //Labeled value Photoresistor
  Blynk.virtualWrite(V21, valPhoto); //Gauge value Photoresistor
  Blynk.virtualWrite(V22, valPhoto); //Chart value Photoresistor
  readIndexPhoto +=1;
  if(readIndexPhoto > 50) readIndexPhoto = 0; //Resetting readIndexPhto

}

void myTimerEvent3() {
  //Reading value of tiltsensor
  valTilt = digitalRead(pinTilt);
  if (valTilt == true) {
    led1.on();
    led2.off();
    Blynk.virtualWrite(V32, 0); //Chart tiltsensor "off"
    readingsTilt[readIndexTilt] = 0; //Tiltsensor has tilted, an "true" value been added
  }
  else {
    led1.off();
    led2.on();
    Blynk.virtualWrite(V32, 1); //Chart tiltsensor "on"
    readingsTilt[readIndexTilt] = 1;//Tilt sensor not tilted, an false value been added
  }
  readIndexTilt +=1;
  if(readIndexTilt >50) readIndexTilt = 0; //Resetting readIndexTilt
}

void myTimerEvent4(){
  //Calculate the distace
  valDistance = ultraSonic();
  valDistance = constrain(valDistance, 2, 400); //Constrain for min and max value
  readingsDistance[readIndexDistance] = valDistance; //Saving the Distance into an array
  Blynk.virtualWrite(V40, valDistance); //Labeled value Distance
  Blynk.virtualWrite(V41, valDistance); // Gauge value Distance
  Blynk.virtualWrite(V42, valDistance); //Chart value Distance
  readIndexDistance += 1;
  if (readIndexDistance > 50) readIndexDistance = 0; // Resetting readIndexDistance


  
}

void myTimerEvent5() {
  //Function for calculating average temp and photoRes
  //The system has to run for an amount of time before this function to run
  if ((millis() - startTime) >= averageTime) {
    //Creating variables internally
    float totalTemp = 0;
    float totalDistance = 0;
    int totalPhoto = 0;
    int k = 0; 
    int h = 0;
    int t = 0;
    
    //Calculating total values from last readIndex
    for (int i = 0; i < numReadings; i++) {
      int readIndexTemp_Average = (readIndexTemp -1) - i;
      int readIndexPhoto_Average = (readIndexPhoto -1) - i;
      int readIndexDistance_Average = (readIndexPhoto-1)-i;
      
      //If the index go below 0, it starts counting from 50
      if( readIndexTemp_Average < 0){
        readIndexTemp_Average = 49 - k;
        k+=1;
      }
       if(readIndexPhoto_Average < 0){
        readIndexPhoto_Average = 49 - h;
        h+=1;
      }
       if(readIndexDistance_Average < 0){
        readIndexDistance_Average = 49 - t;
        t+=1;
      }
      totalTemp = totalTemp + readingsTemp[readIndexTemp_Average];
      totalPhoto = totalPhoto + readingsPhoto[readIndexPhoto_Average];
      totalDistance = totalDistance + readingsDistance[readIndexDistance_Average];

    }
            
    int averagePhoto = (totalPhoto / numReadings); //Calculating average Photo
    float averageTemp = (totalTemp / numReadings); //Calculating average Temp
    float averageDistance = (totalDistance /numReadings); //Calculating average Distance
    //Printing to terminal    
    terminal.print("The average temp is: ");
    terminal.println(averageTemp);
    terminal.print("The average photoval is: ");
    terminal.println(averagePhoto);
    terminal.print("The average distance is: ");
    terminal.println(averageDistance);
    terminal.flush();
    Blynk.virtualWrite(V13, averageTemp); //Chart average value Temp
    Blynk.virtualWrite(V23, averagePhoto); //Chart average value Photo  
    Blynk.virtualWrite(V43, averageDistance); //Chart average value Distance
    
  }
}

void myTimerEvent6(){
  if ((millis() - startTime) >= averageTime) {
      
    int lowTemp = 125;
    int highTemp = -50;
    int lowPhoto = 255;
    int highPhoto = 0;
    int highDistance = 2;
    int lowDistance = 400;
    int boolTilt = 0;

    for(int i=0; i <= 49; i++){
      int arrayTemp = readingsTemp[i];
      int arrayPhoto = readingsPhoto[i];
      int arrayDistance = readingsDistance[i];
      int arrayTilt = readingsTilt[i];

      if( arrayTemp > highTemp) highTemp = arrayTemp;
      if( arrayTemp < lowTemp) lowTemp = arrayTemp;
      if( arrayPhoto > highPhoto) highPhoto = arrayPhoto;
      if( arrayPhoto < lowPhoto) lowPhoto = arrayPhoto;
      if( arrayTilt == 1) boolTilt = 1;
      if( arrayDistance < lowDistance) lowDistance = arrayDistance;
      if( arrayDistance > highDistance) highDistance = arrayDistance;
  }

    Blynk.virtualWrite(V14, highTemp);
    Blynk.virtualWrite(V15, lowTemp);
    Blynk.virtualWrite(V24, highPhoto);
    Blynk.virtualWrite(V25, lowPhoto);
    Blynk.virtualWrite(V34, boolTilt);
    Blynk.virtualWrite(V44, highDistance);
    Blynk.virtualWrite(V45, lowDistance);  

    alarmFunction(highTemp, lowPhoto, boolTilt, highDistance);

    }
}




BLYNK_WRITE(V7) {
  if( param.asInt()){
    analogWrite(buzzer, 0);
  }
  
}

BLYNK_WRITE(V8) {
  //Slider for choosing how many values to use for calculating the average
  numReadings = param.asInt();
  //Writing to terminal how many values are used
  terminal.print("V8 Slider value is: ");
  terminal.println(numReadings);
  terminal.flush();
}


void setup()
{
  // Debug console & setting pinMode
  Serial.begin(115200);
  pinMode(pinTemp, INPUT);
  pinMode(pinPhoto, INPUT);
  pinMode(pinTilt, INPUT);
  pinMode(pinTrig, OUTPUT);
  pinMode(pinEcho, INPUT);
  pinMode(buzzer, OUTPUT);

  //Resetting the arrays for temp and photo
  for (int thisReading = 0; thisReading <= 50; thisReading++) {
    readingsTemp[thisReading] = 0;
    readingsPhoto[thisReading] = 0;
    readingsTilt[thisReading] = 0;
    readingsDistance[thisReading] = 0;
  }

  //Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 80);
  Blynk.begin(auth, ssid, pass, IPAddress(91, 192, 221, 40), 8080);

  //Turning on led signalising calibration
  led1.on();
  led2.on();
  Blynk.virtualWrite(V8, 10);

  //Clearing the terminal
  terminal.clear();

  //Calibrate for 5 secs
  while (millis() < calTime) {
    valPhoto = analogRead(pinPhoto);
    if (valPhoto < minPhoto) minPhoto = valPhoto;//Record the maximum sensor value
    if (valPhoto > maxPhoto) maxPhoto = valPhoto; //Record the minimum sensor value

  }

  //Turning off led signalising calibration completed
  led1.off();
  led2.off();

  //Writing max and min value for Photoresistor
  terminal.print("Max value for Photoresistor:");
  terminal.println(maxPhoto);
  terminal.print("Min photovalue for Photoresistor: ");
  terminal.print(minPhoto);
  terminal.flush();

  //Setting the interval for the timers
  timer.setInterval(4000L, myTimerEvent1);//Temp sensor every 5 sec
  timer.setInterval(3000L, myTimerEvent2);//Photo resistor every 2 sec
  timer.setInterval(2000L, myTimerEvent3);//Tilt sensor every sec
  timer.setInterval(1000L, myTimerEvent4);//HC-SR04 sensor every sec
  timer.setInterval(10000L, myTimerEvent5);//Calculating average every 10sec
  timer.setInterval(30000L, myTimerEvent6);//Max & Min calue every 30 sec

  startTime = millis();
}

void loop()
{
  Blynk.run();
  timer.run(); // Initiates BlynkTimer

}

float ultraSonic(){
  
  float duration = 0;
  float distance = 0;
  
  digitalWrite(pinTrig, LOW);
  delayMicroseconds(2);
  digitalWrite(pinTrig, HIGH);
  delayMicroseconds(10);
  digitalWrite(pinTrig, LOW);
 
  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  duration = pulseIn(pinEcho, HIGH);
 
  // Convert the time into a distance
  distance = duration/58.2;
  return distance;
}

void alarmFunction(int temp, int photo, int tilt, int distance){

  bool alarmTemp = false;
  bool alarmPhoto = false;
  bool alarmTilt = false;
  bool alarmDistance = false;
  int alarmNumb = 0;
  
  if ( temp > tempAlarm_Limit) alarmTemp = true;
  if ( photo < photoAlarm_Limit) alarmPhoto = true;
  if ( tilt == tiltAlarm_Limit) alarmTilt = true;
  if ( distance > distanceAlarm_Limit) alarmDistance = true;

  if ( alarmTemp == true && alarmPhoto == true) alarmNumb = 1;
  else if ( alarmTemp == true && alarmDistance == true) alarmNumb = 2;
  else if ( alarmDistance == true && alarmPhoto == true) alarmNumb = 3;
  else if ( alarmTilt == true) alarmNumb = 4;
  else { alarmNumb = 0;}
  

  switch( alarmNumb ){
    case 0:

      break;
    case 1:
      Serial.println("ALARM! To high Temp and to low Photo");
      analogWrite(buzzer, 1000);
      break;
    case 2:
      Serial.println("ALARM! To high Temp and to big Distance");
      analogWrite(buzzer, 1000);
      break;
    case 3:
      Serial.println("ALARM! To high Distance and to low Photo");
      analogWrite(buzzer, 1000);
      break;
    case 4:
      Serial.println("ALARM! Door is open!");
      analogWrite(buzzer, 1000);
      break;
  }

  


  
}
