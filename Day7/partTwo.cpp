#include <iostream>
#include <fstream>
#include <algorithm>

#include "handTwo.h"

using namespace std;

int main(int argc, char** argv)
{
  vector<HandTwo> hands;

  ifstream file("input");
  if (file.is_open())
  {
    string line;
    while (getline(file, line))
    {
      hands.push_back(HandTwo(line));
    }
  }
  file.close();

  int sum = 0;
  sort(hands.begin(), hands.end());
  for (int i = 0; i < hands.size(); i++)
    sum += (hands[i].getBid() * (i + 1));
  
  cout << sum << endl;
  return 0;
}