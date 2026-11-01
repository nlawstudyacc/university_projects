#include <pic32mx.h>
#include <stdint.h>
#include <stdlib.h>
#include "dataO.h"

void *stdin, *stdout, *stderr;
int screenChanger = 0;
int maps;

int randomMap(void)
{
  return rand() % 4;
}

int main() {

	int WallShapes [4][12] ={
		{40, -2, 24, -2, 34, 24, 77, -2, 61, -2, 71, 24},
		{78, 0, 32, 0, 48, -11, 112, 16, 58, 16, 11, 23},
		{16, 16, 0, 16, 47, 0, 112, 16, 96, 16, 80, 16},
		{81, 0, 29, 0, 13, 0, 64, 16, 48, 16, 97, 0}
	};
	SYSKEY = 0xAA996655;  /* Unlock OSCCON, step 1 */
	SYSKEY = 0x556699AA;  /* Unlock OSCCON, step 2 */
	while(OSCCON & (1 << 21)); /* Wait until PBDIV ready */
	OSCCONCLR = 0x180000; /* clear PBDIV bit <0,1> */
	while(OSCCON & (1 << 21));  /* Wait until PBDIV ready */
	SYSKEY = 0x0;  /* Lock OSCCON */

	/* Set up output pins */
	AD1PCFG = 0xFFFF;
	ODCE = 0x0;
	TRISECLR = 0xFF;
	PORTE = 0x0;

	/* Output pins for display signals */
	PORTF = 0xFFFF;
	PORTG = (1 << 9);
	ODCF = 0x0;
	ODCG = 0x0;
	TRISFCLR = 0x70;
	TRISGCLR = 0x200;

	/* Set up input pins */
	TRISDSET = (1 << 8);
	TRISFSET = (1 << 1);

	/* Set up SPI as master */
	SPI2CON = 0;
	SPI2BRG = 4;
	/* SPI2STAT bit SPIROV = 0; */
	SPI2STATCLR = 0x40;
	/* SPI2CON bit CKP = 1; */
	SPI2CONSET = 0x40;
	/* SPI2CON bit MSTEN = 1; */
	SPI2CONSET = 0x20;
	/* SPI2CON bit ON = 1; */
	SPI2CONSET = 0x8000;

	/* for buttons */
	TRISE = TRISE | 0xff00;
	TRISD = TRISD | 0xffe3;
	enable_interrupt();

	display_init();
	getbtnsP1(); //for game function!!!
	while(1)
	{
    TMR2 = 0x0;
    T2CONSET = 0x8000;
		while(screenChanger == 0)
		{
			int i;

		  display_update(toggle);
		  for(i = 0; i < 512; i++)
		  {
		    bufferArray[toggle][i] = title_Screen[titleShifter][i];
		  }
		  display_update(toggle);
		  if((getbtnsP1() >> 11) & 0x1)
		  {
		    titleShifter++;
		  }
		  else if((getbtnsP1() >> 12) & 0x1)
		  {
		    titleShifter--;
		  }
		  else if((getbtnsP1() >> 10) & 0x1)
		  {
		    screenChanger = titleShifter + 1;
		  }

		  if(titleShifter > 2)
		  {
		    titleShifter = 0;
		  }
		  else if(titleShifter < 0)
		  {
		    titleShifter = 2;
		  }
		  quicksleep(390000);
		}
		titleShifter = 0;
    srand(seed());
    T2CON = 0;
		while((getbtnsP1() >> 10) & 0x1)
		{
				quicksleep(2);
		}
		maps = randomMap();
		wallLShapeX1 = WallShapes[maps][0];
    wallLShapeY1 = WallShapes[maps][1];
    wallTShapeX1 = WallShapes[maps][2];
    wallTShapeY1 = WallShapes[maps][3];
    wallCShapeX1 = WallShapes[maps][4];
    wallCShapeY1 = WallShapes[maps][5];
    wallLShapeX2 = WallShapes[maps][6];
    wallLShapeY2 = WallShapes[maps][7];
    wallTShapeX2 = WallShapes[maps][8];
    wallTShapeY2 = WallShapes[maps][9];
    wallCShapeX2 = WallShapes[maps][10];
    wallCShapeY2 = WallShapes[maps][11];

		while(screenChanger == 1)
		{
			SinglePlayer = 1;
			timer1_begin();
			while(screenChanger == 1)
		  {

		  }
		  SinglePlayer = 0;
		}
		while(screenChanger == 2)
	  {
			timer1_begin();
			while(screenChanger == 2)
		  {

		  }
	  }

		Win();
		timer1_stop();

		while(screenChanger == 3)
		{
			scoreboard();
		}


		while(screenChanger == 4)
		{
			int i;
		  clearDisplay(toggle);
		  for(i = 0; i < 512; i++)
		  {
		    bufferArray[toggle][i] = gameover[w][i];
		  }
		  display_update(toggle);
		  if((getbtnsP1() >> 10) & 0x1)
		    {
		      screenChanger = 0;
		    }
		}

		while((getbtnsP1() >> 10) & 0x1)
		{
				quicksleep(2);
		}
	}
	return 0;
}
