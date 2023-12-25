#include <iostream>
#include <fstream>
#include <map>
#include <utility>
#include <string>
#include <regex>

using namespace std;

int main(int argc, char** argv)
{
  string path;
  map<string, pair<string, string>> paths;

  ifstream file("input");
  if (file.is_open())
  {
    regex wordRgx("[a-zA-Z]+");
    smatch wordMatch;
    
    string line;

    getline(file, line);
    path = line;
    while (getline(file, line))
    {
      if (line.empty())
        continue;

      string origin, left, right;
      if (regex_search(line, wordMatch, wordRgx))
      {
        origin = wordMatch.str();
        line = wordMatch.suffix();
      }
      if (regex_search(line, wordMatch, wordRgx))
      {
        left = wordMatch.str();
        line = wordMatch.suffix();
      }
      if (regex_search(line, wordMatch, wordRgx))
      {
        right = wordMatch.str();
        line = wordMatch.suffix();
      }
      paths.insert(pair<string, pair<string, string>>(origin, pair<string, string>(left, right)));
    }
  }
  file.close();

  int moves = 0;
  int pathIt = 0;
  string current = "AAA";
  while (current != "ZZZ")
  {
    // cout << path.substr(pathIt, 1) << " | " << current << " - " << paths.at(current).first << " : " << paths.at(current).second << " | " << moves << endl;
    if (path.substr(pathIt, 1) == "L")
      current = paths.at(current).first;
    else
      current = paths.at(current).second;

    pathIt = ++pathIt >= path.size() ? 0 : pathIt;

    moves++;
  }

  cout << moves << endl;

  return 0;
}