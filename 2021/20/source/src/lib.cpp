#include "include.h"

constexpr bool operator==(Index2D const& lhs, Index2D const& rhs)
{
  return lhs.x == rhs.x && lhs.y == rhs.y;
}

std::size_t Index2DHash::operator()(Index2D const& in) const
{
  return (std::hash<decltype(in.x)>()(in.x) << 1) ^ (std::hash<decltype(in.y)>()(in.y) >> 1);
}

void Image::AddRow(std::string const& row, signed long long int rowIndex)
{
  signed long long int const width = static_cast<signed long long int>(row.size());
  for (signed long long int i = 0; i < width; ++i)
  {
    if (row[i] == '#')
    {
      m_trackedCells.insert(Index2D{ i, rowIndex });
    }
  }
}

void Image::Step(bool ruleset[512])
{
  bool oldTrack = m_trackTrueCells;
  // Track the infinite grid
  if (m_trackTrueCells && ruleset[0])
  {
    m_trackTrueCells = false;
  }
  else if (!m_trackTrueCells && !ruleset[511])
  {
    m_trackTrueCells = true;
  }

  CellContainer outImage;
  CellContainer calculatedCells;

  for (auto& cell : m_trackedCells)
  {
    for (int j = -1; j < 2; ++j)
    {
      for (int i = -1; i < 2; ++i)
      {
        Index2D neighbour{ cell.x + i, cell.y + j };
        if (calculatedCells.find(neighbour) == calculatedCells.end())
        {
          bool const cellState = ruleset[CalculateCellIndex(neighbour, oldTrack)];
          if (cellState == m_trackTrueCells)
          {
            outImage.insert(neighbour);
          }
          calculatedCells.insert(neighbour);
        }
      }
    }
  }
  std::swap(m_trackedCells, outImage);
}

unsigned long long int Image::CountTrue() const
{
  unsigned long long int counter = 0;
  if (m_trackTrueCells == false)
  {
    counter = std::numeric_limits<unsigned long long int>::max();
  }
  else
  {
    counter = m_trackedCells.size();
  }
  return counter;
}

int Image::CalculateCellIndex(Index2D const& cell, bool trackState) const
{
  int out = 0;
  for (int j = -1; j < 2; ++j)
  {
    for (int i = -1; i < 2; ++i)
    {
      out <<= 1;
      Index2D neighbour{ cell.x + i, cell.y + j };
      out |= ((m_trackedCells.find(neighbour) != m_trackedCells.end()) == trackState) ? 1 : 0;
    }
  }
  return out;
}