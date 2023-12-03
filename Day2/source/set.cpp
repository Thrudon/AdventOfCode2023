#include "set.h"

Set::Set(unsigned int _red = 0, unsigned int _green = 0, unsigned int _blue = 0) :
  red(_red),
  green(_green),
  blue(_blue)
{}

bool Set::isValid(Set composition)
{
  return (red <= composition.red && green <= composition.green && blue <= composition.blue);
}

unsigned int Set::power()
{
  return (red * green * blue);
}