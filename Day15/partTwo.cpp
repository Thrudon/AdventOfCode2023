#include <iostream>
#include <fstream>
#include <string>

#include "lens.h"

using namespace std;

int main(int argc, char** argv)
{
  vector<Lens> lenses;
  ifstream file("input");
  if (file.is_open())
  {
    string line;
    while (getline(file, line))
    {
      while (!line.empty())
      {
        lenses.push_back(Lens(line.find_first_of(',') != string::npos ? line.substr(0, line.find_first_of(',')) : line));
        line = line.find_first_of(',') == string::npos ? "" : line.substr(line.find_first_of(',') + 1);
      }
    }
  }
  file.close();

  cout << "Solution: " << Lens::getPower() << endl;
  return 0;
}