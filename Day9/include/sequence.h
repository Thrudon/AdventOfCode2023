#pragma once
#include <string>
#include <vector>

using namespace std;

class Sequence
{
public:
  Sequence(string line);
  int getNext();
  int getPrev();
private:
  vector<vector<int>> seqs;

  bool isSubseqAllZeros(int idx);
  void makeSubseq(int idx);
  int calculateNext(int idx);
  int calculatePrev(int idx);
};