#pragma once
#include <string>
#include <memory>

using namespace std;

struct Node
{
  Node(string _name);

  string name;
  shared_ptr<Node> left;
  shared_ptr<Node> right;
};