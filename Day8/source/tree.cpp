#include <iostream>
#include <algorithm>

#include "tree.h"

Tree::Tree(shared_ptr<Node> root) :
  _root(root)
{}

void Tree::browse(int numTree, string path)
{
  shared_ptr<Node> currentNode = _root;
  int move = 0;
  while (find(endMovesPath.begin(), endMovesPath.end(), move % path.size()) == endMovesPath.end())
  {
    if (currentNode->name[currentNode->name.size() - 1] == 'Z')
    {
      endMovesPath.push_back(move % path.size());
      endMoves.push_back(move);
    }

    do
    {
      // cout << currentNode->name << " - " << currentNode->left->name << " : " << currentNode->right->name << endl;
      switch (path[move % path.size()])
      {
      case 'L':
        currentNode = currentNode->left;
        break;
      case 'R':
        currentNode = currentNode->right;
        break;
      }
      move++;
    }
    while (currentNode->name[currentNode->name.size() - 1] != 'Z');
  }
  loopLength = move - endMoves[0];
}