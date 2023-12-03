#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

int main(int argc, char** argv)
{
  ifstream file("input");
  if (file.is_open())
  {
    unsigned int calib = 0;
    string line;
    while (getline(file, line))
    {
      stringstream ss;
      ss << line.at(line.find_first_of("0123456789")) << line.at(line.find_last_of("0123456789"));
      calib += stoi(ss.str());
    }
    cout << calib << endl;
  }

  file.close();
  return 0;
}