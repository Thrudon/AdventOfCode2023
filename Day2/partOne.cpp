#include <iostream>
#include <fstream>
using namespace std;

#include "game.h"

int main(int argc, char** argv)
{
  ifstream file("input");
  if (file.is_open())
  {
    unsigned int sum = 0;
    string line;
    Set composition(12, 13, 14);
    while (getline(file, line))
    {
      Game game(line);
      if (game.isValid(composition))
        sum += game.getId();
    }
    cout << sum << endl;
  }
  file.close();
  return 0;
}