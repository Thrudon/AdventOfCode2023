#include <iostream>
#include <fstream>
#include <regex>

#include "converter.h"

using namespace std;

int main(int argc, char** argv)
{
  ifstream file("input");
  Converter converter;
  if (file.is_open())
  {
    string line;

    regex typeRgx("seeds|-soil|-fertilizer|-water|-light|-temperature|-humidity|-location");
    smatch typeMatch;
    string type = "";

    while (getline(file, line))
    {
      if (regex_search(line, typeMatch, typeRgx))
      {
        type = typeMatch.str();
        if (type != "seeds")
        {
          type = type.substr(1);
          continue;
        }
      }

      if (line.empty())
       continue;
      else if (type == "seeds")
        converter.setSeedRanges(line.substr(line.find_first_of(" ") + 1));
      else
        converter.addEntry(type, line);
    }
  }
  file.close();

  converter.sortEntries();
  cout << converter.getMinLocation() << endl;
  return 0;
}