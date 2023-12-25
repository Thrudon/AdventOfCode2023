#pragma once
#include <vector>

#include "node.h"

class Tree
{
public:
  vector<int> endMoves;
  int loopLength;

  Tree(shared_ptr<Node> root);
  void browse(int numTree, string path);

private:
  shared_ptr<Node> _root;
  vector<int> endMovesPath;
};