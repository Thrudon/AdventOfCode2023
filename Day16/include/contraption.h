#pragma once
#include <string>
#include <map>
#include <vector>

#define uint unsigned long long int
#define coords pair<int, int>
using namespace std;

enum ORIENTATION
{
  UP = 0,
  DOWN,
  LEFT,
  RIGHT
};

class Contraption
{
public:
  Contraption();
  void addData(string data);

  int getVisitedAmt(coords coord, ORIENTATION orientation);
  int getMostEfficientVisitPath();
private:
  vector<string> _contraption;
  vector<string> _visited;
  vector<pair<coords, ORIENTATION>> _paths;
  map<coords, vector<ORIENTATION>> _accessWays;
  void initialize(coords, ORIENTATION);
  
  void explore();
};