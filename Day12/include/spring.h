#pragma once
#include <string>
#include <vector>
#include <map>

#define uint unsigned long long int

using namespace std;

class Spring
{
public:
  Spring(string line);
  uint getArrangementAmt(int groupIdx = -1, int position = 0, int prevMatchPosition = 0);
  void unfold(int nb);

private:
  string _spring;
  vector<int> _groups;
  vector<int> _unknownPos;
  vector<map<int, uint>> memorizedData; // For each group, contains a map of (valid location --> amount of valid configurations)
  void setUnknownPos();
};