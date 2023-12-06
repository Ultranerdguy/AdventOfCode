#ifndef _AOC_INCLUDE_H_
#define _AOC_INCLUDE_H_

#include <vector>
#include <iostream>

using value_t = long long;

class PiecewiseFunction
{
public:
  struct StartOffsetPair
  {
    value_t start = 0;
    value_t offset = 0;
  };
  using ranges_t = std::vector<StartOffsetPair>;
  PiecewiseFunction();

  void Reset();
  void Insert(value_t start, value_t offset, value_t count);
  value_t operator()(value_t index) const;
  void Reduce();
  ranges_t GetRanges(value_t start, value_t end) const;
  void Debug()
  {
    for (auto& p : m_map) std::cout << p.start << ' ' << p.offset << '\n';
    std::cout << '\n';
  }

  friend PiecewiseFunction Compose(PiecewiseFunction const& first, PiecewiseFunction const& second);

private:
  void InsertIfNotFound(value_t start, value_t offset);
  void InsertForce(value_t start, value_t offset);

  ranges_t m_map;
};

std::istream& operator>>(std::istream& input, PiecewiseFunction& function);

#endif