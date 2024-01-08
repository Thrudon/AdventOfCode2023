#pragma once
#include <string>
#include <map>
#include <vector>

#define uint unsigned long long int

using namespace std;


class Lens
{
public:
  Lens(string entry);
  int getFullHash();

  static int getPower();

private:
  string _data;
  string _label;
  int _focalLength;
  int _hashVal;

  static map<int, vector<pair<string, int>>> _lens;

  int hash(string data);
};