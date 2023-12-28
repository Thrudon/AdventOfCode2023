#pragma once
#include <string>
#include <vector>

#define uint unsigned long long int

using namespace std;

class Map
{
public:
  Map(int expansionRate);
  void addLine(string line);

  uint getShortestPathsLengthSum();
private:
  int _expansionRate;
  vector<string> map;
  vector<pair<int, int>> galaxyLocs;
  
  vector<bool> emptyRows;
  vector<bool> emptyColumns;

  void expandUniverse();
  uint getShortestPathLength(int galaxyOne, int galaxyTwo);
};