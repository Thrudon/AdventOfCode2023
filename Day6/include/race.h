#pragma once

using namespace std;

#define uint unsigned long long int

class Race
{
public:
  Race(uint _time, uint _record);
  uint getFasterWaysAmount();

private:
  uint time;
  uint record;
};