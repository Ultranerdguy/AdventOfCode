#include "include.h"

#include <queue>
#include <set>

bool operator==(Coord const& lhs, Coord const& rhs)
{
  return lhs.x == rhs.x && lhs.y == rhs.y;
}

bool operator<(Coord const& lhs, Coord const& rhs)
{
  return lhs.x != rhs.x ? lhs.x < rhs.x : lhs.y < rhs.y;
}

bool operator>(Node const& lhs, Node const& rhs)
{
  return lhs.distance > rhs.distance;
}

void Grid::SetWidth(std::size_t const width)
{
  m_width = width;
}

void Grid::SetHeight(std::size_t const height)
{
  m_height = height;
}

void Grid::SetNodeWeights(std::vector<int> const& weights)
{
  m_nodeWeights = weights;
}

unsigned long long Grid::GetPathLength(Coord const& start, Coord const& end)
{
  std::vector<std::size_t> previousNodes;
  previousNodes.resize(m_width * m_height, m_width * m_height);
  std::priority_queue<Node, std::vector<Node>, std::greater<Node>> queue;
  std::set<Coord> visited;
  Node currentNode = Node{ start, 0 };
  queue.push(currentNode);
  visited.insert(start);
  while (!queue.empty())
  {
    currentNode = queue.top();
    queue.pop();
    previousNodes[GetArrayPos(currentNode.pos)] = GetArrayPos(currentNode.previous);
    if (currentNode.pos == end) break;
    auto const adjacent = GetAdjacent(currentNode.pos);
    for (Coord const& adjPos : adjacent)
    {
      if (visited.find(adjPos) == visited.end())
      {
        visited.insert(adjPos);
        queue.push(Node{ adjPos, currentNode.distance + m_nodeWeights[GetArrayPos(adjPos)], currentNode.pos });
      }
    }
  }

  unsigned long long pathRisk = 0;
  std::size_t currentPos = GetArrayPos(end);
  std::size_t startIndex = GetArrayPos(start);
  while (currentPos != startIndex)
  {
    pathRisk += m_nodeWeights[currentPos];
    currentPos = previousNodes[currentPos];
  }
  return pathRisk;
}

unsigned long long Grid::GetWrappedPathLength(Coord const& start, Coord const& end)
{
  std::vector<std::size_t> previousNodes;
  previousNodes.resize(m_width * m_height*25);
  std::priority_queue<Node, std::vector<Node>, std::greater<Node>> queue;
  std::set<Coord> visited;
  Node currentNode = Node{ start, 0 };
  queue.push(currentNode);
  visited.insert(start);
  while (!queue.empty())
  {
    currentNode = queue.top();
    queue.pop();
    previousNodes[GetArrayPos(currentNode.pos, 5)] = GetArrayPos(currentNode.previous, 5);
    if (currentNode.pos == end) break;
    auto const adjacent = GetWrappedAdjacent(currentNode.pos);
    for (Coord const& adjPos : adjacent)
    {
      if (visited.find(adjPos) == visited.end())
      {
        visited.insert(adjPos);
        int deltaWeight = (m_nodeWeights[GetWrappedArrayPos(adjPos)] + (adjPos.x / m_width) + (adjPos.y / m_height)) % 9;
        deltaWeight = deltaWeight != 0 ? deltaWeight : 9;
        queue.push(Node{ adjPos, currentNode.distance + deltaWeight, currentNode.pos });
      }
    }
  }

  unsigned long long pathRisk = 0;
  std::size_t currentPos = GetArrayPos(end, 5);
  std::size_t startIndex = GetArrayPos(start, 5);
  while (currentPos != startIndex)
  {
    Coord pos = Coord{ currentPos % (5*m_width), currentPos / (5 * m_height) };
    int deltaWeight = (m_nodeWeights[GetWrappedArrayPos(pos)] + (pos.x / m_width) + (pos.y / m_height)) % 9;
    deltaWeight = deltaWeight != 0 ? deltaWeight : 9;
    pathRisk += deltaWeight;
    currentPos = previousNodes[currentPos];
  }
  return pathRisk;
}

std::vector<Coord> Grid::GetAdjacent(Coord const& pos)
{
  std::vector<Coord> out;
  out.reserve(4);

  for (int const dx : { -1, 1 })
  {
    if ((pos.x + dx) < m_width) out.emplace_back(Coord{ pos.x + dx, pos.y });
  }
  for (int const dy : { -1, 1 })
  {
    if ((pos.y + dy) < m_height) out.emplace_back(Coord{ pos.x, pos.y + dy });
  }
  return out;
}

std::vector<Coord> Grid::GetWrappedAdjacent(Coord const& pos)
{
  std::vector<Coord> out;
  out.reserve(4);

  for (int const dx : { -1, 1 })
  {
    if ((pos.x + dx) < m_width*5) out.emplace_back(Coord{ pos.x + dx, pos.y });
  }
  for (int const dy : { -1, 1 })
  {
    if ((pos.y + dy) < m_height*5) out.emplace_back(Coord{ pos.x, pos.y + dy });
  }
  return out;
}

std::size_t Grid::GetArrayPos(Coord const& pos, std::size_t widthScale)
{
  return pos.x + pos.y * m_width*widthScale;
}

std::size_t Grid::GetWrappedArrayPos(Coord const& pos)
{
  return (pos.x%m_width) + (pos.y%m_height) * m_width;
}