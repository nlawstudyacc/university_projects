#include <pic32mx.h>
#include <stdint.h>
#include "dataO.h"

int titleShifter = 0;
int scoreboardChanger = 0;
int scoreboardShifter = 0;


void scoreboardSingleplay(void)
{

  int i;
  int j = 64;
  clearDisplay(toggle);
  for(i = 0; i < 512; i++)
  {
    bufferArray[toggle][i] = score_Screens[1][i];
  }
  if(botkills > 9 && botkills < 100)
  {
      j = 58;
  }
  else if(botkills > 99)
  {
      j = 52;
  }
  displayString(toggle, j, 2, itoaconv(botkills));
  display_update(toggle);
  if((getbtnsP1() >> 10) & 0x1)
    {
      scoreboardShifter = 0;
      scoreboardChanger = 0;
    }
}

void scoreboardMultiplay(void)
{
  int i;
  int k = 80;
  int j = 80;

  if(player1kills > 9 && player1kills < 100)
  {
      k = 74;
  }

  else if(player1kills > 99)
  {
      k = 68;
  }

  if(player2kills > 9 && player2kills < 100)
  {
      j = 74;
  }

  else if(player2kills > 99)
  {
      j = 68;
  }

  clearDisplay(toggle);
  for(i = 0; i < 512; i++)
  {
    bufferArray[toggle][i] = score_Screens[0][i];
  }
  displayString(toggle, k, 1, itoaconv(player1kills));
  displayString(toggle, j, 2, itoaconv(player2kills));
  display_update(toggle);
  if((getbtnsP1() >> 10) & 0x1)
    {
      scoreboardShifter = 0;
      scoreboardChanger = 0;
    }
}


void scoreboard(void)
{
  while(screenChanger == 3)
  {
    int i;
    display_update(toggle);
    for(i = 0; i < 512; i++)
    {
      bufferArray[toggle][i] = score_Main[scoreboardShifter][i];
    }
    display_update(toggle);

    if((getbtnsP1() >> 11) & 0x1)
    {
      scoreboardShifter++;
    }
    else if((getbtnsP1() >> 12) & 0x1)
    {
      scoreboardShifter--;
    }
    else if((getbtnsP1() >> 10) & 0x1)
    {
      scoreboardChanger = scoreboardShifter + 1;
    }

    if(scoreboardShifter > 2)
    {
      scoreboardShifter = 0;
    }
    else if(scoreboardShifter < 0)
    {
      scoreboardShifter = 2;
    }

    while((getbtnsP1() >> 10) & 0x1)
		{
				quicksleep(2);
		}

    while(scoreboardChanger == 1)
    {
      scoreboardMultiplay();
    }
    while(scoreboardChanger == 2)
    {
      scoreboardSingleplay();
    }
    if(scoreboardChanger == 3)
    {
      scoreboardShifter = 0;
      scoreboardChanger = 0;
      screenChanger = 0;
    }
    while((getbtnsP1() >> 10) & 0x1)
		{
				quicksleep(2);
		}
    quicksleep(383000);
  }
}
