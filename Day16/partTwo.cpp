#include <iostream>
#include <fstream>
#include <string>

#include "contraption.h"

using namespace std;

int main(int argc, char** argv)
{
  Contraption contraption;
  ifstream file("input");
  if (file.is_open())
  {
    string line;
    while (getline(file, line))
    {
      contraption.addData(line);
    }
  }
  file.close();

  cout << "Solution: " << contraption.getMostEfficientVisitPath() << endl;
  return 0;
}