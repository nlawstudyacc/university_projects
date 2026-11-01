#include <pic32mx.h>
#include <stdint.h>
#include "dataO.h"

int toggle = 0;
int timeoutDisplay = 0;
int timeoutGameOver = 0;
int timeoutMove = 0;
int timeoutAnimation = 0;
int timeoutBullet = 0;
int timerestrictionBullet = 0;
int timerestrictionBullet2 = 0;
int timeout = 0;
int timeout2 = 0;


void user_isr(void)
{
	if(IFS(0) & 0x10)
  {
    timeoutDisplay++;
		timeoutMove++;
		timeoutAnimation++;
		timeoutBullet++;
		timerestrictionBullet++;
		timeoutGameOver++;
		if(timeout == 1)
			timerestrictionBullet++;
		if(timeout2 == 1)
			timerestrictionBullet2++;
    IFSCLR(0) = 0x10;
  }

  if(timeoutDisplay == 20)
  {
		display_update(toggle);
		if(toggle == 0)
		{
			updateBuffer(1);
			toggle = 1;
		}
		else
		{
			updateBuffer(0);
			toggle = 0;
		}

		display_update(toggle);
		timeoutDisplay = 0;
  }

	if(timeoutGameOver == 21)
	{
		game_over(toggle);
		timeoutGameOver = 0;
	}
	if(timerestrictionBullet == 10500)
	{
		timeout = 0;
	}
	if(timerestrictionBullet2 == 5250)
	{
		timeout2 = 0;
	}

	if(timeoutMove == 150)
	{
		movement(timeout);
		bullet1(timeout);
		bullet2(timeout2);
		if(timeout == 0 && bullet1(timeout) == 1)
			{
				timerestrictionBullet = 0;
				timeout = 1;
			}
		if(timeout2 == 0 && bullet2(timeout2) == 1)
			{
				timerestrictionBullet2 = 0;
				timeout2 = 1;
			}
		timeoutMove = 0;
	}

	if(timeoutAnimation == 1000)
	{
		changeCape();
		changeSteps();
		timeoutAnimation = 0;
	}



	if(timeoutBullet == 50)
	{

		flyingBullet();
		timeoutBullet = 0;

	}
  return;
}

unsigned int seed(void)
{
	return (unsigned int) (toggle + TMR2 + TMR1);
}
