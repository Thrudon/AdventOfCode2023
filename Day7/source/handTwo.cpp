#include <map>
#include <sstream>

#include "handTwo.h"

HandTwo::HandTwo(string line)
{
  cardsString = line.substr(0, line.find_first_of(" "));
  bid = stoi(line.substr(line.find_first_of(" ") + 1));

  for (int i = 0; i < cardsString.size(); i++)
  {
    if (cardsString.substr(i, 1) == "2")
      cards.push_back(CardTwo::TWO);
    else if (cardsString.substr(i, 1) == "3")
      cards.push_back(CardTwo::THREE);
    else if (cardsString.substr(i, 1) == "4")
      cards.push_back(CardTwo::FOUR);
    else if (cardsString.substr(i, 1) == "5")
      cards.push_back(CardTwo::FIVE);
    else if (cardsString.substr(i, 1) == "6")
      cards.push_back(CardTwo::SIX);
    else if (cardsString.substr(i, 1) == "7")
      cards.push_back(CardTwo::SEVEN);
    else if (cardsString.substr(i, 1) == "8")
      cards.push_back(CardTwo::EIGHT);
    else if (cardsString.substr(i, 1) == "9")
      cards.push_back(CardTwo::NINE);
    else if (cardsString.substr(i, 1) == "T")
      cards.push_back(CardTwo::TEN);
    else if (cardsString.substr(i, 1) == "J")
      cards.push_back(CardTwo::JOKER);
    else if (cardsString.substr(i, 1) == "Q")
      cards.push_back(CardTwo::QUEEN);
    else if (cardsString.substr(i, 1) == "K")
      cards.push_back(CardTwo::KING);
    else if (cardsString.substr(i, 1) == "A")
      cards.push_back(CardTwo::ACE);
  }

  map<CardTwo, int> cardsAmt;
  for (int i = 0; i < cards.size(); i++)
  {
    if (cardsAmt.find(cards[i]) != cardsAmt.end())
      cardsAmt[cards[i]]++;
    else
      cardsAmt.insert(pair<CardTwo, int>(cards[i], 1));
  }

  if (cardsAmt.find(CardTwo::JOKER) != cardsAmt.end())
  {
    CardTwo mostPresent = CardTwo::JOKER;
    for (pair<CardTwo, int> cardAmt : cardsAmt)
    {
      if (cardAmt.second == CardTwo::JOKER)
        continue;
      
      if (mostPresent == CardTwo::JOKER || cardAmt.second > cardsAmt.at(mostPresent))
        mostPresent= cardAmt.first;
    }
    if (mostPresent != CardTwo::JOKER)
    {
      cardsAmt.at(mostPresent) += cardsAmt.at(CardTwo::JOKER);
      cardsAmt.erase(CardTwo::JOKER);
    }
  }

  int pairAmt = 0;
  int threeOfAKindAmt = 0;
  for (pair<CardTwo, int> cardAmt : cardsAmt)
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

int HandTwo::getBid()
{
  return bid;
}

string HandTwo::toString()
{
  stringstream hand;
  hand << "Cards: " << cardsString << " | Bid: " << bid;
  return hand.str();
}