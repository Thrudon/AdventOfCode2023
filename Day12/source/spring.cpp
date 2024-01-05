#include <iostream>
#include <sstream>
#include <regex>

#include "spring.h"

Spring::Spring(string line)
{
  _spring = line.substr(0, line.find_first_of(' '));
  line = line.substr(line.find_first_of(' ') + 1);
  line.append(",");
  while (!line.empty())
  {
    _groups.push_back(stoi(line.substr(0, line.find_first_of(','))));
    line = line.substr(line.find_first_of(',') + 1);
  }

  setUnknownPos();
}

uint Spring::getArrangementAmt(int groupIdx, int position, int prevMatchPosition)
{
  uint sum = 0;
  
  int nextGroupsSize = 0;
  for (int i = groupIdx + 1; i < _groups.size(); i++)
    nextGroupsSize += _groups[i] + (i == 0 ? 0 : 1);
  int lastOption = _spring.size() - nextGroupsSize;

  if (groupIdx < 0)
  {
    for (int i = 0; i < _groups.size(); i++)
      memorizedData.push_back(map<int, uint>());

    for (int i = 0; i <= lastOption; i++)
    {
      if (_spring.find_first_of('#') != string::npos && _spring.find_first_of('#') < i)
        break;
      sum += getArrangementAmt(groupIdx + 1, i);
    }
    return sum;
  }

  if (memorizedData[groupIdx].find(position) != memorizedData[groupIdx].end())
    return memorizedData[groupIdx][position];
  
  memorizedData[groupIdx][position] = 0;

  stringstream ssHash;
  ssHash << "([?#]{" << _groups[groupIdx] << "})";
  if (groupIdx >= _groups.size() - 1)
    ssHash << "(?:[^#]*$)";

  string hash = ssHash.str();
  regex rgxHash(hash);
  smatch matchHash;

  string spring = _spring.substr(position);
  if (!regex_search(spring, matchHash, rgxHash))
    return 0;

  if ((position + matchHash.position() - 1 >= 0 && _spring[position + matchHash.position() - 1] == '#') ||
      (position + matchHash.position() + _groups[groupIdx] < _spring.size() && _spring[position + matchHash.position() + _groups[groupIdx]] == '#'))
    return 0;

  if (groupIdx > 0 && _spring.substr(prevMatchPosition + _groups[groupIdx - 1]).find_first_of('#') != string::npos && prevMatchPosition + _groups[groupIdx - 1] + _spring.substr(prevMatchPosition + _groups[groupIdx - 1]).find_first_of('#') < position + matchHash.position())
    return 0;

  if (groupIdx == _groups.size() - 1)
  {
    memorizedData[groupIdx][position + matchHash.position()] = 1;
    return memorizedData[groupIdx][position];
  }

  for (int i = position + matchHash.position() + _groups[groupIdx]; i <= lastOption; i++)
  {
    if (_spring.substr(position + matchHash.position() + _groups[groupIdx]).find_first_of('#') != string::npos &&
        _spring.substr(position + matchHash.position() + _groups[groupIdx]).find_first_of('#') + position + matchHash.position() + _groups[groupIdx] < i)
      break;
    sum += getArrangementAmt(groupIdx + 1, i + 1, position + matchHash.position());
  }
  memorizedData[groupIdx][position + matchHash.position()] = sum;
  return memorizedData[groupIdx][position];
}

void Spring::unfold(int nb)
{
  string spring = _spring;
  vector<int> groups = _groups;
  for (int i = 0; i < nb - 1; i++)
  {
    _spring.append("?");
    _spring.append(spring);
    for (int j = 0; j < groups.size(); j++)
      _groups.push_back(groups[j]);
  }

  setUnknownPos();
}

void Spring::setUnknownPos()
{
  _unknownPos.clear();
  for (int i = 0; i < _spring.size(); i++)
    if (_spring[i] == '?')
      _unknownPos.push_back(i);
}