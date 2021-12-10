#include "include.h"
#include <queue>
#include <vector>
#include <string>

void Grid::SetWidth(std::size_t width)
{
  m_width = width;
  m_deltas[3] = static_cast<signed long long>(width);
  m_deltas[0] = -m_deltas[3];
}

void Grid::AddValue(unsigned int value)
{
  m_grid.push_back(value);
}

unsigned long long Grid::CalculateRisk()
{
  unsigned long long sum = 0;
  long long const size = static_cast<long long>(m_grid.size());
  for (long long i=0; i<size; ++i)
  {
    unsigned char const query = m_grid[i];
    bool valid = true;
    for (auto d : m_deltas)
    {
      if (ValidDelta(i,d) && query >= m_grid[i+d])
      {
        valid = false;
        break;
      }
    }
    if (valid)
    {
      sum += query + 1;
    }
  }
  return sum;
}

unsigned long long Grid::FloodBasin(std::size_t start)
{
  unsigned long long counter = 0;
  std::size_t const size = m_grid.size();
  std::queue<std::size_t> queryPos;
  queryPos.push(start);
  while (!queryPos.empty())
  {
    signed long long index = queryPos.front();
    ++counter;
    queryPos.pop();
    for (auto d : m_deltas)
    {
      if (ValidDelta(index, d) && m_grid[index+d] < 9)
      {
        queryPos.push(index+d);
        m_grid[index + d] = 10;
      }
    }
    m_grid[index] = 9;
  }
  return counter;
}

unsigned long long Grid::Max3Product()
{
  std::vector<unsigned long long> sizes;
  std::size_t const size = m_grid.size();
  for (std::size_t i=0; i<size; ++i)
  {
    if (m_grid[i] != 9)
    {
      sizes.push_back(FloodBasin(i));
    }
  }
  std::sort(begin(sizes), end(sizes), std::greater<unsigned long long>());
  return sizes[0] * sizes[1] * sizes[2];
}

bool Grid::ValidDelta(std::size_t i, signed long long d)
{
  std::size_t const size = m_grid.size();

  return i+d >= 0 && i+d < size && ((i+d)/m_width == i/m_width || abs(d) == m_width);
}

std::istream& operator>>(std::istream& lhs, Grid& rhs)
{
  std::string line;
  while (std::getline(lhs, line))
  {
    rhs.SetWidth(line.size());
    for (unsigned char c : line)
    {
      rhs.AddValue(static_cast<unsigned int>(c - '0'));
    }
  }
  return lhs;
}