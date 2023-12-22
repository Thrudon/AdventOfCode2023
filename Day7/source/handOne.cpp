#include <map>
#include <sstream>

#include "handOne.h"

HandOne::HandOne(string line)
{
  cardsString = line.substr(0, line.find_first_of(" "));
  bid = stoi(line.substr(line.find_first_of(" ") + 1));

  for (int i = 0; i < cardsString.size(); i++)
  {
    if (cardsString.substr(i, 1) == "2")
      cards.push_back(CardOne::TWO);
    else if (cardsString.substr(i, 1) == "3")
      cards.push_back(CardOne::THREE);
    else if (cardsString.substr(i, 1) == "4")
      cards.push_back(CardOne::FOUR);
    else if (cardsString.substr(i, 1) == "5")
      cards.push_back(CardOne::FIVE);
    else if (cardsString.substr(i, 1) == "6")
      cards.push_back(CardOne::SIX);
    else if (cardsString.substr(i, 1) == "7")
      cards.push_back(CardOne::SEVEN);
    else if (cardsString.substr(i, 1) == "8")
      cards.push_back(CardOne::EIGHT);
    else if (cardsString.substr(i, 1) == "9")
      cards.push_back(CardOne::NINE);
    else if (cardsString.substr(i, 1) == "T")
      cards.push_back(CardOne::TEN);
    else if (cardsString.substr(i, 1) == "J")
      cards.push_back(CardOne::JACK);
    else if (cardsString.substr(i, 1) == "Q")
      cards.push_back(CardOne::QUEEN);
    else if (cardsString.substr(i, 1) == "K")
      cards.push_back(CardOne::KING);
    else if (cardsString.substr(i, 1) == "A")
      cards.push_back(CardOne::ACE);
  }

  map<CardOne, int> cardsAmt;
  for (int i = 0; i < cards.size(); i++)
  {
    if (cardsAmt.find(cards[i]) != cardsAmt.end())
      cardsAmt[cards[i]]++;
    else
      cardsAmt.insert(pair<CardOne, int>(cards[i], 1));
  }
  int pairAmt = 0;
  int threeOfAKindAmt = 0;
  for (pair<CardOne, int> cardAmt : cardsAmt)
  {
    if (cardAmt.second == 2)
      pairAmt++;
    if (cardAmt.second == 3)
      threeOfAKindAmt++;
    if (cardAmt.second == 4)
    {
      handType = HandType::FourOfAKind;
      return;
    }
    if (cardAmt.second == 5)
    {
      handType = HandType::FiveOfAKind;
      return;
    }
  }
  if (pairAmt == 2)
    handType = HandType::TwoPair;
  else if (pairAmt == 1 && threeOfAKindAmt == 1)
    handType = HandType::FullHouse;
  else if (pairAmt == 1)
    handType = HandType::OnePair;
  else if (threeOfAKindAmt == 1)
    handType = HandType::ThreeOfAKind;
  else
    handType = HandType::HighCard;
}

int HandOne::getBid()
{
  return bid;
}

string HandOne::toString()
{
  stringstream hand;
  hand << "Cards: " << cardsString << " | Bid: " << bid;
  return hand.str();
}