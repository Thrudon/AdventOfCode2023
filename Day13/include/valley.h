#pragma once
#include <string>
#include <vector>

#define uint unsigned long long int

using namespace std;

enum AXIS
{
  NONE = 0,
  VERTICAL = 1,
  HORIZONTAL = 100
};

class Valley
{
public:
  Valley(int smudgeAmt = 0);
  void addData(string line);
  int getValue();

private:
  vector<string> _rows;
  vector<string> _cols;

  int _symmetryIdx;
  AXIS _axis;
  int _smudgeAmt;

  void findSymmetry(AXIS axis);
  bool areSimilar(string& line1, string& line2, int& smudgeAmt);
};