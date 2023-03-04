#include "varuch.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  uint16_t symval;
  char text[] = "Greetings, planet!";
  int strgc = 0;

  while(text[strgc] != 0) {
    symval = pgm_read_byte(&vcode[text[strgc]]);
    Serial.println(symval, HEX);
    strgc++;
  }
}
