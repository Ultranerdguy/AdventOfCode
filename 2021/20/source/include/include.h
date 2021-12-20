#ifndef _AOC_INCLUDE_H_
#define _AOC_INCLUDE_H_

#include <unordered_set>

struct Index2D
{
  signed long long int x = 0;
  signed long long int y = 0;
};

constexpr bool operator==(Index2D const& lhs, Index2D const& rhs);

struct Index2DHash
{
  std::size_t operator()(Index2D const& in) const;
};

class Image
{
public:
  void AddRow(std::string const& row, signed long long int rowIndex);
  void Step(bool ruleset[512]);
  unsigned long long int CountTrue() const;

  int CalculateCellIndex(Index2D const& cell, bool trackState) const;

private:
  bool m_trackTrueCells = true;
  using CellContainer = std::unordered_set<Index2D, Index2DHash>;
  CellContainer m_trackedCells;
};

#endif