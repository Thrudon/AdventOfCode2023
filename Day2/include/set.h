#pragma once

class Set
{
public:
  unsigned int red;
  unsigned int green;
  unsigned int blue;

  Set(unsigned int _red, unsigned int _green, unsigned int _blue);
  bool isValid(Set composition);
  unsigned int power();
};