#include <EEPROM.h> //Including EEPROM library
#include <Zumo32U4.h> //Including Zumo library

Zumo32U4Motors motors;
Zumo32U4ButtonA buttonA;
Zumo32U4ButtonB buttonB;
Zumo32U4LCD lcd;
Zumo32U4LineSensors linesensor;

int account_balance = EEPROM.read(0);
//Making account balance variable


const int money_deposit = 5; // Fixed amount of money to deposit (when e.g pushing button)



void setup() {
  lcd.init();
  lcd.clear();
  lcd.gotoXY(0,0);
  
  

}

void loop() {

  if ( buttonA.getSingleDebouncedPress()){
  account_balance += money_deposit;
  }
  if ( buttonB.getSingleDebouncedPress()){
  account_balance -= money_deposit;
  }
  
  EEPROM.write(0,account_balance); // Write account balance to EEPROM
  lcd.print(EEPROM.read(0)*100);
  delay(20);
  lcd.clear();
  lcd.gotoXY(0,0);
  
}
