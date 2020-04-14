#include <Zumo32U4.h> //Including Zumo library

  const char fugue[] PROGMEM =
  "! O5 L16 agafaea dac+adaea fa<aa<bac#a dac#adaea f"
  "O6 dcd<b-d<ad<g d<f+d<gd<ad<b- d<dd<ed<f+d<g d<f+d<gd<ad"
  "L8 MS <b-d<b-d MLe-<ge-<g MSc<ac<a ML d<fd<f O5 MS b-gb-g"
  "ML >c#e>c#e MS afaf ML gc#gc# MS fdfd ML e<b-e<b-"
  "O6 L16ragafaea dac#adaea fa<aa<bac#a dac#adaea faeadaca"
  "<b-acadg<b-g egdgcg<b-g <ag<b-gcf<af dfcf<b-f<af"
  "<gf<af<b-e<ge c#e<b-e<ae<ge <fe<ge<ad<fd"
  "O5 e>ee>ef>df>d b->c#b->c#a>df>d e>ee>ef>df>d"
  "e>d>c#>db>d>c#b >c#agaegfe f O6 dc#dfdc#<b c#4";

// naming variables
Zumo32U4Motors motors;
Zumo32U4ButtonC buttonC;
Zumo32U4LCD lcd;
Zumo32U4Buzzer buzzer;

void setup() {
  // writes to LCD
  buzzer.play(">g32>>c32");
  lcd.clear();
  lcd.gotoXY(0, 0);
  lcd.print("Press C");
  lcd.gotoXY(0, 1);
  lcd.print("to start");
}

void loop() {
  //bolean variable buttonPress 
  bool buttonPress = buttonC.getSingleDebouncedPress();

  // if - function that runs if buttonPress = true 
  if (buttonPress) {
    delay(1000); // delay to give user time to remove finger from button
    buzzer.playFrequency(440, 200, 15);
    delay(1000);
    buzzer.playNote(NOTE_A(4), 2000, 15);
    delay(200);
    buzzer.stopPlaying();
    delay(1000);
  while(buzzer.isPlaying());
    buzzer.playFromProgramSpace(fugue);
    motors.setSpeeds(200, 200); // drives forward for 1 second
    delay(5000);
    motors.setSpeeds(0, 0); // stops car 1 ms to give motors a break
    delay(100);
    motors.setSpeeds(150, -150);// turning the car 180 degrees
    delay(865);
    motors.setSpeeds(0, 0); //stops car for 1 ms
    delay(100);
    motors.setSpeeds(200, 200); // drives back to start
    delay(5000);
    motors.setSpeeds(0, 0); // stops car
  }
}
