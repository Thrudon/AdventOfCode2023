#pragma once

#define uint unsigned long long int

#include <string>
#include <vector>

using namespace std;

struct Map
{
  uint source;
  uint destination;
  uint range;

  Map(uint _source, uint _destination, uint _range) :
    source(_source),
    destination(_destination),
    range(_range)
  {}

  friend bool operator<(const Map& lhs, const Map& rhs)
  {
    return lhs.source < rhs.source;
  }
};

class Converter
{
public:
  Converter();
  uint getMinLocation();
  
  void setSeeds(string line); // Part 1
  void setSeedRanges(string line); // Part 2

  void addEntry(string entry, string line);
  void sortEntries();

private:
  vector<Map> seedRanges;
  
  vector<Map> seedToSoil;
  vector<Map> soilToFertilizer;
  vector<Map> fertilizerToWater;
  vector<Map> waterToLight;
  vector<Map> lightToTemperature;
  vector<Map> temperatureToHumidity;
  vector<Map> humidityToLocation;

  vector<Map> soilRanges;
  vector<Map> fertilizerRanges;
  vector<Map> waterRanges;
  vector<Map> lightRanges;
  vector<Map> temperatureRanges;
  vector<Map> humidityRanges;
  vector<Map> locationRanges;

  void convertSeedToLocation(Map& seedRange);
  void convertSourceToDestination(Map& source, string destination);
};