#include "browser.h"

Browser::Browser(vector<int> loop) :
  _loop(loop)
{
  _loopLength = loop[loop.size() - 1];
  _nbLoops = 0;
  _loopPos = 0;
}

uint Browser::getNext()
{
  goToNext();
  return getCurrent();
}

uint Browser::getCurrent()
{
  return ((uint) _loopLength * (uint) _nbLoops) + (uint) _loop[_loopPos];
}

void Browser::goToNext()
{
  _loopPos++;
  if (_loopPos >= _loop.size())
  {
    _loopPos = 0;
    _nbLoops++;
  }
}