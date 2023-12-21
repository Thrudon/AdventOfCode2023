#include "race.h"

Race::Race(uint _time, uint _record) :
  time(_time),
  record(_record)
{}

uint Race::getFasterWaysAmount()
{
  uint amount = 1;  
  for (uint heldTime = 1; heldTime * (time - heldTime) < record; heldTime++)
    amount++;
  for (uint heldTime = time - 1; heldTime * (time - heldTime) < record; heldTime--)
    amount++;

  return time - amount;
}