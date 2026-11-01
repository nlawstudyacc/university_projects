#include <pic32mx.h>
#include <stdint.h>
#include "dataO.h"

#define SCREEN_HEIGHT 32
#define SCREEN_WIDTH 128

//x p1 pos = xyCoords[0] y p1 pos = xyCoord[1]
//same stuff for x p2 and y p2 but 1 larger
//bullet - 1 larger 2 for xy for each renderPlayer
int xyCoords[8] = {1, 1, 120, 1, -5, -5, -5, -5};
int AIspawn[4][8] = {
  {3, 16, 117, 117, 2, 21, 2, 22},
  {4, 32, 112, 114, 3, 23, 23, 3},
  {3, 50, 83, 113, 3, 4, 3, 3},
  {16, 30, 89, 117, 4, 21, 20, 21}
};

int SinglePlayer = 0;

int cape = 0;
int steps;

int w;

int directionGhost = 0;
int directionPlayer = 1;

int directionBullet;
int directionBullet2 = 1;

int directionBulletFly;
int directionBulletFly2;

int bulletFly = 0;
int bulletFly2 = 0;


int bulletclear = 0;
int bulletclear2 = 0;

int player1kills = 0;
int player2kills = 0;

int botkills = 0;
int currentbotkills = 0;
int randomLocation(void)
{
  return rand() % 4;
}

int player2death(void)
{
  return ((xyCoords[2] <= xyCoords[4] && xyCoords[4] <= xyCoords[2] + 7) && ((xyCoords[3] <= xyCoords[5]) && (xyCoords[5] <= xyCoords[3] + 7)));
}

void rightP2(void)
{
if(rightMovement(2))
  xyCoords[2]++;
directionPlayer = 0;
directionBullet2 = 0;
}

void leftP2(void)
{
  if(leftMovement(2))
    xyCoords[2]--;
  directionPlayer = 1;
  directionBullet2 = 1;
}

void downP2(void)
{
  if(downMovement(2))
    xyCoords[3]++;
  directionBullet2 = 3;
}

void upP2(void)
{
  if(upMovement(2))
    xyCoords[3]--;
  directionBullet2 = 2;
}

void startBullet2(void)
{
  bulletclear2 = 0;
  if(directionBullet2 == 0) //right
  {
    xyCoords[6] = xyCoords[2] + 6;
    xyCoords[7] = xyCoords[3] + 3;
  }
  else if(directionBullet2 == 1) //left
  {
    xyCoords[6] = xyCoords[2] + 1;
    xyCoords[7] = xyCoords[3] + 3;
  }
  else if(directionBullet2 == 2) //up
  {
    xyCoords[6] = xyCoords[2] + 4;
    xyCoords[7] = xyCoords[3] + 1;
  }
  else if(directionBullet2 == 3) //down
  {
    xyCoords[6] = xyCoords[2] + 3;
    xyCoords[7] = xyCoords[3] + 6;
  }
    bulletFly2 = 1;
}

void Win(void)
{
  if(currentbotkills > botkills)
  {
    botkills = currentbotkills;
  }
  xyCoords[0] = 1;
  xyCoords[1] = 1;
  xyCoords[2] = 120;
  xyCoords[3] = 1;
  xyCoords[4] = -5;
  xyCoords[5] = -5;
  xyCoords[6] = -5;
  xyCoords[7] = -5;
  directionGhost = 0;
  directionPlayer = 1;
  directionBullet;
  directionBullet2 = 1;
  bulletFly = 0;
  bulletFly2 = 0;
  currentbotkills = 0;

  maps = 0;
  bulletclear = 0;
  bulletclear2 = 0;
}

void updateBuffer (int toggle)
{
  clearDisplay(toggle);
  renderTextures(toggle);
  renderPlayer (toggle, xyCoords[0], xyCoords[1], cape, directionGhost);
  renderPlayer2 (toggle, xyCoords[2], xyCoords[3], steps, directionPlayer);
  if(bulletclear == 0)
  {
    renderBullet (toggle, xyCoords[4], xyCoords[5], directionBullet);
  }
  else
  {
    xyCoords[4] = -5;
    xyCoords[5] = -5;
    bulletFly = 0;
  }
  if(bulletclear2 == 0)
  {
    renderBullet (toggle, xyCoords[6], xyCoords[7], directionBullet);
  }
  else
  {
    xyCoords[6] = -5;
    xyCoords[7] = -5;
    bulletFly2 = 0;
  }
}


int movement(int timeout)
{
  if(getbtnsP1() & 0x1)
    {

    if(rightMovement(0))
      xyCoords[0]++;
    directionGhost = 0;
    directionBullet = 0;
    }

    if ((getbtnsP1() >> 1) & 0x1)
    {
      if(leftMovement(0))
      xyCoords[0]--;
    directionGhost = 1;
    directionBullet = 1;
  }
    if ((getbtnsP1() >> 2) & 0x1)
    {
    if(downMovement(0))
      xyCoords[1]++;
    directionBullet = 3;
  }
    if ((getbtnsP1() >> 3) & 0x1)
    {
    if(upMovement(0))
      xyCoords[1]--;
    directionBullet = 2;
  }

  if( ((getbtnsP1() >> 5) & 0x1) && (!SinglePlayer) )
  {
    rightP2();
  }
  else if( (xyCoords[2] < xyCoords[0]) && SinglePlayer)
  {
    rightP2();
  }

  if (((getbtnsP1() >> 6) & 0x1) && (!SinglePlayer) )
  {
    leftP2();
  }
  else if( (xyCoords[2] > xyCoords[0]) && SinglePlayer)
  {
    leftP2();
  }

  if (((getbtnsP1() >> 7) & 0x1) && (!SinglePlayer) )
  {
    downP2();
  }
  else if ( (xyCoords[3] < xyCoords[1]) && SinglePlayer )
  {
    downP2();
  }

  if (((getbtnsP1() >> 8) & 0x1) && (!SinglePlayer) )
    {
      upP2();
    }
  else if( (xyCoords[3] > xyCoords[1]) && SinglePlayer)
  {
    upP2();
  }

}


int bullet1(int timeout)
{
  if(timeout == 0)
    {
      if ( ((getbtnsP1() >> 4) & 0x1) )
      {
        startBullet();
        directionBulletFly = directionBullet;
        return 1;
      }
    }
  return 0;
}

int bullet2(int timeout)
{
  if(timeout == 0)
    {
      if (((getbtnsP1() >> 9) & 0x1) && !(SinglePlayer) )
      {
        startBullet2();
        directionBulletFly2 = directionBullet2;
        return 1;
      }
      else if ( ( (xyCoords[2] == xyCoords[0]) || (xyCoords[3] == xyCoords[1]) ) && SinglePlayer)
      {
        startBullet2();
        directionBulletFly2 = directionBullet2;
        return 1;
      }
    }
  return 0;
}

void game_over(int toggle)
{
    if((xyCoords[0] <= xyCoords[6] && xyCoords[6] <= xyCoords[0] + 7) && ((xyCoords[1] <= xyCoords[7]) && (xyCoords[7] <= xyCoords[1] + 7)))
    {
      w = 0;
      if(!SinglePlayer)
      {
        player2kills++;
      }
      screenChanger = 4;
    }
    else if(player2death() && !SinglePlayer)
    {
      w = 1;
      player1kills++;
      screenChanger = 4;
    }
    else if(player2death() && SinglePlayer)
    {
      currentbotkills++;
      xyCoords[2] = AIspawn[maps][randomLocation()];
      xyCoords[3] = AIspawn[maps][randomLocation() + 4];
      xyCoords[6] = -5;
      xyCoords[7] = -5;
    }
  }

void changeCape (void)
{
  if(cape == 0)
  {
    cape = 1;
  }
  else
  {
    cape = 0;
  }
}

void changeSteps (void)
{
  if(steps == 0)
  {
    steps = 1;
  }
  else
  {
    steps = 0;
  }
}

void startBullet(void)
{
  bulletclear = 0;
  if(directionBullet == 0) //right
  {
    xyCoords[4] = xyCoords[0] + 6;
    xyCoords[5] = xyCoords[1] + 3;
  }
  else if(directionBullet == 1) //left
  {
    xyCoords[4] = xyCoords[0] + 1;
    xyCoords[5] = xyCoords[1] + 3;
  }
  else if(directionBullet == 2) //up
  {
    xyCoords[4] = xyCoords[0] + 4;
    xyCoords[5] = xyCoords[1] + 1;
  }
  else if(directionBullet == 3) //down
  {
    xyCoords[4] = xyCoords[0] + 3;
    xyCoords[5] = xyCoords[1] + 6;
  }
    bulletFly = 1;

}


void flyingBullet(void) //prototype stage
{
  if(bulletFly == 1)
  {
      if(directionBulletFly == 0) //right
      {

        if(rightMovement(4))
          xyCoords[4]++;
          else
            bulletclear = 1;

      }
      else if(directionBulletFly == 1) //left
      {
        if(leftMovement(4))
          xyCoords[4]--;
        else
          bulletclear = 1;
      }
      else if(directionBulletFly == 2) //up
      {
        if(upMovement(4))
          xyCoords[5]--;
        else
          bulletclear = 1;
      }
      else if(directionBulletFly == 3) //down
      {
        if(downMovement(4))
          xyCoords[5]++;
        else
          bulletclear = 1;
      }
      else
      {
        bulletFly = 0;
        bulletclear = 1;
      }
    }
  if(bulletFly2 == 1)
    {
      if(directionBulletFly2 == 0) //right
      {

        if(rightMovement(6))
          xyCoords[6]++;
          else
            bulletclear2 = 1;

      }
      else if(directionBulletFly2 == 1) //left
      {
        if(leftMovement(6))
          xyCoords[6]--;
        else
          bulletclear2 = 1;
      }
      else if(directionBulletFly2 == 2) //up
      {
        if(upMovement(6))
          xyCoords[7]--;
        else
          bulletclear2 = 1;
      }
      else if(directionBulletFly2 == 3) //down
      {
        if(downMovement(6))
          xyCoords[7]++;
        else
          bulletclear2 = 1;
      }
      else
      {
        bulletFly2 = 0;
        bulletclear2 = 1;
      }
    }
  }

//i = player
int rightMovement(int i)
{
  int j;
  if(i > 3)
    j = 8;
  else
    j = 0;
  if(
      (xyCoords[i] + 1 < SCREEN_WIDTH - 8 + j)
      &&
      (
      ( (xyCoords[i] + 8 - j != wallCShapeX1) || !( (wallCShapeY1 - 1 <= xyCoords[i + 1] + 6  - j) && (xyCoords[i + 1] - 1 < wallCShapeY1 + 2) ) ) &&
      ( (xyCoords[i] + 8 - j!= wallCShapeX1 + 13) || !( (wallCShapeY1 + 2 <= xyCoords[i + 1] + 6 - j) && (xyCoords[i + 1] - 1 < wallCShapeY1 + 13) ) ) &&
      ( (xyCoords[i] + 8 -j != wallCShapeX1) || !( (wallCShapeY1 + 12 <= xyCoords[i + 1] + 6 - j) && (xyCoords[i + 1] - 1 < wallCShapeY1 + 15) ) )
      )
      &&
      (
        ( (xyCoords[i] + 8 - j != wallTShapeX1) || !( (wallTShapeY1 - 1 <= xyCoords[i + 1] + 6  - j) && (xyCoords[i + 1] - 1 < wallTShapeY1 + 4) ) ) &&
        ( (xyCoords[i] + 8 - j != wallTShapeX1 + 6) || !( (wallTShapeY1 + 3 <= xyCoords[i + 1] + 6  - j) && (xyCoords[i + 1] - 1 < wallTShapeY1 + 15) ) )
      )
      &&
      (
        ( (xyCoords[i] + 8 - j != wallLShapeX1) || !( (wallLShapeY1 - 1 <= xyCoords[i + 1] + 6  - j) && (xyCoords[i + 1] - 1 < wallLShapeY1 + 4) ) ) &&
        ( (xyCoords[i] + 8 - j != wallLShapeX1 + 11) || !( (wallLShapeY1 + 3 <= xyCoords[i + 1] + 6  - j) && (xyCoords[i + 1] - 1 < wallLShapeY1 + 15) ) )
      )
      &&
      (
        ( (xyCoords[i] + 8 - j != wallCShapeX2) || !( (wallCShapeY2 - 1 <= xyCoords[i + 1] + 6  - j) && (xyCoords[i + 1] - 1 < wallCShapeY2 + 2) ) ) &&
        ( (xyCoords[i] + 8 - j != wallCShapeX2 + 13) || !( (wallCShapeY2 + 2 <= xyCoords[i + 1] + 6  - j) && (xyCoords[i + 1] - 1 < wallCShapeY2 + 13) ) ) &&
        ( (xyCoords[i] + 8 - j != wallCShapeX2) || !( (wallCShapeY2 + 12 <= xyCoords[i + 1] + 6  - j) && (xyCoords[i + 1] - 1 < wallCShapeY2 + 15) ) )
      )
      &&
      (
        ( (xyCoords[i] + 8 - j != wallTShapeX2) || !( (wallTShapeY2 - 1 <= xyCoords[i + 1] + 6  - j) && (xyCoords[i + 1] - 1 < wallTShapeY2 + 4) ) ) &&
        ( (xyCoords[i] + 8 - j != wallTShapeX2 + 6) || !( (wallTShapeY2 + 3 <= xyCoords[i + 1] + 6  - j) && (xyCoords[i + 1] - 1 < wallTShapeY2 + 15) ) )
      )
      &&
      (
        ( (xyCoords[i] + 8 - j != wallLShapeX2) || !( (wallLShapeY2 - 1 <= xyCoords[i + 1] + 6  - j) && (xyCoords[i + 1] - 1 < wallLShapeY2 + 4) ) ) &&
        ( (xyCoords[i] + 8 - j != wallLShapeX2 + 11) || !( (wallLShapeY2 + 3 <= xyCoords[i + 1] + 6  - j) && (xyCoords[i + 1] - 1 < wallLShapeY2 + 15) ) )
      )
  )
    return 1;
  else
    return 0;
}

int leftMovement(int i)
{
  int j;
  if(i > 3)
    j = 8;
  else
    j = 0;
  if(
    (0 < xyCoords[i] - 1)
    &&
    (
    (xyCoords[i] - 1 != wallCShapeX1 + 15) ||
    !( (wallCShapeY1 <= xyCoords[i + 1] + 8 - j) && (xyCoords[i + 1] - 1 < wallCShapeY1 + 15) ) //changed this from rectangle experiment
    )
  &&
  (
    ( (xyCoords[i] - 1 != wallTShapeX1 + 15 ) || !( (wallTShapeY1 - 1 <= xyCoords[i + 1] + 6 - j) && (xyCoords[i + 1] - 1 < wallTShapeY1 + 4) ) ) &&
    ( (xyCoords[i] - 1 != wallTShapeX1 + 8) || !( (wallTShapeY1 + 3 <= xyCoords[i + 1] + 6 - j ) && (xyCoords[i + 1] - 1 < wallTShapeY1 + 15) ) )
  )
  &&
  (
    (xyCoords[i] - 1 != wallLShapeX1 + 15) ||
    !( (wallLShapeY1 <= xyCoords[i + 1] + 8 - j) && (xyCoords[i + 1] - 1 < wallLShapeY1 + 15) )
  )
  &&
  (
    (xyCoords[i] - 1 != wallCShapeX2 + 15) ||
    !( (wallCShapeY2 <= xyCoords[i + 1] + 8 - j) && (xyCoords[i + 1] - 1 < wallCShapeY2 + 15) ) //changed this from rectangle experiment
  )
  &&
  (
    ( (xyCoords[i] - 1 != wallTShapeX2 + 15 ) || !( (wallTShapeY2 - 1 <= xyCoords[i + 1] + 6 - j) && (xyCoords[i + 1] - 1 < wallTShapeY2 + 4) ) ) &&
    ( (xyCoords[i] - 1 != wallTShapeX2 + 8) || !( (wallTShapeY2 + 3 <= xyCoords[i + 1] + 6 - j) && (xyCoords[i + 1] - 1 < wallTShapeY2 + 15) ) )
  )
  &&
  (
    (xyCoords[i] - 1 != wallLShapeX2 + 15) ||
    !( (wallLShapeY2 <= xyCoords[i + 1] + 8 - j) && (xyCoords[i + 1] - 1 < wallLShapeY2 + 15) )
  )
)
    return 1;
  else
    return 0;
}

int downMovement(int i)
{
  int j;
  if(i > 3)
    j = 8;
  else
    j = 0;
  if(
    (xyCoords[i + 1] + 1 < SCREEN_HEIGHT - 8 + j)
    &&
    (
      (xyCoords[i + 1] + 8 - j != wallCShapeY1) && (xyCoords[i + 1] + 8 - j != wallCShapeY1 + 13) ||
      !( (wallCShapeX1 < xyCoords[i] + 8 - j) && (xyCoords[i] - 1 < wallCShapeX1 + 15) )
    )
    &&
    (
      (xyCoords[i + 1] + 8 - j != wallTShapeY1) ||
      !( (wallTShapeX1 < xyCoords[i] + 8 - j) && (xyCoords[i] - 1 < wallTShapeX1 + 15) )
    )
    &&
    (
      (xyCoords[i + 1] + 8 - j != wallLShapeY1) ||
      !( (wallLShapeX1 < xyCoords[i] + 8 - j) && (xyCoords[i] - 1 < wallLShapeX1 + 15) )
    )
    &&
    (
      (xyCoords[i + 1] + 8 - j != wallCShapeY2) && (xyCoords[i + 1] + 8 - j != wallCShapeY2 + 13) ||
      !( (wallCShapeX2 < xyCoords[i] + 8 - j) && (xyCoords[i] - 1 < wallCShapeX2 + 15) )
    )
    &&
    (
      (xyCoords[i + 1] + 8 - j != wallTShapeY2) ||
      !( (wallTShapeX2 < xyCoords[i] + 8 - j) && (xyCoords[i] - 1 < wallTShapeX2 + 15) )
    )
    &&
    (
      (xyCoords[i + 1] + 8 - j != wallLShapeY2) ||
      !( (wallLShapeX2 < xyCoords[i] + 8 - j) && (xyCoords[i] - 1 < wallLShapeX2 + 15) )
    )

  )
    return 1;
  else
    return 0;
}

int upMovement(int i)
{
  int j;
  if(i > 3)
    j = 8;
  else
    j = 0;
  if(
      (0 < xyCoords[i + 1] - 1) &&
      (
        (xyCoords[i + 1] - 1 != wallCShapeY1 + 2) && (xyCoords[i + 1] - 1 != wallCShapeY1 + 15) ||
        !( (wallCShapeX1 < xyCoords[i] + 8 - j) && (xyCoords[i] - 1 < wallCShapeX1 + 15) )
      )
      &&
      (
        ( (xyCoords[i + 1] - 1 != wallTShapeY1 + 4) || !( (wallTShapeX1 < xyCoords[i] + 8 - j) && (xyCoords[i] - 1 < wallTShapeX1 + 6) ) ) &&
        ( (xyCoords[i + 1] - 1 != wallTShapeY1 + 15) || !( (wallTShapeX1 + 6 < xyCoords[i] + 8 - j) && (xyCoords[i] - 1 < wallTShapeX1 + 9) ) )&&
        ( (xyCoords[i + 1] - 1 != wallTShapeY1 + 4) || !( (wallTShapeX1 + 9 < xyCoords[i] + 8 - j) && (xyCoords[i] - 1 < wallTShapeX1 + 15) ) )
      )
      &&
      (
        ( (xyCoords[i + 1] - 1 != wallLShapeY1 + 4) || !( (wallLShapeX1 < xyCoords[i] + 8 - j) && (xyCoords[i] - 1 < wallLShapeX1 + 11) ) ) &&
        ( (xyCoords[i + 1] - 1 != wallLShapeY1 + 15) || !( (wallLShapeX1 + 11 < xyCoords[i] + 8 - j) && (xyCoords[i] - 1 < wallLShapeX1 + 15) ) )
      )
      &&
      (
        (xyCoords[i + 1] - 1 != wallCShapeY2 + 2) && (xyCoords[i + 1] - 1 != wallCShapeY2 + 15) ||
        !( (wallCShapeX2 < xyCoords[i] + 8 - j) && (xyCoords[i] - 1 < wallCShapeX2 + 15) )
      )
      &&
      (
        ( (xyCoords[i + 1] - 1 != wallTShapeY2 + 4) || !( (wallTShapeX2 < xyCoords[i] + 8 - j) && (xyCoords[i] - 1 < wallTShapeX2 + 6) ) ) &&
        ( (xyCoords[i + 1] - 1 != wallTShapeY2 + 15) || !( (wallTShapeX2 + 6 < xyCoords[i] + 8 - j) && (xyCoords[i] - 1 < wallTShapeX2 + 9) ) )&&
        ( (xyCoords[i + 1] - 1 != wallTShapeY2 + 4) || !( (wallTShapeX2 + 9 < xyCoords[i] + 8 - j) && (xyCoords[i] - 1 < wallTShapeX2 + 15) ) )
      )
      &&
      (
        ( (xyCoords[i + 1] - 1 != wallLShapeY2 + 4) || !( (wallLShapeX2 < xyCoords[i] + 8 - j) && (xyCoords[i] - 1 < wallLShapeX2 + 11) ) ) &&
        ( (xyCoords[i + 1] - 1 != wallLShapeY2 + 15) || !( (wallLShapeX2 + 11 < xyCoords[i] + 8 - j) && (xyCoords[i] - 1 < wallLShapeX2 + 15) ) )
      )
    )
    return 1;
  else
    return 0;
}
