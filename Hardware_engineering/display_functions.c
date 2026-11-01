/* Used for storing all necessary functions for display */

#include <pic32mx.h>
#include <stdint.h>
#include "dataO.h"

#define DISPLAY_CHANGE_TO_COMMAND_MODE (PORTFCLR = 0x10)
#define DISPLAY_CHANGE_TO_DATA_MODE (PORTFSET = 0x10)

#define DISPLAY_ACTIVATE_RESET (PORTGCLR = 0x200)
#define DISPLAY_DO_NOT_RESET (PORTGSET = 0x200)

#define DISPLAY_ACTIVATE_VDD (PORTFCLR = 0x40)
#define DISPLAY_ACTIVATE_VBAT (PORTFCLR = 0x20)

#define DISPLAY_TURN_OFF_VDD (PORTFSET = 0x40)
#define DISPLAY_TURN_OFF_VBAT (PORTFSET = 0x20)

/*for buffer array*/
#define BUFFER_ARRAY_SIZE 512
#define WIDTH 128
#define HEIGHT 32

/* quicksleep:
   A simple function to create a small delay.
   Very inefficient use of computing resources,
   but very handy in some special cases. */
void quicksleep(int cyc) {
	int i;
	for(i = cyc; i > 0; i--);
}

void spiBUF(uint8_t data) {
	while(!(SPI2STAT & 0x08));
	SPI2BUF = data;
	while(!(SPI2STAT & 1));
}

/* For display_initialization */
void display_init(void) {
  DISPLAY_CHANGE_TO_COMMAND_MODE;
	quicksleep(10);
	DISPLAY_ACTIVATE_VDD;
	quicksleep(1000000);

	spiBUF(0xAE);
	DISPLAY_ACTIVATE_RESET;
	quicksleep(10);
	DISPLAY_DO_NOT_RESET;
	quicksleep(10);

	spiBUF(0x8D);
	spiBUF(0x14);

	spiBUF(0xD9);
	spiBUF(0xF1);

	DISPLAY_ACTIVATE_VBAT;
	quicksleep(10000000);

	spiBUF(0xA1);
	spiBUF(0xC8);

	spiBUF(0xDA);
	spiBUF(0x20);


  /*set to Horizontal addressing mode */
  spiBUF(0x20);
  spiBUF(0x0);

  /*Activate Display*/
  spiBUF(0xAF);
  quicksleep(100);

  DISPLAY_CHANGE_TO_DATA_MODE;
}

/**
 * Update the display.
 */
void display_update(int toggle) {
	/* send render buffer to screen */
	int i;
	for(i=0; i < BUFFER_ARRAY_SIZE; i++) {
		spiBUF(bufferArray[toggle][i]);
	}
}

/* Clear display */
void clearDisplay(int toggle) {
	int i;

	for(i=0; i<BUFFER_ARRAY_SIZE; i++) {
		bufferArray[toggle][i] = 0x0;
	}

}

 /*Put a pixel on display */

void drawPixel(int toggle, int x, int y) {

	if((x < WIDTH && y < HEIGHT) && (x > 0 && y > 0)) {
		/* array pos value (0-8, where 0 is upper pixel, 8 is lowest pixel) */
		int yOffset = y % 8;

		/* on which page the pixel is */
		int page = y / 8;
		/* position in the data buffer array */
		int arrayPos = page*128 + x;

		/* OR pixel with current value in the column. (1 = 1, 2 = 10, 3 = 100 ...) */
		bufferArray[toggle][arrayPos] = bufferArray[toggle][arrayPos] | (0x1 << yOffset);
	}
}

/* Used for displaying integrer variables */
#define ITOA_BUFSIZ ( 24 )
char * itoaconv( int num )
{
  register int i, sign;
  static char itoa_buffer[ ITOA_BUFSIZ ];
  static const char maxneg[] = "-2147483648";

  itoa_buffer[ ITOA_BUFSIZ - 1 ] = 0;   /* Insert the end-of-string marker. */
  sign = num;                           /* Save sign. */
  if( num < 0 && num - 1 > 0 )          /* Check for most negative integer */
  {
    for( i = 0; i < sizeof( maxneg ); i += 1 )
    itoa_buffer[ i + 1 ] = maxneg[ i ];
    i = 0;
  }
  else
  {
    if( num < 0 ) num = -num;           /* Make number positive. */
    i = ITOA_BUFSIZ - 2;                /* Location for first ASCII digit. */
    do {
      itoa_buffer[ i ] = num % 10 + '0';/* Insert next digit. */
      num = num / 10;                   /* Remove digit from number. */
      i -= 1;                           /* Move index to next empty position. */
    } while( num > 0 );
    if( sign < 0 )
    {
      itoa_buffer[ i ] = '-';
      i -= 1;
    }
  }
  /* Since the loop always sets the index i to the next empty position,
   * we must add 1 in order to return a pointer to the first occupied position. */
  return( &itoa_buffer[ i + 1 ] );
}
