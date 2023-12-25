#include <iostream>
#include <fstream>
#include <string>

#include "sequence.h"

using namespace std;

int main(int argc, char** argv)
{
  vector<Sequence> seqs;

  ifstream file("input");
  if (file.is_open())
  {
    string line;
    while (getline(file, line))
    {
      seqs.push_back(Sequence(line));
    }
  }
  file.close();

  int sum = 0;
  for (int i = 0; i < seqs.size(); i++)
    sum += seqs[i].getNext();
  
  cout << "Solution: " << sum << endl;
  return 0;
}