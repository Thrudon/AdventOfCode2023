#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <regex>

using namespace std;

string convLiteralToDigit(string literal);

int main(int argc, char** argv)
{
  ifstream file("input");
  if (file.is_open())
  {
    unsigned int calib = 0;
    string line;
    int numLine = 0;
    while (getline(file, line))
    {
      numLine++;
      bool first = true;
      string firstOccur;
      string otherOccur;
      smatch m;
      regex rgx ("([0-9]|one|two|three|four|five|six|seven|eight|nine)");
      while (regex_search(line, m, rgx)) {
        if (first)
        {
          first = false;
          firstOccur = m.str();
        }
        otherOccur = m.str();

        line = line.substr(m.position() + 1);
      }
      stringstream ss;
      ss << convLiteralToDigit(firstOccur) << convLiteralToDigit(otherOccur);
      calib += stoi(ss.str());
    }
    cout << calib << endl;
  }

  file.close();
  return 0;
}

string convLiteralToDigit(string literal)
{
  if (literal == "one")
    return "1";
  if (literal == "two")
    return "2";
  if (literal == "three")
    return "3";
  if (literal == "four")
    return "4";
  if (literal == "five")
    return "5";
  if (literal == "six")
    return "6";
  if (literal == "seven")
    return "7";
  if (literal == "eight")
    return "8";
  if (literal == "nine")
    return "9";
  return literal;
}