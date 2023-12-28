#include <cmath>

#include "map.h"

Map::Map(int expansionRate) :
  _expansionRate(expansionRate)
{}

void Map::addLine(string line)
{
  map.push_back(line);
}

void Map::expandUniverse()
{
  // Locate empty columns
  for (int i = 0; i < map.size(); i++)
  {
    for (int j = 0; j < map[i].size(); j++)
    {
      if (emptyColumns.size() <= j)
        emptyColumns.push_back(true);
      if (map[i][j] != '.')
        emptyColumns[j] = false;
    }
  }

  // Double empty lines and record galaxy locations
  bool emptyLine;
  for (int i = 0; i < map.size(); i++)
  {
    emptyLine = true;
    for (int j = 0; j < map[i].size(); j++)
    {
      if (map[i][j] != '.')
      {
        emptyLine = false;
        galaxyLocs.push_back(pair<int, int>(i, j));
      }
    }
    emptyRows.push_back(emptyLine);
  }
}

uint Map::getShortestPathsLengthSum()
{
  expandUniverse();

  uint sum = 0;
  for (int i = 0; i < galaxyLocs.size(); i++)
    for (int j = i + 1; j < galaxyLocs.size(); j++)
      sum += getShortestPathLength(i, j);
  return sum;
}

uint Map::getShortestPathLength(int galaxyOne, int galaxyTwo)
{
  int x1 = galaxyLocs[galaxyOne].first > galaxyLocs[galaxyTwo].first ? galaxyLocs[galaxyTwo].first : galaxyLocs[galaxyOne].first;
  int x2 = galaxyLocs[galaxyOne].first > galaxyLocs[galaxyTwo].first ? galaxyLocs[galaxyOne].first : galaxyLocs[galaxyTwo].first;

  int y1 = galaxyLocs[galaxyOne].second > galaxyLocs[galaxyTwo].second ? galaxyLocs[galaxyTwo].second : galaxyLocs[galaxyOne].second;
  int y2 = galaxyLocs[galaxyOne].second > galaxyLocs[galaxyTwo].second ? galaxyLocs[galaxyOne].second : galaxyLocs[galaxyTwo].second;

  uint dist = 0;

  for (int i = x1; i < x2; i++)
  {
    if (emptyRows[i])
      dist += _expansionRate;
    else
      dist++;
  }
  for (int j = y1; j < y2; j++)
  {
    if (emptyColumns[j])
      dist += _expansionRate;
    else
      dist++;
  }
  return dist;
}