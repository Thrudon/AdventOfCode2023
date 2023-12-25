#pragma once
#include <vector>

#define uint unsigned long long int

using namespace std;

class Browser
{
public:
  Browser(vector<int> loop);
  uint getNext();
  uint getCurrent();

private:
  int _loopLength;
  int _nbLoops;
  int _loopPos;
  vector<int> _loop;

  void goToNext();
};