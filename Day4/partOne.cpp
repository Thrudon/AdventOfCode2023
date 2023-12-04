#include <iostream>
#include <fstream>
#include <cmath>

#include "card.h"

using namespace std;

int main(int argc, char** argv)
{
  ifstream file("input");
  if (file.is_open())
  {
    unsigned int sum = 0;
    string line;
    while (getline(file, line))
    {
      Card card(line);
      unsigned int score = card.getScore();
      score = score ? pow(2, score - 1) : score;
      sum += score;
    }
    cout << sum << endl;
  }
  file.close();
  return 0;
}