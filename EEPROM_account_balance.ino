#include <EEPROM.h> //Including EEPROM library

//Making account balance variable
int account_balance = 0; 
int buttonPin = 2; 

const int money_deposit = 500; // Fixed amount of money to deposit (when e.g pushing button)

int buttonState = 0; //Pushbutton status variable
int debounceTime = 20; 
int lastButtonState = 1; 
long unsigned int lastPress; 

void setup() {
  pinMode(buttonPin, INPUT_PULLUP); 

}

void loop() {
  int buttonState = digitalRead(buttonPin); //Read and store the state of buttonPin (0 or 1)
  if ((millis() - lastPress) > debounceTime); //If the time between the last buttonChange is greater than the debounceTime
  {
    lastPress = millis(); //update lastPress 
    if(buttonState == 0 && lastButtonState == 1) //if button is pressed and was released last change
    {
      EEPROM.write(0, (account_balance + money_deposit)); 
      lastButtonState = 0; //Record the lastButtonState
      //evt. putte inn kode som viser oppdatert saldo på zumoskjermen, EEPROM.read(0)
    }

   if (buttonState == 1 && lastButtonState == 0) //If button is not pressed, and was pressed last change
    {
      lastButtonState = 1; //Record the lsatButtonState
    }
  }

  
  EEPROM.write(0,account_balance); // Write account balance to EEPROM
  
}
