#ifndef _AOC_INCLUDE_H_
#define _AOC_INCLUDE_H_

#include <istream>
#include <unordered_map>

struct vec2
{
  int x = 0;
  int y = 0;
};

std::istream& operator>>(std::istream& lhs, vec2& rhs);

class VentGrid
{
public:
  void AddVent(vec2 const& start, vec2 const& end);
  void WalkGrid(bool doDiagonal);
  int CountCollisions() const;

  void PrintGrid() const;
protected:
  std::vector<std::pair<vec2, vec2>> m_vents;
  vec2 m_max;
  std::unordered_map<int, int> m_ventMap;
};

#endif