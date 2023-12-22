#pragma once

#include <string>
#include <vector>

#include "common.h"

using namespace std;

enum CardOne
{
  TWO = 0,
  THREE,
  FOUR,
  FIVE,
  SIX,
  SEVEN,
  EIGHT,
  NINE,
  TEN,
  JACK,
  QUEEN,
  KING,
  ACE
};

class HandOne
{
public:
  HandOne(string line);
  int getBid();
  string toString();

private:
  string cardsString;
  vector<CardOne> cards;
  int bid;
  HandType handType;

  friend bool operator<(const HandOne &lhs, const HandOne &rhs)
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