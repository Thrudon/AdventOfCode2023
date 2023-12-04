#include <iostream>
#include <fstream>
#include <vector>
#include <regex>
#include <map>
#include <utility>
using namespace std;

int main(int argc, char** argv)
{
  ifstream file("input");
  if (file.is_open())
  {
    unsigned int sum = 0;
    string line;
    vector<string> lines;
    while (getline(file, line))
    {
      lines.push_back(line);
    }
    regex numRgx("([0-9]+)");
    regex symRgx("[^.a-zA-Z0-9]");
    smatch numMatch;
    smatch symMatch;

    map<pair<pair<int, int>, string>, vector<int>> parts;
    for (unsigned int i = 0; i < lines.size(); i++)
    {
      int pos = 0;
      string line = lines[i];
      while (regex_search(line, numMatch, numRgx))
      {
        // ### Check previous line
        if (i > 0)
        {
          // ### Check previous character
          if (numMatch.position() > 0)
          {
            string symString = lines[i-1].substr(numMatch.position() - 1 + pos, 1);
            if (regex_search(symString, symMatch, symRgx))
              parts[pair<pair<int, int>, string>(pair<int, int>(i, numMatch.position() - 1 + pos + symMatch.position() + 1), symString)].push_back(stoi(numMatch.str()));
          }
          // ### Check next character
          if (numMatch.position() + numMatch.str().size() < line.size())
          {
            string symString = lines[i-1].substr(numMatch.position() + numMatch.str().size() + pos, 1);
            if (regex_search(symString, symMatch, symRgx))
              parts[pair<pair<int, int>, string>(pair<int, int>(i, numMatch.position() + numMatch.str().size() + pos + symMatch.position() + 1), symString)].push_back(stoi(numMatch.str()));
          }
          // ### Check same position character(s)
          string symString = lines[i-1].substr(numMatch.position() + pos, numMatch.str().size());
          while (regex_search(symString, symMatch, symRgx))
          {
            parts[pair<pair<int, int>, string>(pair<int, int>(i, numMatch.position() + pos + symMatch.position() + 1), symMatch.str())].push_back(stoi(numMatch.str()));
            symString = symString.substr(symMatch.position() + 1);
          }
        }

        // ### Check next line
        if (i < lines.size() - 1)
        {
          // ### Check previous character
          if (numMatch.position() > 0)
          {
            string symString = lines[i+1].substr(numMatch.position() - 1 + pos, 1);
            if (regex_search(symString, symMatch, symRgx))
              parts[pair<pair<int, int>, string>(pair<int, int>(i+2, numMatch.position() - 1 + pos + symMatch.position() + 1), symString)].push_back(stoi(numMatch.str()));
          }
          // ### Check next character
          if (numMatch.position() + numMatch.str().size() < line.size())
          {
            string symString = lines[i+1].substr(numMatch.position() + numMatch.str().size() + pos, 1);
            if (regex_search(symString, symMatch, symRgx))
              parts[pair<pair<int, int>, string>(pair<int, int>(i+2, numMatch.position() + numMatch.str().size() + pos + symMatch.position() + 1), symString)].push_back(stoi(numMatch.str()));
          }
          // ### Check same position character(s)
          string symString = lines[i+1].substr(numMatch.position() + pos, numMatch.str().size());
          while (regex_search(symString, symMatch, symRgx))
          {
            parts[pair<pair<int, int>, string>(pair<int, int>(i+2, numMatch.position() + pos + symMatch.position() + 1), symMatch.str())].push_back(stoi(numMatch.str()));
            symString = symString.substr(symMatch.position() + 1);
          }
        }

        // ### Check current line
        // ### Check previous character
        if (numMatch.position() > 0)
        {
          string symString = lines[i].substr(numMatch.position() - 1 + pos, 1);
          if (regex_search(symString, symMatch, symRgx))
            parts[pair<pair<int, int>, string>(pair<int, int>(i+1, numMatch.position() - 1 + pos + symMatch.position() + 1), symString)].push_back(stoi(numMatch.str()));
        }
        // ### Check next character
        if (numMatch.position() + numMatch.str().size() < line.size())
        {
          string symString = lines[i].substr(numMatch.position() + numMatch.str().size() + pos, 1);
          if (regex_search(symString, symMatch, symRgx))
            parts[pair<pair<int, int>, string>(pair<int, int>(i+1, numMatch.position() + numMatch.str().size() + pos + symMatch.position() + 1), symString)].push_back(stoi(numMatch.str()));
        }
        line = numMatch.suffix();
        pos += numMatch.position() + numMatch.str().size();
      }
    }

    for (auto part : parts)
    {
      if (part.first.second == "*")
        if (part.second.size() > 1)
          sum += (part.second.at(0) * part.second.at(1));
    }
    cout << sum << endl;
  }
  file.close();
  return 0;
}