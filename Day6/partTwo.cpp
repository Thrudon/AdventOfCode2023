#include <iostream>
#include <fstream>
#include <vector>
#include <regex>
#include <algorithm>

#include "race.h"

using namespace std;

int main(int argc, char** argv)
{
  vector<uint> times;
  vector<uint> distances;

  ifstream file("input");
  if (file.is_open())
  {
    regex numRgx("\\d+");
    smatch numMatch;

    string line;
    
    getline(file, line);
    line.erase(remove_if(line.begin(), line.end(), ::isspace), line.end());
    while (regex_search(line, numMatch, numRgx))
    {
      times.push_back(stoll(numMatch.str()));
      line = numMatch.suffix();
    }

    getline(file, line);
    line.erase(remove_if(line.begin(), line.end(), ::isspace), line.end());
    while (regex_search(line, numMatch, numRgx))
    {
      distances.push_back(stoll(numMatch.str()));
      line = numMatch.suffix();
    }
  }
  file.close();
  
  vector<Race> races;
  for (int i = 0; i < times.size(); i++)
    races.push_back(Race(times[i], distances[i]));
  
  int val = 1;
  for (vector<Race>::iterator race = races.begin(); race != races.end(); race++)
    val *= race->getFasterWaysAmount();

  cout << val << endl;
  return 0;
}