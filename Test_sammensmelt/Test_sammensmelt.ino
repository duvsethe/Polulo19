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
      lcd.print(">90Degree");
      lcd.gotoXY(0, 1);
      lcd.print("Turn");
      break;
    case 2:
      lcd.clear();
      lcd.print(">Turn");
      lcd.gotoXY(0, 1);
      lcd.print("Sircle");
      break;
    case 3:
      lcd.clear();
      lcd.print(">Sircle");
      lcd.gotoXY(0, 1);
      lcd.print(" Menu4");
      break;
    case 4:
      lcd.clear();
      lcd.print(" Menu4");
      lcd.gotoXY(0, 1);
      lcd.print(">Menu4");
      break;
    case 5:
      menu = 4;
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
  }
}

void action1() {
  lcd.clear();
  lcd.print(">Exec 1");
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
void action2() {
  lcd.clear();
  lcd.print(">Exec 2");
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

void action3() {
  lcd.clear();
  lcd.print(">Exec 3");
  delay(1500);
  motors.setSpeeds(80, 200); //Begynne svingen
  delay(3750);
  motors.setSpeeds(0, 0); // stops car entirely
}


void action4() {
  lcd.clear();
  lcd.print(">Exec 4");
  delay(1500);
}
