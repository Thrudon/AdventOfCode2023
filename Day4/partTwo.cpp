#include <iostream>
#include <fstream>
#include <utility>

#include "card.h"

using namespace std;

int main(int argc, char** argv)
{
  vector<pair<Card, int>> cards;
  ifstream file("input");
  if (file.is_open())
  {
    unsigned int sum = 0;
    string line;
    while (getline(file, line))
    {
      cards.push_back(pair<Card, int>(Card(line), 1));
    }
  }
  file.close();

  int sum = 0;
  for (unsigned int cardIt = 0; cardIt < cards.size(); cardIt++)
  {
    sum += cards[cardIt].second;
    for (unsigned int score = cards[cardIt].first.getScore(); score > 0; score--)
    {
      cards[cardIt + score].second += cards[cardIt].second;
    }
  }
  cout << sum << endl;
  return 0;
}