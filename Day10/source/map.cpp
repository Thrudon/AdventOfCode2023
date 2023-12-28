#include <iostream>
#include <algorithm>

#include "map.h"

Map::Map()
{}

void Map::addLine(string line)
{
  for (int i = 0; i < line.size(); i++)
    if (line[i] == 'S')
      animalLoc = pair<int, int>(map.size(), i);
  map.push_back(line);
}

int Map::getDistanceToFurthestPoint()
{
  pathLocs.push_back(animalLoc);
  int moves = 1;
  getFirstLocs();

  while (currentLocs[0] != currentLocs[1])
  {
    pathLocs.push_back(currentLocs[0]);
    pathLocs.push_back(currentLocs[1]);
    goToNextLocs();
    moves++;
  }
  pathLocs.push_back(currentLocs[0]);

  return moves;
}

int Map::getNbTilesInsidePath()
{
  int insideTiles = 0;
  char entryWay = '.';

  int bordersPassed = 0;
  for (int i = 0; i < map.size(); i++)
  {
    for (int j = 0; j < map[i].size(); j++)
    {
      if (find(pathLocs.begin(), pathLocs.end(), pair<int, int>(i, j)) != pathLocs.end())
      {
        if (find(pathLocs.begin(), pathLocs.end(), pair<int, int>(i, j - 1)) == pathLocs.end())
        {
          bordersPassed++;
          entryWay = map[i][j];
        }
        else
        {
          if (map[i][j] == 'F' || map[i][j] == 'L' || map[i][j] == '|')
          {
            bordersPassed++;
            entryWay = map[i][j];
          }
          else if ((entryWay == 'F' && map[i][j] == '7') || (entryWay == 'L' && map[i][j] == 'J'))
            bordersPassed--;
        }
      }
      else if (bordersPassed % 2 != 0)
        insideTiles++;
    }
    bordersPassed = 0;
  }

  return insideTiles;
}

void Map::goToNextLocs()
{
  for (int i = 0; i < currentLocs.size(); i++)
  {
    pair<int, int> newLoc;
    switch(map[currentLocs[i].first][currentLocs[i].second])
    {
    case '-':
      if (prevLocs[i].second < currentLocs[i].second)
        newLoc = pair<int, int>(currentLocs[i].first, currentLocs[i].second + 1);
      else
        newLoc = pair<int, int>(currentLocs[i].first, currentLocs[i].second - 1);
      break;
    case '|':
      if (prevLocs[i].first < currentLocs[i].first)
        newLoc = pair<int, int>(currentLocs[i].first + 1, currentLocs[i].second);
      else
        newLoc = pair<int, int>(currentLocs[i].first - 1, currentLocs[i].second);
      break;
    case 'L':
      if (prevLocs[i].first < currentLocs[i].first)
        newLoc = pair<int, int>(currentLocs[i].first, currentLocs[i].second + 1);
      else
        newLoc = pair<int, int>(currentLocs[i].first - 1, currentLocs[i].second);
      break;
    case 'F':
      if (prevLocs[i].first > currentLocs[i].first)
        newLoc = pair<int, int>(currentLocs[i].first, currentLocs[i].second + 1);
      else
        newLoc = pair<int, int>(currentLocs[i].first + 1, currentLocs[i].second);
      break;
    case '7':
      if (prevLocs[i].first > currentLocs[i].first)
        newLoc = pair<int, int>(currentLocs[i].first, currentLocs[i].second - 1);
      else
        newLoc = pair<int, int>(currentLocs[i].first + 1, currentLocs[i].second);
      break;
    case 'J':
      if (prevLocs[i].first < currentLocs[i].first)
        newLoc = pair<int, int>(currentLocs[i].first, currentLocs[i].second - 1);
      else
        newLoc = pair<int, int>(currentLocs[i].first - 1, currentLocs[i].second);
      break;
    }
    prevLocs[i] = currentLocs[i];
    currentLocs[i] = newLoc;
  }
}

void Map::getFirstLocs()
{
  prevLocs.push_back(animalLoc);
  prevLocs.push_back(animalLoc);

  if (animalLoc.first == 0 && animalLoc.second == 0)
  {
    currentLocs.push_back(pair<int, int>(0, 1));
    currentLocs.push_back(pair<int, int>(1, 0));
  }
  else if (animalLoc.first == 0 && animalLoc.second == map[animalLoc.first].size() - 1)
  {
    currentLocs.push_back(pair<int, int>(0, animalLoc.second - 1));
    currentLocs.push_back(pair<int, int>(1, animalLoc.second));
  }
  else if (animalLoc.first == map.size() - 1 && animalLoc.second == 0)
  {
    currentLocs.push_back(pair<int, int>(animalLoc.first - 1, 0));
    currentLocs.push_back(pair<int, int>(animalLoc.first, 1));
  }
  else if (animalLoc.first == map.size() - 1 && animalLoc.second == map[animalLoc.first].size() - 1)
  {
    currentLocs.push_back(pair<int, int>(animalLoc.first - 1, animalLoc.second));
    currentLocs.push_back(pair<int, int>(animalLoc.first, animalLoc.second - 1));
  }
  else
  {
    if (animalLoc.first != 0)
    {
      switch (map[animalLoc.first - 1][animalLoc.second])
      {
      case '|':
      case 'F':
      case '7':
        currentLocs.push_back(pair<int, int>(animalLoc.first - 1, animalLoc.second));
        break;
      }
    }
    if (animalLoc.first != map.size())
    {
      switch (map[animalLoc.first + 1][animalLoc.second])
      {
      case '|':
      case 'L':
      case 'J':
        currentLocs.push_back(pair<int, int>(animalLoc.first + 1, animalLoc.second));
        break;
      }
    }
    if (animalLoc.second != 0)
    {
      switch (map[animalLoc.first][animalLoc.second - 1])
      {
      case '-':
      case 'F':
      case 'L':
        currentLocs.push_back(pair<int, int>(animalLoc.first, animalLoc.second - 1));
        break;
      }
    }
    if (animalLoc.second != map[animalLoc.second].size())
    {
      switch (map[animalLoc.first][animalLoc.second + 1])
      {
      case '-':
      case '7':
      case 'J':
        currentLocs.push_back(pair<int, int>(animalLoc.first, animalLoc.second + 1));
        break;
      }
    }
  }

  if (currentLocs[0].first < animalLoc.first)
  {
    if (currentLocs[1].first > animalLoc.first)
      map[animalLoc.first][animalLoc.second] = '|';
    else if (currentLocs[1].second < animalLoc.second)
      map[animalLoc.first][animalLoc.second] = 'J';
    else if (currentLocs[1].second > animalLoc.second)
      map[animalLoc.first][animalLoc.second] = 'L';
  }
  else if (currentLocs[0].first > animalLoc.first)
  {
    if (currentLocs[1].first < animalLoc.first)
      map[animalLoc.first][animalLoc.second] = '|';
    else if (currentLocs[1].second < animalLoc.second)
      map[animalLoc.first][animalLoc.second] = '7';
    else if (currentLocs[1].second > animalLoc.second)
      map[animalLoc.first][animalLoc.second] = 'F';
  }
  else if (currentLocs[0].second < animalLoc.second)
  {
    if (currentLocs[1].first == animalLoc.first)
      map[animalLoc.first][animalLoc.second] = '-';
    else if (currentLocs[1].first < animalLoc.first)
      map[animalLoc.first][animalLoc.second] = 'J';
    else if (currentLocs[1].first > animalLoc.first)
      map[animalLoc.first][animalLoc.second] = '7';
  }
  else if (currentLocs[0].second > animalLoc.second)
  {
    if (currentLocs[1].first == animalLoc.first)
      map[animalLoc.first][animalLoc.second] = '-';
    else if (currentLocs[1].first < animalLoc.first)
      map[animalLoc.first][animalLoc.second] = 'L';
    else if (currentLocs[1].first > animalLoc.first)
      map[animalLoc.first][animalLoc.second] = 'F';
  }
}