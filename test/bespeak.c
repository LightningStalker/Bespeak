/*
 * Some debugging here?
 *
 * compileWith$ gcc -g -o thisCfile thisCfile.c
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
			putchar((veriByte & 1) ? *"1" : *"0");  // LSB bit test 0
		}
		while(veriByte >>= 1);               // Next right shift
		puts(" 00");                         // DEBUG
		msgChar++;                           // Next character
	}
	//putchar(0x0a);                           // DEBUG
}

int main() {
	char text[] = "Greetings, planet!";
	int strgc = 0;
	char letter;
/*
	while((letter = text[strgc]) != 0) {
		printf("0x%x 0x%x %i\n", vcode[text[strgc]] >> 1, vcode[text[strgc]], letter);
		strgc++;
	}  */
	symOut(text);
	return 0;
}