

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
#include <WebServer.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <ESP32_Servo.h>
#include <analogWrite.h>


//Defining blynk modules
BlynkTimer timer;
WidgetLED led1 (V0);
WidgetLED led2 (V1);
WidgetTerminal terminal(V9);
Servo myservo;
WebServer server(80);

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "4c6Lu1mnZD0FbMNK-95dckX85k7OEhlB";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Khuongs10";
char pass[] = "Kake1234";

//Defining pinnumber and global variables

//Pins
const int pinTemp = 32;
const int pinPhoto = 33;
const int pinTilt = 14;
const int pinTrig = 0;
const int pinEcho = 4;
const int buzzer = 27;

//Raw values from sensors
bool valTilt;
float valTemp;
int numReadings = 10;
float tempC;
int valPhoto;
float valDistance;

//Values for calibrating Photoresistor
int minPhoto = 1023;
int maxPhoto = 0;

//Time variables
unsigned long calTime = 5000;
unsigned long averageTime = 30000;
unsigned long startTime;

//Values for WebServer and arrays
int averagePhoto;
float averageTemp;
float averageDistance;


//Array values
float readingsTemp[50];
int readingsPhoto[50];
int readingsTilt[50];
float readingsDistance[50];
int readIndexTemp = 0;
int readIndexPhoto = 0;
int readIndexTilt = 0;
int readIndexDistance = 0;
int testButton = 0;
int servoEndPos = 0;
int servoPos = 0;
int alarmNumb = 0;

//Alarm limits
int tempAlarm_Limit = 30;
int photoAlarm_Limit = 100;
int tiltAlarm_Limit = 1;
int distanceAlarm_Limit = 200;
int servoAlarmVal = 180;
int servoResetVal = 0;

  


void myTimerEvent1()
{
  //Reading temp value and writing to Blynk
  if( !testButton){
  valTemp = analogRead(pinTemp);
  float volt = (valTemp / 1023.0);
  tempC = (volt - 0.5) * 100; // converting into Celsius
  readingsTemp[readIndexTemp] = tempC; //Saving the temp into an array
  Blynk.virtualWrite(V10, tempC); //Labeled value Temp
  Blynk.virtualWrite(V11, tempC); // Gauge value Temp
  Blynk.virtualWrite(V12, tempC); //Chart value Temp
  readIndexTemp += 1;
  if (readIndexTemp > 50) readIndexTemp = 0; // Resetting readIndexTemp
  }
}

void myTimerEvent2() {
  if( !testButton){
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
}

void myTimerEvent3() {
  if( !testButton){
  //Reading value of tiltsensor
  valTilt = digitalRead(pinTilt);
  if (valTilt == true) {
    led1.on();// Green led on
    led2.off();// Red led off
    Blynk.virtualWrite(V32, 0); //Chart tiltsensor "off"
    readingsTilt[readIndexTilt] = 0; //Tiltsensor has tilted, an "true" value been added
  }
  else {
    led1.off();//Green led off
    led2.on();//Red led on
    Blynk.virtualWrite(V32, 1); //Chart tiltsensor "on"
    readingsTilt[readIndexTilt] = 1;//Tilt sensor not tilted, an false value been added
  }
  readIndexTilt +=1;
  if(readIndexTilt >50) readIndexTilt = 0; //Resetting readIndexTilt
  }
}

void myTimerEvent4(){
  //Calculate the distace
  if( !testButton){
  valDistance = ultraSonic();
  valDistance = constrain(valDistance, 2, 400); //Constrain for min and max value
  readingsDistance[readIndexDistance] = valDistance; //Saving the Distance into an array
  Blynk.virtualWrite(V40, valDistance); //Labeled value Distance
  Blynk.virtualWrite(V41, valDistance); // Gauge value Distance
  Blynk.virtualWrite(V42, valDistance); //Chart value Distance
  readIndexDistance += 1;
  if (readIndexDistance > 50) readIndexDistance = 0; // Resetting readIndexDistance
  }
}

void myTimerEvent5() {
  //Function for calculating average temp and photoRes
  //The system has to run for an amount of time before this function to run
  if( !testButton){
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
            
    averagePhoto = (totalPhoto / numReadings); //Calculating average Photo
    averageTemp = (totalTemp / numReadings); //Calculating average Temp
    averageDistance = (totalDistance /numReadings); //Calculating average Distance
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
}

void myTimerEvent6(){
  if ((millis() - startTime) >= averageTime) {
    if( !testButton){
      //Creating variables to find MIN and MAX values
      int lowTemp = 125;
      int highTemp = -50;
      int lowPhoto = 255;
      int highPhoto = 0;
      int highDistance = 2;
      int lowDistance = 400;
      int boolTilt = 0;

      for(int i=0; i <= 49; i++){
        //Reading the values from arrays
        int arrayTemp = readingsTemp[i];
        int arrayPhoto = readingsPhoto[i];
        int arrayDistance = readingsDistance[i];
        int arrayTilt = readingsTilt[i];
        //Replace the MIN and MAX values
        if( arrayTemp > highTemp) highTemp = arrayTemp;
        if( arrayTemp < lowTemp) lowTemp = arrayTemp;
        if( arrayPhoto > highPhoto) highPhoto = arrayPhoto;
        if( arrayPhoto < lowPhoto) lowPhoto = arrayPhoto;
        if( arrayTilt == 1) boolTilt = 1;
        if( arrayDistance < lowDistance) lowDistance = arrayDistance;
        if( arrayDistance > highDistance) highDistance = arrayDistance;
      }
      //Charting the MIN and MAX values
      Blynk.virtualWrite(V14, highTemp);
      Blynk.virtualWrite(V15, lowTemp);
      Blynk.virtualWrite(V24, highPhoto);
      Blynk.virtualWrite(V25, lowPhoto);
      Blynk.virtualWrite(V34, boolTilt);
      Blynk.virtualWrite(V44, highDistance);
      Blynk.virtualWrite(V45, lowDistance);  
      //Sends values to alarmfunction
      alarmFunction(highTemp, lowPhoto, boolTilt, highDistance);
    }
  }
}

void myTimerEvent7(){
  //Testing servomotor
  //When testing the servo, sensors do not read values
  //Testing does not work if theres an alarm active
  if ( alarmNumb == 0 && testButton == 1){
    if( servoEndPos == 0){
      Serial.println("test");
      myservo.write(servoPos);
      servoPos += 1;
      if ( servoPos == 180) servoEndPos = 1;
    }
     else if (servoEndPos == 1){
      Serial.println("test2");
      myservo.write(servoPos);
      servoPos -= 1;
      if (servoPos == 0) servoEndPos = 0;
     }
  }
}

void myTimerEvent8(){

}



BLYNK_WRITE(V7) {
  //Resetting buzzer and LED alarms
  if( param.asInt()){
    servoReset();
    Serial.println("Alarm reset");
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

BLYNK_WRITE(V99){
  //Test button for servomotr
  testButton  = param.asInt();
 
}



void setup()
{
  // Debug console & connecting to wifi
  Serial.begin(115200);
  delay(100);
  Serial.println("Connecting to ");
  Serial.println(ssid);
  //Connecting to the local wi-fi
  WiFi.begin(ssid, pass);

  //Controls if connectiong is made and prints the IP adress
  while (WiFi.status() != WL_CONNECTED) {
  delay(1000);
  Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected..!");
  Serial.print("Got IP: ");  Serial.println(WiFi.localIP());
  server.on("/", handle_OnConnect);
  server.onNotFound(handle_NotFound);
  server.begin();
  Serial.println("HTTP server started");
  
  //Setting pinMode
  pinMode(pinTemp, INPUT);
  pinMode(pinPhoto, INPUT);
  pinMode(pinTilt, INPUT);
  pinMode(pinTrig, OUTPUT);
  pinMode(pinEcho, INPUT);
  pinMode(buzzer, OUTPUT);
  
  //Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 80);
  Blynk.begin(auth, ssid, pass, IPAddress(91, 192, 221, 40), 8080);

  //Attach pin to servomotor, and test the motor
  myservo.attach(12);
  for ( int i = 0; i <=180; i++){
    myservo.write(i);
    servoPos = i;
    delay(10);
  }
  for ( int i = 180; i >=0; i--){
    myservo.write(i);
    servoPos = i;
    delay(10);
  }

  //Resetting the arrays for temp and photo
  for (int thisReading = 0; thisReading <= 50; thisReading++) {
    readingsTemp[thisReading] = 0;
    readingsPhoto[thisReading] = 0;
    readingsTilt[thisReading] = 0;
    readingsDistance[thisReading] = 0;
  }

  //Turning on led signalising calibration an sets numReading to 10
  led1.on();
  led2.on();
  Blynk.virtualWrite(V8, 10);

  //Clearing the terminal
  terminal.clear();

  //Calibrate for 5 secs
  unsigned long timeNow = millis();
  while ((millis()-timeNow) < calTime) {
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
  timer.setInterval(2000L, myTimerEvent1);//Temp sensor every 5 sec
  timer.setInterval(1000L, myTimerEvent2);//Photo resistor every 2 sec
  timer.setInterval(500L, myTimerEvent3);//Tilt sensor every sec
  timer.setInterval(750L, myTimerEvent4);//HC-SR04 sensor every sec
  timer.setInterval(10000L, myTimerEvent5);//Calculating average every 10sec
  timer.setInterval(30000L, myTimerEvent6);//Max & Min calue every 30 sec
  timer.setInterval(20L, myTimerEvent7); 
  timer.setInterval(60000L, myTimerEvent8);
  //Start time set
  startTime = millis();
}


float ultraSonic(){
  //Function for the SR-HC04 sensor
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

//Function for alarms
void alarmFunction(int temp, int photo, int tilt, int distance){
  //Creating variables used in the function
  bool alarmTemp = false;
  bool alarmPhoto = false;
  bool alarmTilt = false;
  bool alarmDistance = false;
  //Checks if values are over/under limit values
  if ( temp > tempAlarm_Limit) alarmTemp = true;
  if ( photo < photoAlarm_Limit) alarmPhoto = true;
  if ( tilt == tiltAlarm_Limit) alarmTilt = true;
  if ( distance > distanceAlarm_Limit) alarmDistance = true;
  //Sets the alarmcodes
  if ( alarmTemp == true && alarmPhoto == true) alarmNumb = 1; 
  else if ( alarmTemp == true && alarmDistance == true) alarmNumb = 2;
  else if ( alarmDistance == true && alarmPhoto == true) alarmNumb = 3;
  else if ( alarmTilt == true) alarmNumb = 4;
  else { alarmNumb = 0;}
  

  alarmSwitch(alarmNumb);
  
}

void alarmSwitch(int alarmNumb){
  
  switch( alarmNumb ){
    case 0:

      break;
      //Temp and Photo alarm
    case 1:
      Serial.println("ALARM! To high Temp and to low Photo");
      terminal.println("ALARM! To high Temp and to low Photo");
      terminal.flush();
      servoAlarm();
      break;
      //Temp and Distance alarm
    case 2:
      Serial.println("ALARM! To high Temp and to big Distance");
      terminal.println("ALARM! To high Temp and to big Distance");
      servoAlarm();
      terminal.flush();
      break;
      //Distance and Photo alarm
    case 3:
      Serial.println("ALARM! To high Distance and to low Photo");
      terminal.println("ALARM! To high Distance and to low Photo");
      servoAlarm();
      terminal.flush();
      break;
      //Tilt alarm
    case 4:
      Serial.println("ALARM! Door is open!");
      terminal.println("ALARM! Door is open!");
      servoAlarm();
      terminal.flush();
      break;
  }
}


void servoAlarm(){
  //Sets servo in alarm modus
  myservo.write(servoAlarmVal);
  servoEndPos = 1; //Signalising what end position servo is in
  servoPos = servoAlarmVal;  
}

void servoReset(){
  //Sets servo back in "normal" condition
  myservo.write(servoResetVal);
  servoEndPos = 0; //Signalising what end position servo is in
  servoPos = servoResetVal;
}

void handle_OnConnect() {
  //If connection is made, sends values to create HTML webserver
  float Temperature = averageTemp; // Gets the values of the temperature
  int PhotoRes = averagePhoto; // Gets the values of the humidity 
  float Distance = averageDistance; //Gets the value of SR-HC04
  String alarmText;
  if ( alarmNumb == 0) alarmText = "Normal";
  else{ alarmText = "Alarm";}
  server.send(200, "text/html", SendHTML(Temperature,PhotoRes, Distance, alarmText)); 
}

void handle_NotFound(){
  //If no connection you get an error page
  server.send(404, "text/plain", "Not found");
}

String SendHTML(float Temperature,float PhotoRes, float Distance, String Text){
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr +="<title>ESP32 Sensors Readings</title>\n";
  ptr +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: left;}\n";
  ptr +="body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;}\n";
  ptr +="p {font-size: 24px;color: #444444;margin-bottom: 10px;}\n";
  ptr +="</style>\n";
  ptr +="</head>\n";
  ptr +="<body>\n";
  ptr +="<div id=\"webpage\">\n";
  ptr +="<h1>ESP32 Sensors Readings</h1>\n";
    
  ptr +="<p>Temperature: ";
  ptr +=(int)Temperature;
  ptr +="C";
  ptr +="<p>PhotoResistor: ";
  ptr +=(int)PhotoRes;
  ptr +="<p>Distance: ";
  ptr +=(float)Distance;
  ptr +=" meters";
  ptr +="<p>Status: ";
  ptr +=(String)Text;
  ptr +="<p>Mokka suger pikk";
  ptr +="<br> ";
  ptr +="<br> ";
  ptr +="<br> ";
  ptr +="<br> ";
  ptr +="<br> ";
  ptr +="<br> ";
  ptr +="<img src=http://www.agdervent.no/images/logo/bil-agderventilasjon-72dpi-farge.jpg>";//Image
  ptr +="<br> ";
  ptr +="<br> ";
  ptr +="Made by Khuong Huynh";
  ptr +="</p>";
  ptr +="<meta http-equiv=refresh content=10>";//Refreshes every 10 sec automatically
  
  ptr +="</div>\n";
  ptr +="</body>\n";
  ptr +="</html>\n";
  return ptr;
}


void loop()
{
  Blynk.run();
  timer.run(); // Initiates BlynkTimer
  server.handleClient();

}
