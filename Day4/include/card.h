#pragma once

using namespace std;

#include <string>
#include <vector>

class Card
{
public:
  Card(string line);
  unsigned int getScore();
  string toString();

private:
  unsigned int id;
  vector<int> winningNumbers;
  vector<int> playerNumbers;
  vector<int> matchingNumbers;
};