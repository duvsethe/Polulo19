#include <Zumo32U4.h>
Zumo32U4ButtonA buttonA;
Zumo32U4ButtonB buttonB;
Zumo32U4ButtonB buttonC;
Zumo32U4LCD lcd;

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
      lcd.print(">MenuItem1");
      lcd.gotoXY(0, 1);
      lcd.print(" MenuItem2");
      break;
    case 2:
      lcd.clear();
      lcd.print(" MenuItem1");
      lcd.gotoXY(0, 1);
      lcd.print(">MenuItem2");
      break;
    case 3:
      lcd.clear();
      lcd.print(">MenuItem3");
      lcd.gotoXY(0, 1);
      lcd.print(" MenuItem4");
      break;
    case 4:
      lcd.clear();
      lcd.print(" MenuItem3");
      lcd.gotoXY(0, 1);
      lcd.print(">MenuItem4");
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
  lcd.print(">Executing #1");
  delay(1500);
}
void action2() {
  lcd.clear();
  lcd.print(">Executing #2");
  delay(1500);
}
void action3() {
  lcd.clear();
  lcd.print(">Executing #3");
  delay(1500);
}
void action4() {
  lcd.clear();
  lcd.print(">Executing #4");
  delay(1500);
}
