#include <iostream>
#include <regex>
#include <algorithm>

#include "card.h"

Card::Card(string line)
{
  id = stoi(line.substr(line.find_first_of(" ") + 1, line.find_first_of(":") - line.find_first_not_of(" ") + 1));
  line = line.substr(line.find_first_of(":") + 2);

  regex numbersRgx("[0-9]+");
  smatch match;

  string winning = line.substr(0, line.find_first_of(("|")));
  while (regex_search(winning, match, numbersRgx))
  {
    winningNumbers.push_back(stoi(match.str()));
    winning = match.suffix();
  }
  sort(winningNumbers.begin(), winningNumbers.end());

  line = line.substr(line.find_first_of("|") + 2);
  while (regex_search(line, match, numbersRgx))
  {
    playerNumbers.push_back(stoi(match.str()));
    line = match.suffix();
  }
  sort(playerNumbers.begin(), playerNumbers.end());
}

unsigned int Card::getScore()
{
  unsigned int score = 0;
  
  unsigned int playerNumberIt = 0;
  unsigned int winningNumberIt = 0;
  while (playerNumberIt < playerNumbers.size())
  {
    while (winningNumberIt < winningNumbers.size())
    {
      if (playerNumbers[playerNumberIt] == winningNumbers[winningNumberIt])
      {
        matchingNumbers.push_back(playerNumbers[playerNumberIt]);
        score++;
        break;
      }
      else if (playerNumbers[playerNumberIt] < winningNumbers[winningNumberIt])
      {
        break;
      }
      winningNumberIt++;
    }
    playerNumberIt++;
  }
  return score;
}

string Card::toString()
{
  string card;
  card += "Card ";
  card += to_string(id);
  card += ":";
  for (int winningNumber : winningNumbers)
  {
    card += " ";
    card += to_string(winningNumber);
  }
  card += " |";
  for (int playerNumber : playerNumbers)
  {
    card += " ";
    card += to_string(playerNumber);
  }
  card += " -";
  for (int matchingNumber : matchingNumbers)
  {
    card += " ";
    card += to_string(matchingNumber);
  }
  return card;
}