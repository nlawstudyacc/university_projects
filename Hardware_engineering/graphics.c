#include <pic32mx.h>
#include <stdint.h>
#include "dataO.h"


/* for gameplay */
void renderPlayer (int toggle, int x, int y, int cape, int direction) /*this is ghost */
{
  if(direction == 0)
  {
  if(cape == 0)
  {
  drawPixel(toggle, x, y + 1);

  drawPixel(toggle, x + 1, y);
  drawPixel(toggle, x + 1, y + 7);

  drawPixel(toggle, x + 2, y);
  drawPixel(toggle, x + 2, y + 1);
  drawPixel(toggle, x + 2, y + 2);
  drawPixel(toggle, x + 2, y + 3);
  drawPixel(toggle, x + 2, y + 5);
  drawPixel(toggle, x + 2, y + 6);
  drawPixel(toggle, x + 2, y + 7);

  drawPixel(toggle, x + 3, y);
  drawPixel(toggle, x + 3, y + 1);
  drawPixel(toggle, x + 3, y + 2);
  drawPixel(toggle, x + 3, y + 3);
  drawPixel(toggle, x + 3, y + 4);
  drawPixel(toggle, x + 3, y + 5);
  drawPixel(toggle, x + 3, y + 6);
  drawPixel(toggle, x + 3, y + 7);

  drawPixel(toggle, x + 4, y);
  drawPixel(toggle, x + 4, y + 1);
  drawPixel(toggle, x + 4, y + 3);
  drawPixel(toggle, x + 4, y + 4);
  drawPixel(toggle, x + 4, y + 5);
  drawPixel(toggle, x + 4, y + 6);
  drawPixel(toggle, x + 4, y + 7);

  drawPixel(toggle, x + 5, y + 1);
  drawPixel(toggle, x + 5, y + 2);
  drawPixel(toggle, x + 5, y + 4);
  drawPixel(toggle, x + 5, y + 5);
  drawPixel(toggle, x + 5, y + 6);
  drawPixel(toggle, x + 5, y + 7);

  drawPixel(toggle, x + 6, y + 1);
  drawPixel(toggle, x + 6, y + 3);
  drawPixel(toggle, x + 6, y + 5);
  drawPixel(toggle, x + 6, y + 7);

  drawPixel(toggle, x + 7, y + 2);
  drawPixel(toggle, x + 7, y + 5);

  }
  else
  {
    drawPixel(toggle, x, y + 2);
    drawPixel(toggle, x, y + 7);

    drawPixel(toggle, x + 1, y);
    drawPixel(toggle, x + 1, y + 1);
    drawPixel(toggle, x + 1, y + 6);
    drawPixel(toggle, x + 1, y + 7);

    drawPixel(toggle, x + 2, y);
    drawPixel(toggle, x + 2, y + 1);
    drawPixel(toggle, x + 2, y + 2);
    drawPixel(toggle, x + 2, y + 3);
    drawPixel(toggle, x + 2, y + 5);
    drawPixel(toggle, x + 2, y + 6);
    drawPixel(toggle, x + 2, y + 7);

    drawPixel(toggle, x + 3, y);
    drawPixel(toggle, x + 3, y + 1);
    drawPixel(toggle, x + 3, y + 2);
    drawPixel(toggle, x + 3, y + 3);
    drawPixel(toggle, x + 3, y + 4);
    drawPixel(toggle, x + 3, y + 5);
    drawPixel(toggle, x + 3, y + 6);
    drawPixel(toggle, x + 3, y + 7);

    drawPixel(toggle, x + 4, y);
    drawPixel(toggle, x + 4, y + 1);
    drawPixel(toggle, x + 4, y + 3);
    drawPixel(toggle, x + 4, y + 4);
    drawPixel(toggle, x + 4, y + 5);
    drawPixel(toggle, x + 4, y + 6);
    drawPixel(toggle, x + 4, y + 7);

    drawPixel(toggle, x + 5, y + 1);
    drawPixel(toggle, x + 5, y + 2);
    drawPixel(toggle, x + 5, y + 4);
    drawPixel(toggle, x + 5, y + 5);
    drawPixel(toggle, x + 5, y + 6);
    drawPixel(toggle, x + 5, y + 7);

    drawPixel(toggle, x + 6, y + 1);
    drawPixel(toggle, x + 6, y + 3);
    drawPixel(toggle, x + 6, y + 5);
    drawPixel(toggle, x + 6, y + 7);

    drawPixel(toggle, x + 7, y + 2);
    drawPixel(toggle, x + 7, y + 5);

  }
}
  else if (direction == 1)
  {
    if(cape == 0)
    {
    drawPixel(toggle, x, y + 2);
    drawPixel(toggle, x, y + 5);

    drawPixel(toggle, x + 1, y + 1);
    drawPixel(toggle, x + 1, y + 3);
    drawPixel(toggle, x + 1, y + 5);
    drawPixel(toggle, x + 1, y + 7);

    drawPixel(toggle, x + 2, y + 1);
    drawPixel(toggle, x + 2, y + 2);
    drawPixel(toggle, x + 2, y + 4);
    drawPixel(toggle, x + 2, y + 5);
    drawPixel(toggle, x + 2, y + 6);
    drawPixel(toggle, x + 2, y + 7);

    drawPixel(toggle, x + 3, y);
    drawPixel(toggle, x + 3, y + 1);
    drawPixel(toggle, x + 3, y + 3);
    drawPixel(toggle, x + 3, y + 4);
    drawPixel(toggle, x + 3, y + 5);
    drawPixel(toggle, x + 3, y + 6);
    drawPixel(toggle, x + 3, y + 7);

    drawPixel(toggle, x + 4, y);
    drawPixel(toggle, x + 4, y + 1);
    drawPixel(toggle, x + 4, y + 2);
    drawPixel(toggle, x + 4, y + 3);
    drawPixel(toggle, x + 4, y + 4);
    drawPixel(toggle, x + 4, y + 5);
    drawPixel(toggle, x + 4, y + 6);
    drawPixel(toggle, x + 4, y + 7);

    drawPixel(toggle, x + 5, y);
    drawPixel(toggle, x + 5, y + 1);
    drawPixel(toggle, x + 5, y + 2);
    drawPixel(toggle, x + 5, y + 3);
    drawPixel(toggle, x + 5, y + 5);
    drawPixel(toggle, x + 5, y + 6);
    drawPixel(toggle, x + 5, y + 7);

    drawPixel(toggle, x + 6, y);
    drawPixel(toggle, x + 6, y + 7);

    drawPixel(toggle, x + 7, y + 1);

    }
    else
    {
      drawPixel(toggle, x, y + 2);
      drawPixel(toggle, x, y + 5);

      drawPixel(toggle, x + 1, y + 1);
      drawPixel(toggle, x + 1, y + 3);
      drawPixel(toggle, x + 1, y + 5);
      drawPixel(toggle, x + 1, y + 7);

      drawPixel(toggle, x + 2, y + 1);
      drawPixel(toggle, x + 2, y + 2);
      drawPixel(toggle, x + 2, y + 4);
      drawPixel(toggle, x + 2, y + 5);
      drawPixel(toggle, x + 2, y + 6);
      drawPixel(toggle, x + 2, y + 7);

      drawPixel(toggle, x + 3, y);
      drawPixel(toggle, x + 3, y + 1);
      drawPixel(toggle, x + 3, y + 3);
      drawPixel(toggle, x + 3, y + 4);
      drawPixel(toggle, x + 3, y + 5);
      drawPixel(toggle, x + 3, y + 6);
      drawPixel(toggle, x + 3, y + 7);

      drawPixel(toggle, x + 4, y);
      drawPixel(toggle, x + 4, y + 1);
      drawPixel(toggle, x + 4, y + 2);
      drawPixel(toggle, x + 4, y + 3);
      drawPixel(toggle, x + 4, y + 4);
      drawPixel(toggle, x + 4, y + 5);
      drawPixel(toggle, x + 4, y + 6);
      drawPixel(toggle, x + 4, y + 7);

      drawPixel(toggle, x + 5, y);
      drawPixel(toggle, x + 5, y + 1);
      drawPixel(toggle, x + 5, y + 2);
      drawPixel(toggle, x + 5, y + 3);
      drawPixel(toggle, x + 5, y + 5);
      drawPixel(toggle, x + 5, y + 6);
      drawPixel(toggle, x + 5, y + 7);

      drawPixel(toggle, x + 6, y);
      drawPixel(toggle, x + 6, y + 1);
      drawPixel(toggle, x + 6, y + 6);
      drawPixel(toggle, x + 6, y + 7);

      drawPixel(toggle, x + 7, y + 2);
      drawPixel(toggle, x + 7, y + 7);

    }
  }
}


void renderPlayer2 (int toggle, int x, int y, int steps, int direction)
{
  if(direction == 0)
  {
    if(steps == 0)
    {
      drawPixel(toggle, x, y + 4);

      drawPixel(toggle, x + 1, y + 1);
      drawPixel(toggle, x + 1, y + 2);

      drawPixel(toggle, x + 2, y);
      drawPixel(toggle, x + 2, y + 1);
      drawPixel(toggle, x + 2, y + 2);
      drawPixel(toggle, x + 2, y + 3);
      drawPixel(toggle, x + 2, y + 6);
      drawPixel(toggle, x + 2, y + 7);

      drawPixel(toggle, x + 3, y);
      drawPixel(toggle, x + 3, y + 2);
      drawPixel(toggle, x + 3, y + 3);
      drawPixel(toggle, x + 3, y + 7);

      drawPixel(toggle, x + 4, y);
      drawPixel(toggle, x + 4, y + 2);
      drawPixel(toggle, x + 4, y + 3);

      drawPixel(toggle, x + 5, y + 1);
      drawPixel(toggle, x + 5, y + 2);
      drawPixel(toggle, x + 5, y + 5);
      drawPixel(toggle, x + 5, y + 6);

      drawPixel(toggle, x + 6, y + 6);

      drawPixel(toggle, x + 7, y + 4);
    }
    else
    {
      drawPixel(toggle, x, y + 5);

      drawPixel(toggle, x + 1, y + 1);
      drawPixel(toggle, x + 1, y + 2);

      drawPixel(toggle, x + 2, y);
      drawPixel(toggle, x + 2, y + 1);
      drawPixel(toggle, x + 2, y + 2);
      drawPixel(toggle, x + 2, y + 3);
      drawPixel(toggle, x + 2, y + 5);
      drawPixel(toggle, x + 2, y + 6);

      drawPixel(toggle, x + 3, y);
      drawPixel(toggle, x + 3, y + 2);
      drawPixel(toggle, x + 3, y + 3);
      drawPixel(toggle, x + 3, y + 6);

      drawPixel(toggle, x + 4, y);
      drawPixel(toggle, x + 4, y + 2);
      drawPixel(toggle, x + 4, y + 3);

      drawPixel(toggle, x + 5, y + 1);
      drawPixel(toggle, x + 5, y + 2);
      drawPixel(toggle, x + 5, y + 6);
      drawPixel(toggle, x + 5, y + 7);

      drawPixel(toggle, x + 6, y + 7);

      drawPixel(toggle, x + 7, y + 4);
    }
  }
    else if (direction == 1)
    {
      if(steps == 0)
      {
        drawPixel(toggle, x, y + 4);

        drawPixel(toggle, x + 1, y + 6);

        drawPixel(toggle, x + 2, y + 1);
        drawPixel(toggle, x + 2, y + 2);
        drawPixel(toggle, x + 2, y + 5);
        drawPixel(toggle, x + 2, y + 6);

        drawPixel(toggle, x + 3, y);
        drawPixel(toggle, x + 3, y + 2);
        drawPixel(toggle, x + 3, y + 3);

        drawPixel(toggle, x + 4, y);
        drawPixel(toggle, x + 4, y + 2);
        drawPixel(toggle, x + 4, y + 3);
        drawPixel(toggle, x + 4, y + 7);

        drawPixel(toggle, x + 5, y);
        drawPixel(toggle, x + 5, y + 1);
        drawPixel(toggle, x + 5, y + 2);
        drawPixel(toggle, x + 5, y + 3);
        drawPixel(toggle, x + 5, y + 6);
        drawPixel(toggle, x + 5, y + 7);

        drawPixel(toggle, x + 6, y + 1);
        drawPixel(toggle, x + 6, y + 2);

        drawPixel(toggle, x + 7, y + 4);
      }
      else
      {
        drawPixel(toggle, x, y + 4);

        drawPixel(toggle, x + 1, y + 7);

        drawPixel(toggle, x + 2, y + 1);
        drawPixel(toggle, x + 2, y + 2);
        drawPixel(toggle, x + 2, y + 6);
        drawPixel(toggle, x + 2, y + 7);

        drawPixel(toggle, x + 3, y);
        drawPixel(toggle, x + 3, y + 2);
        drawPixel(toggle, x + 3, y + 3);

        drawPixel(toggle, x + 4, y);
        drawPixel(toggle, x + 4, y + 2);
        drawPixel(toggle, x + 4, y + 3);
        drawPixel(toggle, x + 4, y + 6);

        drawPixel(toggle, x + 5, y);
        drawPixel(toggle, x + 5, y + 1);
        drawPixel(toggle, x + 5, y + 2);
        drawPixel(toggle, x + 5, y + 3);
        drawPixel(toggle, x + 5, y + 5);
        drawPixel(toggle, x + 5, y + 6);

        drawPixel(toggle, x + 6, y + 1);
        drawPixel(toggle, x + 6, y + 2);

        drawPixel(toggle, x + 7, y + 5);

      }
    }
  }


void renderBullet (int toggle, int x, int y, int direction)
{
  if(direction == 0) //right
  {
    drawPixel(toggle, x, y);
    drawPixel(toggle, x + 1, y);

  }
  else if (direction == 1) //left
  {
    drawPixel(toggle, x, y);
    drawPixel(toggle, x - 1, y);

  }
  else if (direction == 2) //up
  {
    drawPixel(toggle, x, y);
    drawPixel(toggle, x, y + 1);
  }
  else if (direction == 3) //down
  {
    drawPixel(toggle, x, y);
    drawPixel(toggle, x, y - 1);
  }
}


/* for title screen */
void displayString(int toggle, int x, int line, char* string) {
	const char* i;
	int j;
	int k = x;
	for (i = string; *i!='\0'; i++) {
		char c = *i;
		/* Dont draw outside the screen */
		if(j + k > 128) {
			continue;
		}
		/* Display every hex value of a char */
		for (j = 0; j<5; j++) {
			bufferArray[toggle][j + k + line*128] |= charArray[(c - 48)*5 + j];
			}
		/* Next letter and add space. */
		k += 6;
	}
}


void renderTextures(int toggle)
{
  int i;

    for(i = 0; i < 512; i++)
      {
        bufferArray[toggle][i] = allMaps[maps][i];
      }
}
