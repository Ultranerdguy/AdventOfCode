#include "include.h"
#include <algorithm>
#include <stack>
#include <set>
#include <iostream>

const std::string Graph::start = "start";
const std::string Graph::end = "end";

void Graph::AddConnection(std::string line)
{
  auto const sepPos = line.find('-');
  std::string left = line.substr(0, sepPos);
  std::string right = line.substr(sepPos + 1);

  m_nodes[left].m_adjacent.push_back(&m_nodes[right]);
  m_nodes[right].m_adjacent.push_back(&m_nodes[left]);

  m_nodes[left].m_isSmall = std::find_if(left.begin(), left.end(), isupper) == left.end();
  m_nodes[right].m_isSmall = std::find_if(right.begin(), right.end(), isupper) == right.end();

  m_nodes[left].name = left;
  m_nodes[right].name = right;
}

unsigned long long Graph::CountPaths(bool canDuplicate)
{
  unsigned long long counter = 0;
  Node& endNode = m_nodes[end];
  Node& startNode = m_nodes[start];
  for (auto pNode : startNode.m_adjacent)
  {
    auto itr = std::find(pNode->m_adjacent.begin(), pNode->m_adjacent.end(), &startNode);
    if (itr != pNode->m_adjacent.end())
    {
      pNode->m_adjacent.erase(itr);
    }
  }
  endNode.m_adjacent.clear();

  struct State
  {
    Node* pCurrentNode = nullptr;
    typename decltype(Node::m_adjacent)::iterator currentChild;
  };
  std::stack<State> states;
  std::set<Node*> visitedSmallNodes;
  Node* pDuplicateNode = nullptr;

  State startState{ &m_nodes[start], m_nodes[start].m_adjacent.begin() };
  states.push(startState);
  if (m_nodes[start].m_isSmall)
  {
    visitedSmallNodes.insert(&m_nodes[start]);
  }

  while (!states.empty())
  {
    State& currentState = states.top();
    if (currentState.pCurrentNode
      && currentState.currentChild != currentState.pCurrentNode->m_adjacent.end())
    {
      if (visitedSmallNodes.find(*currentState.currentChild) != visitedSmallNodes.end()
        && !(canDuplicate && !pDuplicateNode))
      {
        ++currentState.currentChild;
      }
      else
      {
        State newState;
        newState.pCurrentNode = *currentState.currentChild;
        newState.currentChild = newState.pCurrentNode->m_adjacent.begin();
        states.push(newState);
        if (newState.pCurrentNode->m_isSmall)
        {
          auto itr = visitedSmallNodes.find(newState.pCurrentNode);
          if (canDuplicate && itr != visitedSmallNodes.end() && !pDuplicateNode)
          {
            pDuplicateNode = newState.pCurrentNode;
          }
          visitedSmallNodes.insert(newState.pCurrentNode);
        }

        if (newState.pCurrentNode == &endNode) ++counter;
      }
    }
    else
    {
      if (currentState.pCurrentNode == pDuplicateNode)
      {
        pDuplicateNode = nullptr;
      }
      else
      {
        visitedSmallNodes.erase(currentState.pCurrentNode);
      }
      states.pop();
      if (!states.empty())
      {
        State& newState = states.top();
        ++newState.currentChild;
      }
    }
  }
  return counter;
}