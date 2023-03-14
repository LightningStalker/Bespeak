/* PROJECT BRAIN STUPID
 * Some debugging here?
 *
 * compileWith$ gcc -g3 -o thisCfile thisCfile.c
 *
 */
#include <stdio.h>
#include <string.h>

#include "vercod.h"

unsigned int asctovcode(char inChar) {
	printf("%c=", inChar);
	return vcode[inChar];
}
/*
int symOut(char *inMsg) {  // Verycold translation and output routine
	int msgChar = 0;        // messages from the beyond of the beyond
	int veriByte;

	while(inMsg[msgChar] != 0) {             // Done yet?
		veriByte = vcode[inMsg[msgChar]];    // Hash lookup
		printf("%c=", inMsg[msgChar]);       // DEBUG
		do {                                 // Binary conversion {}
			putchar((veriByte & 1) ? *"1" : *"0");  // LSB bit test 0
		} while(veriByte >>= 1);             // Next right shift
		puts(" 00");                         // DEBUG
		msgChar++;                           // Next character
	}
	//putchar(0x0a);                           // DEBUG
}
*/
void symOut(int veriByte) {
	putchar((veriByte & 1) ? *"1" : *"0");
}

int main() {
	char text[] = "Greetings, planet!";
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
			pskByte = asctovcode(text[strgc]);
			do {                                // Binary conversion {}
				symOut(pskByte);
			} while(pskByte >>= 1);             // Next right shift
			puts(" 00");
			strgc++;
			if(strgc >= textlen) break;
	}
	// symOut(text);
	return 0;
}
