/*
 * Some debugging here?
 *
 * compileWith$ gcc -Wall -g3 -Og -o thisCfile thisCfile.c
 *                    of text
 */

/*
This is where we're going, this is where we are, this is where we were
Are we done yet?
Do we need to get another ASCII character to decode in the hash table?
zero or one?
beginnin middle or end?
preamble, idle, sending bit, tx tail?
or the 2 zeros between characters
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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
		isrtrigger = 0, \
		moreZeros = 31, \
		pskOn = 2;
	struct timespec begin, end;
    
/*
	while((letter = text[strgc]) != 0) {
		printf("0x%x 0x%x %i\n", vcode[text[strgc]] >> 1, vcode[text[strgc]], letter);
		strgc++;
	}  */
	textlen = strlen(text);
	clock_gettime(CLOCK_MONOTONIC_RAW, &begin);
	while(1) {  // this is a kind of ugly state machine
		clock_gettime(CLOCK_MONOTONIC_RAW, &end);
		if(difftime(end.tv_nsec, begin.tv_nsec) > 30000000) {
			isrtrigger = 2;                    // start sending (imaginary isr)
			puts("feef");
			clock_gettime(CLOCK_MONOTONIC_RAW, &begin);
		}
		for(; isrtrigger; isrtrigger--) {  // interrupt has triggered
			if(pskByte) {
				BINTESTBIT(pskByte);       // do binary conversion
				pskByte >>= 1;             // next right shift
				isrtrigger ^= isrtrigger;
				break;
			}
			else if (moreZeros) {          // send 0 bits between chars
				putchar(*"0");             // and during idle periods
				moreZeros--;
				isrtrigger ^= isrtrigger;
				break;
			}
			else if (strgc < textlen) {
				moreZeros = 2;         // intercharacter space
				printf("\n%c=", text[strgc]);
				pskByte = ASCTOVCODE(text[strgc]);  // get next character
				strgc++;               // increment string counter
				continue;              // rerun the algo
			}
			else {                     // end of input string
				if(pskOn) {            // still going? idle period?
					if(pskOn == 2) puts("");
					pskByte = 0xffff;  // tx tail
					pskOn--;           // shut off the furnace
					continue;          // loop again
				}
				else {
					puts("");
					exit(0);             // MESSAGE COMPLETE
				}
			}
		}
	}
			// do all of the other things that need to be done
	// symOut(text);
	return 0;  // error known
}
