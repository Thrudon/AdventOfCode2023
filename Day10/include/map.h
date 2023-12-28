#pragma once
#include <string>
#include <vector>

using namespace std;

class Map
{
public:
  Map();
  void addLine(string line);

  int getDistanceToFurthestPoint();
  int getNbTilesInsidePath();
private:
  vector<string> map;
  vector<pair<int, int>> pathLocs;
  pair<int, int> animalLoc;

  vector<pair<int, int>> prevLocs;
  vector<pair<int, int>> currentLocs;
  
  void goToNextLocs();
  void getFirstLocs();
};