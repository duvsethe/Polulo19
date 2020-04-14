#include <Zumo32U4.h>
Zumo32U4ButtonA buttonA;
Zumo32U4ButtonB buttonB;
Zumo32U4ButtonC buttonC;
Zumo32U4LCD lcd;
Zumo32U4Motors motors;

int menu = 1;

void setup() {
  lcd.init();
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
      lcd.print("Battery");
      break;
    case 3:
      lcd.clear();
      lcd.print(">Battery");
      lcd.gotoXY(0, 1);
      lcd.print(" Menu4");
      break;
    case 4:
      lcd.clear();
      lcd.print("> Menu4");
      lcd.gotoXY(0, 1);
      lcd.print("Menu4");
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

void action11(){
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

void action12(){
  lcd.clear();
  lcd.print(">Circle");
  delay(1500);
  motors.setSpeeds(80, 200); //Begynne svingen
  delay(3750);
  motors.setSpeeds(0, 0); // stops car entirely
}

void action13(){
  lcd.clear();
  menu = 1;
}
