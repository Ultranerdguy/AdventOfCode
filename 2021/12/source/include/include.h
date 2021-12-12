#ifndef _AOC_INCLUDE_H_
#define _AOC_INCLUDE_H_

#include <vector>
#include <string>
#include <unordered_map>

struct Node
{
  std::string name;
  bool m_isSmall = false;
  std::vector<Node*> m_adjacent;
};

class Graph
{
public:
  void AddConnection(std::string line);

  unsigned long long CountPaths(bool canDuplicate);

  static const std::string start;
  static const std::string end;
protected:
  Node* m_pStart = nullptr;
  Node* m_pEnd = nullptr;
  std::unordered_map<std::string, Node> m_nodes;
};

#endif