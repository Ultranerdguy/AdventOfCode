#include "include.h"

#include <string>

void Grid::Reset()
{
  m_grid.clear();
}

void Grid::AddValue(int value)
{
  m_grid.push_back(value);
}

int Grid::Step()
{
  int counter = 0;
  std::vector<std::size_t> flashIndexes;
  // First, increment all values
  std::size_t const size = m_grid.size();
  for (std::size_t i=0; i<size; ++i)
  {
    ++m_grid[i];
    if (m_grid[i] > 9)
    {
      flashIndexes.push_back(i);
    }
  }

  while (!flashIndexes.empty())
  {
    auto const index = flashIndexes.back();
    flashIndexes.pop_back();
    if (m_grid[index] != 0)
    {
      m_grid[index] = 0;
      ++counter;

      int const x = static_cast<int>(index)%10;
      int const y = static_cast<int>(index)/10;

      for (int dx = -1; dx < 2; ++dx)
      {
        for (int dy = -1; dy < 2; ++dy)
        {
          if (dx == 0 && dy == 0)
            continue;
        
          int const nX = x+dx;
          int const nY = y+dy;
          if (nX >= 0 && nX < 10 && nY >= 0 && nY < 10)
          {
            int const pos = nY*10 + nX;
            if (m_grid[pos] != 0)
            {
              ++m_grid[pos];
              if (m_grid[pos] > 9)
              {
                flashIndexes.push_back(pos);
              }
            }
          }
        }
      }
    }
  }
  return counter;
}

std::istream& operator>>(std::istream& lhs, Grid& rhs)
{
  rhs.Reset();
  for (int i=0; i<10; ++i)
  {
    std::string line;
    if (std::getline(lhs, line))
    {
      for (char c : line)
      {
        rhs.AddValue(static_cast<int>(c-'0'));
      }
    }
  }
  return lhs;
}