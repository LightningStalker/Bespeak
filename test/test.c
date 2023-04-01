// gcc -Wall -g3 -Og -o test test.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "vercod.h"

// hash lookup macro -
#define ASCTOVCODE(INCHAR) ({int retval; \
	retval = vcode[(unsigned int)INCHAR]; retval;})  // reveal

// binary conversion macro -
#define BINTESTBIT(VERIBYTE) ({int retval; \
	putchar(retval = (VERIBYTE & 1) ? *"1" : *"0"); retval;})

int main() {
	const char text[] = "Greetings, planet!";
	enum pskToggle {on, off} pskSwitch;
	enum pskTasks {preamble, idle, sendBit, getChar, txTail} pskDo;
	unsigned int textlen, pskByte, moreZeros, pretailRemains;

	textlen = strlen(text);
	textlen = textlen;
	usleep(200000);
	pskDo = getChar;
	pskSwitch = on;

	if(pskSwitch == on) {
		switch (pskDo) {
			case getChar:             // more characters?
				puts("getChar");
				pskByte = text[1];
				pskDo = sendBit;
			case sendBit:
				if(pskByte) {
					puts("sendBit");
				}
				else {
					pskDo = idle;
					moreZeros = 2;
				}
				break;
			case preamble:
				putchar(*"1");
				if(pretailRemains--);
				else {
					pskDo = getChar;
				}
				break;
			case idle:                // send 0 bits between chars
				putchar(*"0");        // and during idle periods
				if(moreZeros--) pskDo = getChar;
				break;
			case txTail:
				if(pretailRemains--) putchar(*"1");
				break;
			default:
				puts("default");
		}
	}
}