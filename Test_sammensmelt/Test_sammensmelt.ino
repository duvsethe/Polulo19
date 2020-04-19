#include <EEPROM.h> //Including EEPROM library
#include <Zumo32U4.h>

Zumo32U4ButtonA buttonA;
Zumo32U4ButtonB buttonB;
Zumo32U4ButtonC buttonC;
Zumo32U4LCD lcd;
Zumo32U4Motors motors;
Zumo32U4LineSensors linesensor;
Zumo32U4Buzzer buzzer;


//Creating int value for sensvaluer
unsigned int linesensorValues[5];

int account_balance = EEPROM.read(0);
const int money_deposit = 5; // Fixed amount of money to deposit (when e.g pushing button)

const double P = 0.3;
const double D = 8;
double lastE = 0;
const unsigned char maxSpeed = 200;
int tapeNum = 0;
bool linePID = false;
bool lineSTD = false;


int menu = 1;

void setup() {
  lcd.init();
  linesensor.initFiveSensors();
  updateMenu();
}

void loop() {
  if (buttonA.getSingleDebouncedPress()){
    menu++;
    updateMenu();
    delay(100);
  }
  if (buttonC.getSingleDebouncedPress()){
    menu--;
    updateMenu();
    delay(100);
  }
  if (buttonB.getSingleDebouncedPress()){
    executeAction();
    updateMenu();
    delay(100);
  }
}

void updateMenu() {
  switch (menu) {
    case 0:
      menu = 1;
      break;
    case 1:
      lcd.clear();
      lcd.print(">Autonom");
      lcd.gotoXY(0, 1);
      lcd.print("Line");
      break;
    case 2:
      lcd.clear();
      lcd.print(">Line");
      lcd.gotoXY(0, 1);
      lcd.print("Account");
      break;
    case 3:
      lcd.clear();
      lcd.print(">Account");
      lcd.gotoXY(0, 1);
      lcd.print("Battery");
      break;
    case 4:
      lcd.clear();
      lcd.print(">Battery");
      lcd.gotoXY(0, 1);
      lcd.print(" ");
      break;
    case 5:
      menu = 4;
      break;
    case 9:
      menu = 10;
      break;
    case 10:
      lcd.clear();
      lcd.print(">Turn");
      lcd.gotoXY(0,1);
      lcd.print("90Degree");
      break;
    case 11:
      lcd.clear();
      lcd.print(">90Degree");
      lcd.gotoXY(0,1);
      lcd.print("90Circle");
      break;
    case 12:
      lcd.clear();
      lcd.print(">Circle");
      lcd.gotoXY(0,1);
      lcd.print("Back");
      break;
    case 13:
      lcd.clear();
      lcd.print(">Back");
      lcd.gotoXY(0,1);
      lcd.print(" ");
      break;
    case 14:
      menu = 13;
      break;
    case 19:
      menu = 20;
      break;
    case 20:
      lcd.clear();
      lcd.print(">Standard");
      lcd.gotoXY(0,1);
      lcd.print("PID");
      break;
    case 21:
      lcd.clear();
      lcd.print(">PID");
      lcd.gotoXY(0,1);
      lcd.print("Calib");
      break; 
    case 22:
      lcd.clear();
      lcd.print(">Calib");
      lcd.gotoXY(0,1);
      lcd.print("Back");
      break;
    case 23:
      lcd.clear();
      lcd.print(">Back");
      lcd.gotoXY(0,1);
      lcd.print(" ");
      break;
    case 24:
      menu = 23;
      break;
    case 29:
      menu = 30;
      break;
    case 30:
      lcd.clear();
      lcd.print(">View acc");
      lcd.gotoXY(0,1);
      lcd.print("++Cash");
      break;
    case 31:
      lcd.clear();
      lcd.print(">++Cash");
      lcd.gotoXY(0,1);
      lcd.print("Back");
      break;
    case 32:
      lcd.clear();
      lcd.print(">Back");
      lcd.gotoXY(0,1);
      lcd.print(" ");
      break;
    case 33:
      menu = 32;
  }
}

void executeAction() {
  switch (menu) {
    case 1:
      action1();
      break;
    case 2:
      action2();
      break;
    case 3:
      action3();
      break;
    case 4:
      action4();
      break;
    case 10:
      action10();
      break;
    case 11:
      action11();
      break;
    case 12:
      action12();
      break;
    case 13:
      action13();
      break;
    case 20:
      action20();
      break;
    case 21:
      action21();
      break;
    case 22:
      action22();
      break;
    case 23:
      action23();
      break;
    case 30:
      action30();
      break;
    case 31:
      action31();
      break;
    case 32:
      action32();
      break;
    
      
  }
}

void action1() {
  lcd.clear();
  menu = 10;
  }
     
void action2() {
  lcd.clear();
  menu = 20;
}

void action3() {
  lcd.clear();
  menu = 30;
}


void action4() {
  lcd.clear();
  lcd.print(">Exec 4");
  delay(1500);
}

void action10(){
  if ( account_balance >= 10){
    account_balance -= 10;
    EEPROM.write(0, account_balance);
    lcd.clear();
    lcd.print(">Turning");
    delay(1500);
    motors.setSpeeds(200, 200); // drives forward for 1 second
    delay(5000);
    motors.setSpeeds(0, 0); // stops car 1 ms to give motors a break
    delay(100);
    motors.setSpeeds(150, -150);// turning the car 180 degrees
    delay(950);
    motors.setSpeeds(0, 0); //stops car for 1 ms
    delay(100);
    motors.setSpeeds(200, 200); // drives back to start
    delay(5000);
    motors.setSpeeds(0, 0); // stops car
  }
  else{
    lcd.clear();
    lcd.print("To low");
    lcd.gotoXY(0,1);
    lcd.print("balance");
    delay(2000);
  }
}

void action11(){
  if ( account_balance >= 10){
    account_balance -= 10;
    EEPROM.write(0, account_balance);
    lcd.clear();
    lcd.print(">90Degree");
    delay(1500);
    for(int i=0;i<4;i++){
      motors.setSpeeds(200, 200); // drives forward
      delay(500);
      motors.setSpeeds(0, 0); // stops car
      delay(500);
      motors.setSpeeds(-150, 150); // turns car 90 degrees to the left
      delay(470);
      motors.setSpeeds(0,0);
      delay(500);
    }
  }
  else{
    lcd.clear();
    lcd.print("To low");
    lcd.gotoXY(0,1);
    lcd.print("balance");
    delay(2000);
  }
}

void action12(){
  if ( account_balance >= 10){
    account_balance -= 10;
    EEPROM.write(0, account_balance);
    lcd.clear();
    lcd.print(">Circle");
    delay(1500);
    motors.setSpeeds(80, 200); //Start turning
    delay(3750);
    motors.setSpeeds(0, 0); // stops car entirely
  }
  else{
    lcd.clear();
    lcd.print("To low");
    lcd.gotoXY(0,1);
    lcd.print("balance");
    delay(2000);
  }
}

void action13(){
  lcd.clear();
  menu = 1;
}

void action20(){
  lcd.clear();
  lineSTD = true;
  tapeNum = 0;
  delay(1000);
  while ( lineSTD ){
    int position = linesensor.readLine(linesensorValues);
    bool myTape = false;
  
   
    if ( linesensorValues[0] >= 800 && linesensorValues[1] >= 800 && linesensorValues[2] >= 800 && linesensorValues[3] >=800 && linesensorValues[4] >=800 ){
      motors.setSpeeds(0,0);
      delay(500);
      myTape = true;
      if ( buttonB.isPressed()){
        lineSTD = false;  
        break;
      }
    }
    
   //Prints linesensors value on lcd
   lcd.gotoXY(0,0);
   lcd.print(position);
   lcd.gotoXY(0,1);
   lcd.print(tapeNum);
   
   //Using function to choose motorpower
   direct(position, myTape, tapeNum);
   delay(50);
  }
  
  menu = 1;
}


void direct(int x, bool myTape, int Num ){

  if ( myTape && Num == 0 ){
    motors.setSpeeds(100,100);
    delay(2000);
    tapeNum = 1;
  }
  else if ( myTape && Num == 1 ){
    motors.setSpeeds(0,0);
    delay(200);
    motors.setSpeeds(100, -100);
    delay(1800);
    motors.setSpeeds(100,100);
    delay(1800);
    motors.setSpeeds(0,0);
    delay(20);
    motors.setSpeeds(100, -100);
    delay(900);
    motors.setSpeeds(0,0);
    delay(20);
    motors.setSpeeds(100,100);
    tapeNum = 0;
  }
  else if( x < 1500){
    motors.setSpeeds(0,175);
  }
  else if( x < 1600){
    motors.setSpeeds(20,175);
  }
  else if( x < 1700){
    motors.setSpeeds(40,175);
  }
  else if( x < 1800){
    motors.setSpeeds(50,175);
  }
  else if( x > 2500){
    motors.setSpeeds(175, 0);
  }
  else if( x > 2400){
    motors.setSpeeds(175, 20);
  }
  else if( x > 2300){
    motors.setSpeeds(175, 40);
  }
  else if( x > 2200){
    motors.setSpeeds(175, 50);
  }
  //Straight forward
  else{
    motors.setSpeeds(150,150);
  }

}

void action21(){
  lcd.clear();
  linePID = true;
  tapeNum = 0;
  delay(1000);
  while ( linePID ){
      //Reads linesensor value and "error"
    if ( buttonB.isPressed()){
      linePID = false;  
      break;
    }
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
    if ( linesensorValues[0] >= 800 && linesensorValues[1] >= 800 && linesensorValues[2] >= 800 && linesensorValues[3] >=800 && linesensorValues[4] >=800){
      motors.setSpeeds(0,0);
      delay(500);
      if ( buttonB.isPressed()){
      linePID = false;  
      break;
    }
      blackTape();
     }
    motors.setSpeeds(leftSpeed, rightSpeed);
    //Prints linesensors on lcd
    lcd.print(tapeNum);
    lcd.gotoXY(0,0);
}
  motors.setSpeeds(0,0);
  lcd.clear();
  lcd.gotoXY(0,0);
  lcd.print("Back to");
  lcd.gotoXY(0,1);
  lcd.print("Meny");
  delay(1000);
  menu = 1;
}

void blackTape(){
  if( tapeNum == 0  ){
    motors.setSpeeds(100,100);
    delay(2000);
    tapeNum = 1;
  }
  else if ( tapeNum == 1){
    motors.setSpeeds(0,0);
    delay(200);
    motors.setSpeeds(100, -100);
    delay(1800);
    motors.setSpeeds(100,100);
    delay(1800);
    motors.setSpeeds(0,0);
    delay(20);
    motors.setSpeeds(100, -100);
    delay(900);
    motors.setSpeeds(0,0);
    delay(20);
    motors.setSpeeds(100,100);
    tapeNum = 0;
  }
}


void action22(){
  lcd.clear();
  lcd.print("Cali -");
  lcd.gotoXY(0,1);
  lcd.print("brating");
  delay(1000);
  int i = 0;
  while(i < 100){
    linesensor.calibrate();
    motors.setSpeeds(150, -150);
    i++;
  }
  motors.setSpeeds(0,0);
  buzzer.play(">g32>>c32");
  lcd.clear();
}

void action23(){
  lcd.clear();
  menu = 1;
}

void action30(){
  lcd.clear();
  lcd.print("Balance:");
  lcd.gotoXY(0,1);
  lcd.print(EEPROM.read(0));
  delay(2000);
}

void action31(){
  lcd.clear();
  if ( account_balance <= 250){
    account_balance += money_deposit;
   EEPROM.write(0, account_balance);
  lcd.clear();
  lcd.print("Balance:");
  lcd.gotoXY(0,1);
  lcd.print(EEPROM.read(0));
  }
  else{
    lcd.clear();
    lcd.print("Account");
    lcd.gotoXY(0,1);
    lcd.print("is full!");
    delay(2000);   
  }
}
void action32(){
  lcd.clear();
  menu = 1;
}
