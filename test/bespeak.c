/*
 * Some debugging here?
 *
 * compileWith$ gcc -Wall -g3 -Og -o thisCfile thisCfile.c
 *
 */
#include <stdio.h>
#include <string.h>

#include "vercod.h"

// hash lookup macro -
#define ASCTOVCODE(INCHAR) ({int retval; \
	retval = vcode[(unsigned int)INCHAR]; retval;})  // reveal

// binary conversion macro -
#define BINTESTBIT(VERIBYTE) ({int retval; \
	putchar(retval = (VERIBYTE & 1) ? *"1" : *"0"); retval;})
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

void symOut(int veriByte) {
	putchar((veriByte & 1) ? *"1" : *"0");
}
*/
int main() {
	const char text[] = "Greetings, planet!";
	unsigned int textlen, \
		strgc = 0, \
		pskByte = 0, \
		isrtrigger, \
		moreZeros = 31, \
		pskOn = 2;

/*
	while((letter = text[strgc]) != 0) {
		printf("0x%x 0x%x %i\n", vcode[text[strgc]] >> 1, vcode[text[strgc]], letter);
		strgc++;
	}  */
	textlen = strlen(text);
	while(1) {  // this is a kind of ugly state machine
			isrtrigger = 0xff;             // start sending message
			if(isrtrigger) {               // interrupt has triggered
				isrtrigger ^= isrtrigger;  // clear the trigger condition
				if(pskByte) {
					BINTESTBIT(pskByte);   // do binary conversion
					pskByte >>= 1;         // next right shift
				}
				else if (moreZeros) {      // send 0 bits between chars,
					putchar(*"0");         // and during idle periods
					moreZeros--;
				}
				else if (strgc < textlen) {
					moreZeros = 2;         // intercharacter space
					printf("\n%c=", text[strgc]);
					pskByte = ASCTOVCODE(text[strgc]);  // get next character
					strgc++;
				}
				else {
					if(pskOn) {
						if(pskOn == 2) puts("");
						pskByte = 0xffff;  // tx tail
						pskOn--;           // shut off the furnace
					}
					else {
						puts("");
						break;             // MESSAGE COMPLETE
					}
				}
			}
		}
			// do all of the other things that need to be done
	// symOut(text);
	return 0;  // error known
}
