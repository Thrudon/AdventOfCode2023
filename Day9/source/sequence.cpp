#include "sequence.h"

Sequence::Sequence(string line)
{
  vector<int> seq;
  line.append(" ");
  do
  {
    seq.push_back(stoi(line.substr(0, line.find_first_of(' '))));
    line = line.substr(line.find_first_of(' ') + 1);
  } while(!line.empty());  
  seqs.push_back(seq);
}

int Sequence::getNext()
{
  int i = seqs.size() - 1;
  while (!isSubseqAllZeros(i))
    makeSubseq(i++);
  
  seqs[seqs.size() - 1].push_back(0);
  int next = 0;
  while (i > 0)
    next = calculateNext(--i);
  
  return next;
}

int Sequence::getPrev()
{
  int i = seqs.size() - 1;
  while (!isSubseqAllZeros(i))
    makeSubseq(i++);
  
  seqs[seqs.size() - 1].push_back(0);
  int prev = 0;
  while (i > 0)
    prev = calculatePrev(--i);
  
  return prev;
}

bool Sequence::isSubseqAllZeros(int idx)
{
  for (int i = 0; i < seqs[idx].size(); i++)
    if (seqs[idx][i] != 0)
      return false;
  return true;
}

void Sequence::makeSubseq(int idx)
{
  vector<int> subseq;
  for (int i = 1; i < seqs[idx].size(); i++)
    subseq.push_back(seqs[idx][i] - seqs[idx][i - 1]);
  
  seqs.push_back(subseq);
}

int Sequence::calculateNext(int idx)
{
  int val = seqs[idx + 1][seqs[idx + 1].size() - 1] + seqs[idx][seqs[idx + 1].size() - 1];
  seqs[idx].push_back(val);
  return val;
}

int Sequence::calculatePrev(int idx)
{
  int val = seqs[idx][0] - seqs[idx + 1][0];
  seqs[idx].insert(seqs[idx].begin(), val);
  return val;
}