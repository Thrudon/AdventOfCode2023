#include <iostream>
#include <algorithm>

#include "converter.h"

Converter::Converter()
{}

uint Converter::getMinLocation()
{
  uint minLoc = -1;
  for (vector<Map>::iterator seedRange = seedRanges.begin(); seedRange != seedRanges.end(); seedRange++)
  {
    convertSeedToLocation(*seedRange);
    if (locationRanges.size())
    {
      minLoc = minLoc < locationRanges[0].source ? minLoc : locationRanges[0].source;
    }
  }
  return minLoc;
}

void Converter::setSeeds(string line)
{
  line += " ";
  while (line.find_first_of(" ") != string::npos)
  {
    seedRanges.push_back(Map(stoll(line.substr(0, line.find_first_of(" "))), 0LL, 0LL));
    line = line.substr(line.find_first_of(" ") + 1);
  }
}

void Converter::setSeedRanges(string line)
{
  line += " ";
  while (line.find_first_of(" ") != string::npos)
  {
    uint seed = stoll(line.substr(0, line.find_first_of(" ")));
    line = line.substr(line.find_first_of(" ") + 1);
    uint range = stoll(line.substr(0, line.find_first_of(" ")));
    seedRanges.push_back(Map(seed, 0, range));
    line = line.substr(line.find_first_of(" ") + 1);
  }
}

void Converter::addEntry(string entry, string line)
{
  uint destination = stoll(line.substr(0, line.find_first_of(" ")));
  line = line.substr(line.find_first_of(" ") + 1);
  uint source = stoll(line.substr(0, line.find_first_of(" ")));
  line = line.substr(line.find_first_of(" ") + 1);
  uint range = stoll(line);

  if (entry == "soil")
    seedToSoil.push_back(Map(source, destination, range));
  if (entry == "fertilizer")
    soilToFertilizer.push_back(Map(source, destination, range));
  if (entry == "water")
    fertilizerToWater.push_back(Map(source, destination, range));
  if (entry == "light")
    waterToLight.push_back(Map(source, destination, range));
  if (entry == "temperature")
    lightToTemperature.push_back(Map(source, destination, range));
  if (entry == "humidity")
    temperatureToHumidity.push_back(Map(source, destination, range));
  if (entry == "location")
    humidityToLocation.push_back(Map(source, destination, range));
}

void Converter::sortEntries()
{
  sort(seedToSoil.begin(), seedToSoil.end());
  sort(soilToFertilizer.begin(), soilToFertilizer.end());
  sort(fertilizerToWater.begin(), fertilizerToWater.end());
  sort(waterToLight.begin(), waterToLight.end());
  sort(lightToTemperature.begin(), lightToTemperature.end());
  sort(temperatureToHumidity.begin(), temperatureToHumidity.end());
  sort(humidityToLocation.begin(), humidityToLocation.end());
}

void Converter::convertSeedToLocation(Map& seedRange)
{
  // Convert seed range to soil ranges
  soilRanges.clear();
  convertSourceToDestination(seedRange, "soil");
  sort(soilRanges.begin(), soilRanges.end());

  // Convert soil ranges to fertilizer ranges
  fertilizerRanges.clear();
  for (vector<Map>::iterator soilRange = soilRanges.begin(); soilRange != soilRanges.end(); soilRange++)
    convertSourceToDestination(*soilRange, "fertilizer");
  sort(fertilizerRanges.begin(), fertilizerRanges.end());

  // Convert fertilizer ranges to water ranges
  waterRanges.clear();
  for (vector<Map>::iterator fertilizerRange = fertilizerRanges.begin(); fertilizerRange != fertilizerRanges.end(); fertilizerRange++)
    convertSourceToDestination(*fertilizerRange, "water");
  sort(waterRanges.begin(), waterRanges.end());

  // Convert water ranges to light ranges
  lightRanges.clear();
  for (vector<Map>::iterator waterRange = waterRanges.begin(); waterRange != waterRanges.end(); waterRange++)
    convertSourceToDestination(*waterRange, "light");
  sort(lightRanges.begin(), lightRanges.end());

  // Convert light ranges to temperature ranges
  temperatureRanges.clear();
  for (vector<Map>::iterator lightRange = lightRanges.begin(); lightRange != lightRanges.end(); lightRange++)
    convertSourceToDestination(*lightRange, "temperature");
  sort(temperatureRanges.begin(), temperatureRanges.end());

  // Convert temperature ranges to humidity ranges
  humidityRanges.clear();
  for (vector<Map>::iterator temperatureRange = temperatureRanges.begin(); temperatureRange != temperatureRanges.end(); temperatureRange++)
    convertSourceToDestination(*temperatureRange, "humidity");
  sort(humidityRanges.begin(), humidityRanges.end());

  // Convert humidity ranges to location ranges
  locationRanges.clear();
  for (vector<Map>::iterator humidityRange = humidityRanges.begin(); humidityRange != humidityRanges.end(); humidityRange++)
    convertSourceToDestination(*humidityRange, "location");
  sort(locationRanges.begin(), locationRanges.end());
}

void Converter::convertSourceToDestination(Map& origin, string dest)
{
  vector<Map> targets;
  vector<Map> destinations;
  if (dest == "soil")
    targets = seedToSoil;
  else if (dest == "fertilizer")
    targets = soilToFertilizer;
  else if (dest == "water")
    targets = fertilizerToWater;
  else if (dest == "light")
    targets = waterToLight;
  else if (dest == "temperature")
    targets = lightToTemperature;
  else if (dest == "humidity")
    targets = temperatureToHumidity;
  else if (dest == "location")
    targets = humidityToLocation;

  vector<Map>::iterator prevTarget = targets.end();
  for (vector<Map>::iterator target = targets.begin(); target != targets.end(); ++target)
  {

    // Case : (Partly) Before first Target range
    if (target == targets.begin())
    {
      if (origin.source < target->source)
      {
        if (origin.source + origin.range < target->source)
        {
          destinations.push_back(origin);
        }
        else
        {
          destinations.push_back(Map(origin.source, 0, target->source - origin.source));
        }
      }
    }

    // Case : (Partly) Between current and previous Target ranges
    if (prevTarget != targets.end())
    {
      if (target->source - (prevTarget->source + prevTarget->range) > 1)
      {
        uint sourceVal = 0;
        bool sourced = false;
        if (origin.source >= prevTarget->source + prevTarget->range &&
            origin.source < target->source)
        {
          sourced = true;
          sourceVal = origin.source;
        }
        else if (origin.source <= prevTarget->source + prevTarget->range &&
            origin.source + origin.range > prevTarget->source + prevTarget->range)
        {
          sourced = true;
          sourceVal = prevTarget->source + prevTarget->range + 1;
        }

        uint rangeVal = 0;
        if (sourceVal == origin.source)
        {
          if (origin.source + origin.range < target->source)
            rangeVal = origin.range;
          else
            rangeVal = target->source - origin.source;
        }
        else
        {
          if (origin.source + origin.range < target->source)
            rangeVal = origin.range - (sourceVal - origin.source);
          else
            rangeVal = target->source - sourceVal;
        }

        if (sourced)
        {
          destinations.push_back(Map(sourceVal, 0, rangeVal));
        }
      }
    }

    // Case : (Partly) Inside Target range
    if (origin.source + origin.range >= target->source &&
        origin.source <= target->source + target->range)
    {
      uint sourceVal = 0;
      if (origin.source >= target->source)
        sourceVal = target->destination + (origin.source - target->source);
      else
        sourceVal = target->destination;
      
      uint rangeVal = 0;
      if (origin.source + origin.range <= target->source + target->range)
      {
        if (origin.source >= target->source)
          rangeVal = origin.range;
        else
          rangeVal = origin.range - (target->source - origin.source);
      }
      else
        rangeVal = target->destination + target->range - sourceVal;

      destinations.push_back(Map(sourceVal, 0, rangeVal));
    }

    // Case : (Partly) After last Target range
    if (target == targets.end())
    {
      if (origin.source > target->source + target->range)
      {
        destinations.push_back(origin);
      }
      else if (origin.source + origin.range > target->source + target->range)
      {
        destinations.push_back(Map(target->source + target->range + 1, 0, origin.source + origin.range - (target->source + target->range)));
      }
    }

    prevTarget = target;
  }

  if (dest == "soil")
    soilRanges.insert(soilRanges.end(), destinations.begin(), destinations.end());
  else if (dest == "fertilizer")
    fertilizerRanges.insert(fertilizerRanges.end(), destinations.begin(), destinations.end());
  else if (dest == "water")
    waterRanges.insert(waterRanges.end(), destinations.begin(), destinations.end());
  else if (dest == "light")
    lightRanges.insert(lightRanges.end(), destinations.begin(), destinations.end());
  else if (dest == "temperature")
    temperatureRanges.insert(temperatureRanges.end(), destinations.begin(), destinations.end());
  else if (dest == "humidity")
    humidityRanges.insert(humidityRanges.end(), destinations.begin(), destinations.end());
  else if (dest == "location")
    locationRanges.insert(locationRanges.end(), destinations.begin(), destinations.end());
}