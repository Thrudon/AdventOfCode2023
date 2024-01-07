#include "valley.h"

Valley::Valley(int smudgeAmt) :
  _symmetryIdx(0),
  _axis(AXIS::NONE),
  _smudgeAmt(smudgeAmt)
{}

void Valley::addData(string line)
{
  _rows.push_back(line);
  if (_cols.empty())
    for (int i = 0; i < line.size(); i++)
      _cols.push_back(line.substr(i, 1));
  else
    for (int i = 0; i < line.size(); i++)
      _cols[i].append(line.substr(i, 1));
}

int Valley::getValue()
{
  findSymmetry(AXIS::HORIZONTAL);
  if (_axis == AXIS::NONE)
    findSymmetry(AXIS::VERTICAL);
  
  return _symmetryIdx * _axis;
}

void Valley::findSymmetry(AXIS axis)
{
  if (axis == AXIS::NONE)
    return;
  
  vector<string> vect = (axis == AXIS::HORIZONTAL ? _rows : _cols);
  bool isSymmetric = false;
  for (int i = 0; i < vect.size() - 1; i++)
  {
    int smudgeAmt = _smudgeAmt;
    if (areSimilar(vect[i], vect[i+1], smudgeAmt))
    {
      isSymmetric = true;
      for (int j = 1; j <= i; j++)
      {
        if (i+1 + j >= vect.size())
          break;
        
        if (!areSimilar(vect[i - j], vect[i+1 + j], smudgeAmt))
        {
          isSymmetric = false;
          break;
        }
      }
      if (smudgeAmt == 0 && isSymmetric)
      {
        _symmetryIdx = i + 1;
        _axis = axis;
        return;
      }
    }
  }
}

bool Valley::areSimilar(string& line1, string& line2, int& smudgeAmt)
{
  for (int i = 0; i < line1.size(); i++)
  {
    if (line1[i] != line2[i] && smudgeAmt-- == 0)
      return false;
  }
  return true;
}