#include <iostream>

#include "lens.h"

map<int, vector<pair<string, int>>> Lens::_lens = map<int, vector<pair<string, int>>>();

Lens::Lens(string entry) :
  _data(entry)
{
  int opPos = _data.find_first_of("=-");
  if (opPos == string::npos)
    return;

  _label = _data.substr(0, opPos);
  _hashVal = hash(_label);
  bool updated = false;

  switch (_data[opPos])
  {
  case '=':
    _focalLength = stoi(_data.substr(opPos + 1));
    for (vector<pair<string, int>>::iterator lensIt = _lens[_hashVal].begin(); lensIt != _lens[_hashVal].end(); ++lensIt)
    {
      if (lensIt->first == _label)
      {
        updated = true;
        lensIt->second = _focalLength;
        break;
      }
    }
    if (!updated)
      _lens[_hashVal].push_back(pair<string, int>(_label, _focalLength));
    break;
  case '-':
    for (vector<pair<string, int>>::iterator lensIt = _lens[_hashVal].begin(); lensIt != _lens[_hashVal].end(); ++lensIt)
    {
      if (lensIt->first == _label)
      {
        _lens[_hashVal].erase(lensIt);
        break;
      }
    }
    break;
  }
}

int Lens::getFullHash()
{
  return hash(_data);
}

int Lens::hash(string data)
{
  int hash = 0;
  for (int i = 0; i < data.size(); i++)
  {
    hash += data[i];
    hash *= 17;
    hash %= 256;
  }
  return hash;
}

int Lens::getPower()
{
  int power = 0;
  for (map<int, vector<pair<string, int>>>::iterator lensIt = _lens.begin(); lensIt != _lens.end(); ++lensIt)
    for (int i = 0; i < lensIt->second.size(); i++)
      power += (lensIt->first + 1) * (i + 1) * lensIt->second[i].second;
  return power;
}