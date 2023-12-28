#include <iostream>
#include <fstream>
#include <string>

#include "map.h"

using namespace std;

int main(int argc, char** argv)
{
  Map map(1000000);

  ifstream file("input");
  if (file.is_open())
  {
    string line;
    while (getline(file, line))
    {
      map.addLine(line);
    }
  }
  file.close();

  cout << "Solution: " << map.getShortestPathsLengthSum() << endl;
  return 0;
}