#include <iostream>
#include <fstream>
#include <string>

#include "map.h"

using namespace std;

int main(int argc, char** argv)
{
  Map map;

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

  cout << "Solution: " << map.getDistanceToFurthestPoint() << endl;
  return 0;
}