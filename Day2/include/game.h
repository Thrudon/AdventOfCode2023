#pragma once

#include <string>
#include <vector>
using namespace std;

#include "set.h"

class Game
{
  unsigned int id;
  vector<Set> sets;

public:
  Game(string line);
  unsigned int getId();
  bool isValid(Set composition);
  string toString();
  Set getMinSet();
};