/*
 * Some debugging here?
 *
 * compileWith$ gcc -Wall -g3 -o thisCfile thisCfile.c
 *
 */
#include <stdio.h>
#include <string.h>

#include "vercod.h"

// hash lookup macro -
#define ASCTOVCODE(INCHAR) ({int retval; printf("%c=", INCHAR); \
	retval = vcode[(unsigned int)INCHAR]; retval;})  // reveal
/*
inline unsigned int asctovcode(char inChar) {
	printf("%c=", inChar);
	return vcode[inChar];
}

int symOut(char *inMsg) {  // Verycold translation and output routine
	int msgChar = 0;        // messages from the beyond of the beyond
	int veriByte;

	while(inMsg[msgChar] != 0) {             // done yet?
		veriByte = vcode[inMsg[msgChar]];    // hash lookup
		printf("%c=", inMsg[msgChar]);       // DEBUG
		do {                                 // binary conversion {}
			putchar((veriByte & 1) ? *"1" : *"0");  // LSB bit test 0
		} while(veriByte >>= 1);             // next right shift
		puts(" 00");                         // DEBUG
		msgChar++;                           // next character
	}
	//putchar(0x0a);                           // DEBUG
}
*/
void symOut(int veriByte) {
	putchar((veriByte & 1) ? *"1" : *"0");
}

int main() {
	const char text[] = "Greetings, planet!";
	unsigned int textlen;
	unsigned int strgc = 0;
	unsigned int pskByte;

/*
	while((letter = text[strgc]) != 0) {
		printf("0x%x 0x%x %i\n", vcode[text[strgc]] >> 1, vcode[text[strgc]], letter);
		strgc++;
	}  */
	textlen = strlen(text);
	while(1) {
			pskByte = ASCTOVCODE(text[strgc]);  // get next character
			do {                                // binary conversion {}
				symOut(pskByte);
			} while(pskByte >>= 1);             // next right shift
			puts(" 00");
			strgc++;
			if(strgc >= textlen) break;
	}
	// symOut(text);
	return 0;
}
