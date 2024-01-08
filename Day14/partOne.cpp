#include <iostream>
#include <fstream>
#include <string>

#include "dish.h"

using namespace std;

int main(int argc, char** argv)
{
  Dish dish;
  ifstream file("input");
  if (file.is_open())
  {
    string line;
    while (getline(file, line))
    {
      dish.addData(line);
    }
  }
  file.close();

  dish.tilt(AXIS::NORTH);
  cout << "Solution: " << dish.getValue() << endl;
  return 0;
}