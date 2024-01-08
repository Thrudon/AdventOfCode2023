#include <algorithm>

#include "dish.h"

Dish::Dish()
{}

void Dish::addData(string line)
{
  vector<char> data;
  for (int i = 0; i < line.size(); i++)
    data.push_back(line[i]);
  _data.push_back(data);
}

void Dish::tilt(AXIS axis)
{
  int origI, destI, incrI;
  int origJ, destJ, incrJ;
  switch (axis)
  {
  case AXIS::NORTH:
    origI = 0; destI = _data.size(); incrI = 1;
    origJ = 0; destJ = _data[origI].size(); incrJ = 1;
    break;
  case AXIS::SOUTH:
    origI = _data.size() - 1; destI = -1; incrI = -1;
    origJ = 0; destJ = _data[origI].size(); incrJ = 1;
    break;
  case AXIS::EAST:
    origI = 0; destI = _data.size(); incrI = 1;
    origJ = _data[origI].size() - 1; destJ = -1; incrJ = -1;
    break;
  case AXIS::WEST:
    origI = 0; destI = _data.size(); incrI = 1;
    origJ = 0; destJ = _data[origI].size(); incrJ = 1;
    break;
  }

  for (int i = origI; i != destI; i += incrI)
  {
    for (int j = origJ; j != destJ; j += incrJ)
    {
      if (_data[i][j] == 'O')
      {
        int k;
        switch(axis)
        {
        case AXIS::NORTH:
        case AXIS::SOUTH:
          k = i;
          while (k != origI)
          {
            if (_data[k-incrI][j] == '#')
              break;
            if (_data[k-incrI][j] == '.')
            {
              _data[k][j] = '.';
              _data[k-incrI][j] = 'O';
            }
            k -= incrI;
        }
          break;
        case AXIS::EAST:
        case AXIS::WEST:
          k = j;
          while (k != origJ)
          {
            if (_data[i][k-incrJ] == '#')
              break;
            if (_data[i][k-incrJ] == '.')
            {
              _data[i][k] = '.';
              _data[i][k-incrJ] = 'O';
            }
            k -= incrJ;
          }
          break;
        }
      }
    }
  }
}

int Dish::getValue()
{
  int sum = 0;
  for (int i = 0; i < _data.size(); i++)
  {
    for (int j = 0; j < _data[i].size(); j++)
    {
      if (_data[i][j] == 'O')
        sum += (_data.size() - i);
    }
  }
  return sum;
}

void Dish::spin(int cycleAmt)
{
  bool cycleFound = false;
  int cycles = cycleAmt;
  vector<vector<vector<char>>> reachedStates;
  while (cycles-- > 0)
  {
    tilt(AXIS::NORTH);
    tilt(AXIS::WEST);
    tilt(AXIS::SOUTH);
    tilt(AXIS::EAST);

    if (!cycleFound)
    {
      vector<vector<vector<char>>>::iterator pos = find(reachedStates.begin(), reachedStates.end(), _data);
      if (pos == reachedStates.end())
        reachedStates.push_back(_data);
      else
      {
        cycleFound = true;
        int beforeLoop = pos - reachedStates.begin() - 1;
        int loopLength = reachedStates.end() - pos;
        int endPos = (cycleAmt - beforeLoop) % loopLength;
        _data = reachedStates[beforeLoop + endPos - 1];
        return;
      }
    }
  }
}