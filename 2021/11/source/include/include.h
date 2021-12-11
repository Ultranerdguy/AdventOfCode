#ifndef _AOC_INCLUDE_H_
#define _AOC_INCLUDE_H_

#include <vector>
#include <istream>

class Grid
{
public:
  void Reset();
  void AddValue(int value);

  int Step();

protected:
  std::vector<int> m_grid;
};

std::istream& operator>>(std::istream& lhs, Grid& rhs);

#endif