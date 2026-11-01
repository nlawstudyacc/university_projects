/*used for necessary initialization! */
#include "dataO.h"
#include <pic32mx.h>
#include <stdint.h>


void timer1_begin (void)
{
		T1CON = 0x0;

	  T1CONSET = 0x30;

	  TMR1 = 0x0;

	  PR1 = (((8000000 / 256) / 10) / 100);
	  T1CONSET = 0x8000;
		IPCSET(1) = 0x1f;
  	IECSET(0) = 0x10;
	return;
}

void timer1_stop (void)
{
	IEC(0) = 0;
	IPC(1) = 0;
	IFS(0) = 0;
	T1CON = 0;

	return;
}
