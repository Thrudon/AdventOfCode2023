#include <iostream>
#include <fstream>
#include <string>

#include "valley.h"

using namespace std;

int main(int argc, char** argv)
{
  vector<Valley> valleys;

  ifstream file("input");
  if (file.is_open())
  {
    Valley* valley = new Valley(1);
    string line;
    while (getline(file, line))
    {
      if (line.empty())
      {
        valleys.push_back(*valley);
        valley = new Valley(1);

        continue;
      }

      valley->addData(line);
    }
    valleys.push_back(*valley);
  }
  file.close();

  int sum = 0;

  for (vector<Valley>::iterator valleyIt = valleys.begin(); valleyIt != valleys.end(); ++valleyIt)
    sum += (*valleyIt).getValue();

  cout << "Solution: " << sum << endl;
  return 0;
}