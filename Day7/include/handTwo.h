#pragma once

#include <string>
#include <vector>

#include "common.h"

using namespace std;

enum CardTwo
{
  JOKER = 0,
  TWO,
  THREE,
  FOUR,
  FIVE,
  SIX,
  SEVEN,
  EIGHT,
  NINE,
  TEN,
  QUEEN,
  KING,
  ACE
};

class HandTwo
{
public:
  HandTwo(string line);
  int getBid();
  string toString();

private:
  string cardsString;
  vector<CardTwo> cards;
  int bid;
  HandType handType;

  friend bool operator<(const HandTwo &lhs, const HandTwo &rhs)
  {
    if (lhs.handType < rhs.handType)
      return true;
    else if (lhs.handType > rhs.handType)
      return false;

    for (int i = 0; i < lhs.cards.size(); i++)
    {
      if (lhs.cards[i] < rhs.cards[i])
        return true;
      else if (lhs.cards[i] > rhs.cards[i])
        return false;
    }
    return true;
  }
};