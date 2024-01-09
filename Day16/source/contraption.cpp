#include <algorithm>
#include "contraption.h"

Contraption::Contraption()
{}

void Contraption::addData(string data)
{
  _contraption.push_back(data);
}

int Contraption::getVisitedAmt(coords coord, ORIENTATION orientation)
{
  _visited = _contraption;
  _accessWays.clear();
  initialize(coord, orientation);
  explore();

  int visitedAmt = 0;
  for (int i = 0; i < _visited.size(); i++)
    for (int j = 0; j < _visited.size(); j++)
      if (_visited[i][j] == '#')
        visitedAmt++;

  return visitedAmt;
}

int Contraption::getMostEfficientVisitPath()
{
  int mostEfficient = 0;
  int exploreValue = 0;
  for (int i = 0; i < _contraption.size(); i++)
  {
    exploreValue = getVisitedAmt(coords(i, 0), ORIENTATION::RIGHT);
    mostEfficient = (exploreValue > mostEfficient ? exploreValue : mostEfficient);
    if (i == 0 || i == _contraption.size() - 1)
    {
      for (int j = 0; j < _contraption[i].size(); j++)
      {
        exploreValue = getVisitedAmt(coords(i, j), (i == 0 ? ORIENTATION::DOWN : ORIENTATION::UP));
        mostEfficient = (exploreValue > mostEfficient ? exploreValue : mostEfficient);
      }
    }
    exploreValue = getVisitedAmt(coords(i, _contraption[i].size() - 1), ORIENTATION::LEFT);
    mostEfficient = (exploreValue > mostEfficient ? exploreValue : mostEfficient);
  }
  return mostEfficient;
}

void Contraption::explore()
{
  while (!_paths.empty())
  {
    for (int i = 0; i < _paths.size(); i++)
    {
      switch (_contraption[_paths[i].first.first][_paths[i].first.second])
      {
      case '/':
        _accessWays[_paths[i].first].push_back(_paths[i].second);
        switch (_paths[i].second)
        {
        case ORIENTATION::UP:
          _paths[i].second = ORIENTATION::RIGHT;
          break;
        case ORIENTATION::DOWN:
          _paths[i].second = ORIENTATION::LEFT;
          break;
        case ORIENTATION::LEFT:
          _paths[i].second = ORIENTATION::DOWN;
          break;
        case ORIENTATION::RIGHT:
          _paths[i].second = ORIENTATION::UP;
          break;
        }
        break;
      case '\\':
        _accessWays[_paths[i].first].push_back(_paths[i].second);
        switch (_paths[i].second)
        {
        case ORIENTATION::UP:
          _paths[i].second = ORIENTATION::LEFT;
          break;
        case ORIENTATION::DOWN:
          _paths[i].second = ORIENTATION::RIGHT;
          break;
        case ORIENTATION::LEFT:
          _paths[i].second = ORIENTATION::UP;
          break;
        case ORIENTATION::RIGHT:
          _paths[i].second = ORIENTATION::DOWN;
          break;
        }
        break;
      case '-':
        _accessWays[_paths[i].first].push_back(_paths[i].second);
        switch (_paths[i].second)
        {
        case ORIENTATION::UP:
        case ORIENTATION::DOWN:
          _paths[i].second = ORIENTATION::RIGHT;
          _paths.push_back(pair<coords, ORIENTATION>(_paths[i].first, ORIENTATION::LEFT));
          break;
        }
        break;
      case '|':
        _accessWays[_paths[i].first].push_back(_paths[i].second);
        switch (_paths[i].second)
        {
        case ORIENTATION::LEFT:
        case ORIENTATION::RIGHT:
          _paths[i].second = ORIENTATION::UP;
          _paths.push_back(pair<coords, ORIENTATION>(_paths[i].first, ORIENTATION::DOWN));
          break;
        }
        break;
      }

      bool endWay = false;
      switch(_paths[i].second)
      {
      case ORIENTATION::UP:
        if (_paths[i].first.first == 0)
        {
          _paths.erase(_paths.begin() + i);
          endWay = true;
          break;
        }
        _paths[i].first.first -= 1;
        break;
      case ORIENTATION::DOWN:
        if (_paths[i].first.first == _contraption.size() - 1)
        {
          _paths.erase(_paths.begin() + i);
          endWay = true;
          break;
        }
        _paths[i].first.first += 1;
        break;
      case ORIENTATION::LEFT:
        if (_paths[i].first.second == 0)
        {
          _paths.erase(_paths.begin() + i);
          endWay = true;
          break;
        }
        _paths[i].first.second -= 1;
        break;
      case ORIENTATION::RIGHT:
        if (_paths[i].first.second == _contraption[_paths[i].first.first].size() - 1)
        {
          _paths.erase(_paths.begin() + i);
          endWay = true;
          break;
        }
        _paths[i].first.second += 1;
        break;
      }

      if (endWay)
        continue;
      
      _visited[_paths[i].first.first][_paths[i].first.second] = '#';

      if (_accessWays.find(_paths[i].first) != _accessWays.end())
        if (find(_accessWays[_paths[i].first].begin(), _accessWays[_paths[i].first].end(), _paths[i].second) != _accessWays[_paths[i].first].end())
          _paths.erase(_paths.begin() + i);
    }
  }
}

void Contraption::initialize(coords coord, ORIENTATION orientation)
{
  _paths.push_back(pair<coords, ORIENTATION>(coord, orientation));
  _visited[coord.first][coord.second] = '#';
}