#include <iostream>
#include <fstream>
#include <vector>
#include <regex>
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
    for (unsigned int i = 0; i < lines.size(); i++)
    {
      int pos = 0;
      string line = lines[i];
      while (regex_search(line, numMatch, numRgx))
      {
        bool isValid = false;

        // ### Check previous line
        if (i > 0)
        {
          // ### Check previous character
          if (numMatch.position() > 0)
          {
            string symString = lines[i-1].substr(numMatch.position() - 1 + pos, 1);
            if (regex_search(symString, symMatch, symRgx))
              isValid = true;
          }
          // ### Check next character
          if (numMatch.position() + numMatch.str().size() < line.size())
          {
            string symString = lines[i-1].substr(numMatch.position() + numMatch.str().size() + pos, 1);
            if (regex_search(symString, symMatch, symRgx))
              isValid = true;
          }
          // ### Check same position character(s)
          string symString = lines[i-1].substr(numMatch.position() + pos, numMatch.str().size());
          if (regex_search(symString, symMatch, symRgx))
            isValid = true;
        }

        // ### Check next line
        if (i < lines.size() - 1)
        {
          // ### Check previous character
          if (numMatch.position() > 0)
          {
            string symString = lines[i+1].substr(numMatch.position() - 1 + pos, 1);
            if (regex_search(symString, symMatch, symRgx))
              isValid = true;
          }
          // ### Check next character
          if (numMatch.position() + numMatch.str().size() < line.size())
          {
            string symString = lines[i+1].substr(numMatch.position() + numMatch.str().size() + pos, 1);
            if (regex_search(symString, symMatch, symRgx))
              isValid = true;
          }
          // ### Check same position character(s)
          string symString = lines[i+1].substr(numMatch.position() + pos, numMatch.str().size());
          if (regex_search(symString, symMatch, symRgx))
            isValid = true;
        }

        // ### Check current line
        // ### Check previous character
        if (numMatch.position() > 0)
        {
          string symString = lines[i].substr(numMatch.position() - 1 + pos, 1);
          if (regex_search(symString, symMatch, symRgx))
            isValid = true;
        }
        // ### Check next character
        if (numMatch.position() + numMatch.str().size() < line.size())
        {
          string symString = lines[i].substr(numMatch.position() + numMatch.str().size() + pos, 1);
          if (regex_search(symString, symMatch, symRgx))
            isValid = true;
        }

        if (isValid)
          sum += stoi(numMatch.str());
        
        line = numMatch.suffix();
        pos += numMatch.position() + numMatch.str().size();
      }
    }
    cout << sum << endl;
  }
  file.close();
  return 0;
}