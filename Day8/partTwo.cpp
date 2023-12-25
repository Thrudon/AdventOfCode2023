#include <iostream>
#include <fstream>
#include <regex>

#include "tree.h"
#include "browser.h"

using namespace std;

int main(int argc, char** argv)
{
  string path;
  map<string, shared_ptr<Node>> nodes;
  vector<Tree> trees;

  ifstream file("input");
  if (file.is_open())
  {
    getline(file, path);

    regex wordRgx("[0-9A-Z]+");
    smatch wordMatch;

    string line;
    while (getline(file, line))
    {
      if (line.empty())
        continue;
      
      vector<string> nodeDetails;
      while (regex_search(line, wordMatch, wordRgx))
      {
        nodeDetails.push_back(wordMatch.str());
        line = wordMatch.suffix();
      }
      if (nodes.find(nodeDetails[0]) == nodes.end())
        nodes.insert(make_pair(nodeDetails[0], make_shared<Node>(Node(nodeDetails[0]))));
      
      if (nodes.find(nodeDetails[1]) == nodes.end())
        nodes.insert(make_pair(nodeDetails[1], make_shared<Node>(Node(nodeDetails[1]))));
      nodes.at(nodeDetails[0])->left = nodes.at(nodeDetails[1]);
      
      if (nodes.find(nodeDetails[2]) == nodes.end())
        nodes.insert(make_pair(nodeDetails[2], make_shared<Node>(Node(nodeDetails[2]))));
      nodes.at(nodeDetails[0])->right = nodes.at(nodeDetails[2]);

      if (nodeDetails[0][nodeDetails[0].size() - 1] == 'A')
        trees.push_back(Tree(nodes.at(nodeDetails[0])));
    }
  }
  file.close();

  vector<Browser> browsers;
  for (int i = 0; i < trees.size(); i++)
  {
    trees[i].browse(i, path);
    browsers.push_back(Browser(trees[i].endMoves));
  }

  uint commonEndMove;
  bool end = false;

  vector<uint> values;
  for (int i = 0; i < browsers.size(); i++)
    values.push_back(browsers[i].getCurrent());
  
  int minVal = 0;
  while (!end)
  {
    end = true;
    for (int i = 0; i < values.size(); i++)
      minVal = values[i] < values[minVal] ? i : minVal;
    values[minVal] = browsers[minVal].getNext();

    for (int i = 0; i < values.size(); i++)
    {
      if (values[i] != values[minVal])
      {
        end = false;
        break;
      }
    }
  }
  cout << "Solution: " << values[minVal] << endl;
  return 0;
}