#include <algorithm>
#include <iostream>

#include "include.h"

std::istream& operator>>(std::istream& lhs, vec2& rhs)
{
  lhs >> rhs.x;
  lhs.get();
  lhs >> rhs.y;
  return lhs;
}

void VentGrid::AddVent(vec2 const& start, vec2 const& end)
{
  m_vents.push_back(std::make_pair(start, end));
  m_max.x = std::max(start.x, m_max.x);
  m_max.x = std::max(end.x, m_max.x);
  m_max.y = std::max(start.y, m_max.y);
  m_max.y = std::max(end.y, m_max.y);
}

void VentGrid::WalkGrid(bool doDiagonal)
{
  m_ventMap.clear();
  for (auto& vent : m_vents)
  {
    vec2 s = vent.first;
    vec2 const& e = vent.second;

    // Get a "normalised" direction vector
    vec2 dir{ e.x - s.x, e.y - s.y };
    if (dir.x != 0) dir.x /= abs(dir.x);
    if (dir.y != 0) dir.y /= abs(dir.y);

    if (doDiagonal || !(dir.x && dir.y))
    {
      while (s.x != e.x || s.y != e.y)
      {
        ++m_ventMap[s.x + s.y * m_max.x];
        s.x += dir.x;
        s.y += dir.y;
      }
      ++m_ventMap[e.x + e.y * m_max.x];
    }
  }
}

int VentGrid::CountCollisions() const
{
  int counter = 0;
  for (auto& p : m_ventMap)
  {
    if (p.second > 1) ++counter;
  }
  return counter;
}

void VentGrid::PrintGrid() const
{
  for (int i=0; i<=m_max.y; ++i)
  {
    for (int j=0; j<=m_max.x; ++j)
    {
      auto itr = m_ventMap.find(j + i*m_max.x);
      if (itr != m_ventMap.end())
      {
        std::cout << itr->second;
      }
      else
      {
        std::cout << '.';
      }
    }
    std::cout << '\n';
  }
}
