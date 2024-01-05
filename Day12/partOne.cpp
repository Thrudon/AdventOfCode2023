#include <iostream>
#include <fstream>
#include <string>

#include "spring.h"

using namespace std;

int main(int argc, char** argv)
{
  vector<Spring> springs;

  ifstream file("input");
  if (file.is_open())
  {
    string line;
    while (getline(file, line))
    {
      springs.push_back(Spring(line));
    }
  }
  file.close();

  int sum = 0;
  for (int i = 0; i < springs.size(); i++)
    sum += springs[i].getArrangementAmt();

  cout << "Solution: " << sum << endl;
  return 0;
}