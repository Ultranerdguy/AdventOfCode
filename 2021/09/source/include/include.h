#ifndef _AOC_INCLUDE_H_
#define _AOC_INCLUDE_H_

#include <vector>
#include <istream>

class Grid
{
public:
  void AddValue(unsigned int);
  void SetWidth(std::size_t width);

  unsigned long long CalculateRisk();
  unsigned long long FloodBasin(std::size_t start);
  unsigned long long Max3Product();

protected:
  bool ValidDelta(std::size_t i, signed long long d);

  std::vector<unsigned int> m_grid;
  signed long long m_deltas[4]{0,-1,1,0};
  std::size_t m_width;
};

std::istream& operator>>(std::istream& lhs, Grid& rhs);

#endif