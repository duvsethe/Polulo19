#include <EEPROM.h> //Including EEPROM library
#include <Zumo32U4.h> //Including Zumo library

Zumo32U4Motors motors;
Zumo32U4ButtonA buttonA;
Zumo32U4LCD lcd;
Zumo32U4LineSensors linesensor;


//Making account balance variable
int account_balance = 0; 
int buttonPin = 2; 

const int money_deposit = 500; // Fixed amount of money to deposit (when e.g pushing button)



void setup() {
  lcd.init();
  lcd.clear();
  lcd.gotoXY(0,0);
  

}

void loop() {
  
      //evt. putte inn kode som viser oppdatert saldo på zumoskjermen, EEPROM.read(0)
  if ( buttonA.getSingleDebouncedPress()){
  account_balance += money_deposit;
  }
  EEPROM.write(0,account_balance); // Write account balance to EEPROM
  lcd.print(EEPROM.read(0));
  delay(20);
  lcd.clear();
  lcd.gotoXY(0,0);
  
}
