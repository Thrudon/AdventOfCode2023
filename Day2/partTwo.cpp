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
    while (getline(file, line))
    {
      Game game(line);
      sum += game.getMinSet().power();
    }
    cout << sum << endl;
  }
  file.close();
  return 0;
}