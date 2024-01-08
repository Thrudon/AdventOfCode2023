#pragma once
#include <string>
#include <vector>

#define uint unsigned long long int

using namespace std;

enum AXIS
{
  NORTH = 0,
  SOUTH,
  EAST,
  WEST
};

class Dish
{
public:
  Dish();
  void addData(string line);
  void tilt(AXIS axis);
  void spin(int cycleAmt);
  int getValue();

private:
  vector<vector<char>> _data;
};