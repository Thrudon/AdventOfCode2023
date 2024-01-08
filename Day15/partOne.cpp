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

  int sum = 0;
  for (int i = 0; i < lenses.size(); i++)
    sum += lenses[i].getFullHash();
  cout << "Solution: " << sum << endl;
  return 0;
}