#include <iostream>
#include <sstream>
#include <algorithm>

#include "game.h"

Game::Game(string line)
{
  unsigned int spacePos = line.find_first_of(" ");
  unsigned int semicolonPos = line.find_first_of(":");
  id = stoi(line.substr(spacePos, semicolonPos - spacePos));
  line = line.substr(semicolonPos + 2);

  // cout << line << endl;
  int semicolonAmt = count(line.begin(), line.end(), ';');
  while (semicolonAmt >= 0)
  {
    unsigned int red = 0;
    unsigned int green = 0;
    unsigned int blue = 0;
    string set = line.substr(0, line.find_first_of(";"));

    // cout << "-- " << semicolonAmt << " - " << set << endl;
    int colonAmt = count(set.begin(), set.end(), ',');
    while (colonAmt >= 0)
    {
      string color = set.substr(0, set.find_first_of(","));
      // cout << "---- " << colonAmt << " - " << color << " - " << color.substr(0, color.find_first_of(" ")) << ":" << color.substr(color.find_first_of(" ") + 1) << endl;
      if (color.substr(color.find_first_of(" ") + 1) == "red")
        red = stoi(color.substr(0, color.find_first_of(" ")));
      if (color.substr(color.find_first_of(" ") + 1) == "green")
        green = stoi(color.substr(0, color.find_first_of(" ")));
      if (color.substr(color.find_first_of(" ") + 1) == "blue")
        blue = stoi(color.substr(0, color.find_first_of(" ")));
      
      set = set.substr(set.find_first_of(",") + 2);
      colonAmt--;
    }
    sets.push_back(Set(red, green, blue));

    line = line.substr(line.find_first_of(";") + 2);
    semicolonAmt--;
  }

  // cout << toString() << endl;
}

unsigned int Game::getId()
{
  return id;
}

bool Game::isValid(Set composition)
{
  for (Set set : sets)
  {
    if (!set.isValid(composition))
      return false;
  }
  return true;
}

string Game::toString()
{
  stringstream ss;
  ss << "Game " << id << ":";
  for (Set set : sets)
  {
    ss << " ";
    if (set.red)
    {
      ss << set.red << " red";
    }
    if (set.green)
    {
      if (set.red)
        ss << ", ";
      ss << set.green << " green";
    }
    if (set.blue)
    {
      if (set.red || set.green)
        ss << ", ";
      ss << set.blue << " blue";
    }
    ss << ";";
  }
  return ss.str();
}

Set Game::getMinSet()
{
  unsigned int red = 0;
  unsigned int green = 0;
  unsigned int blue = 0;

  for (Set set : sets)
  {
    // cout << "Set: " << set.red << " " << set.green << " " << set.blue << endl;
    red = set.red > red ? set.red : red;
    green = set.green > green ? set.green : green;
    blue = set.blue > blue ? set.blue : blue;
  }
  // cout << "MinSet: " << red << " " << green << " " << blue << endl;
  return Set(red, green, blue);
}