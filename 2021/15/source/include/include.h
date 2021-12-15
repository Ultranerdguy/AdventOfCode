#ifndef _AOC_INCLUDE_H_
#define _AOC_INCLUDE_H_

#include <vector>

struct Coord
{
  std::size_t x = 0;
  std::size_t y = 0;
};

bool operator==(Coord const& lhs, Coord const& rhs);
bool operator<(Coord const& lhs, Coord const& rhs);

struct Node
{
  Coord pos;
  int distance = 0;
  Coord previous;
};

bool operator>(Node const& lhs, Node const& rhs);

class Grid
{
public:
  void SetWidth(std::size_t const width);
  void SetHeight(std::size_t const height);
  void SetNodeWeights(std::vector<int> const& weights);

  unsigned long long GetPathLength(Coord const& start, Coord const& end);
  unsigned long long GetWrappedPathLength(Coord const& start, Coord const& end);

private:
  std::vector<Coord> GetAdjacent(Coord const& pos);
  std::vector<Coord> GetWrappedAdjacent(Coord const& pos);
  std::size_t GetArrayPos(Coord const& pos, std::size_t widthScale = 1);
  std::size_t GetWrappedArrayPos(Coord const& pos);

  std::size_t m_width = 0;
  std::size_t m_height = 0;

  std::vector<int> m_nodeWeights;
};

#endif