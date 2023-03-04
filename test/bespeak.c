/*
 * Some debugging here?
 *
 * compileWith$ gcc -o thisCfile thisCfile.c
 *
 */
#include <stdio.h>

#include "vercod.h"

void symOut(char *inMsg) {       // Verycold translation and output routine
	int msgChar = 0;
	int veriByte;

	while(inMsg[msgChar] != 0) {             // Done yet?
		veriByte = vcode[inMsg[msgChar]];    // Hash lookup
		printf("%c=", inMsg[msgChar]);       // DEBUG
		do {                                 // Binary conversion {}
			if(veriByte & 1) putchar(*"1");  // LSB bit test 0
			else putchar(*"0");
		}
		while(veriByte >>= 1);               // Next right shift
		putchar(0x0a);                       // DEBUG
		msgChar++;                           // Next character
	}
	putchar(0x0a);                           // DEBUG
}

int main() {
	char text[] = "Greetings, planet!";
	int strgc = 0;
	char letter;

	while((letter = text[strgc]) != 0) {
		printf("0x%x 0x%x %i\n", vcode[text[strgc]] >> 1, vcode[text[strgc]], letter);
		strgc++;
	}
	symOut(text);
	return 0;
}

/* void symOut(int thisym, int rate) { // Translate an ASCII character into ITU morse and generate keying signal.
  int c = 0;
  uint8_t symval1, symval2;

  if(thisym == *" ") {
    delay(rate * 2); // special case " "
    return;
  }
  // letter number or symbol
  thisym = thisym - 0x20; // align ASCII with start of morse symbol table
  symval1 = pgm_read_byte(&sym[thisym]); // Reading from our symbol table array stored in flash
  symval2 = symval1;
  
  while(symval1 >>= 1) { // WE DON'T NEED THIS. JUST LOOK FOR 0
    c++; // move past initial zeros and high start bit to first signal
  }
  #ifdef DEBUG
    SerialUSB.println(thisym, HEX); // primitive serial debug
    SerialUSB.println(symval, BIN);
    SerialUSB.println(rate, DEC);
    SerialUSB.println(c, DEC);
  #endif
  for(c--; c >= 0; c--) {
    if ((symval2 >> c) & 1) {
      digitalWrite(keyPin, HIGH); // We'll just use the uino output functions here for now.
      delay(rate * 3);
      digitalWrite(keyPin, LOW); // for readability
    }
    else {
      digitalWrite(keyPin, HIGH); // since a need for speed and extremely accurate timing is not anticipated
      delay(rate);
      digitalWrite(keyPin, LOW);
    }
    delay(rate);
  }
}*/