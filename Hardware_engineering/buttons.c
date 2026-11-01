#include <pic32mx.h>
#include <stdint.h>
#include "dataO.h"

int getbtnsP1(void)
{
  int BTN = (PORTE & 0x00ff) | ((PORTD & 0x3) << 8) | ((PORTD & 0xe0) << 5);
  return BTN;
}
