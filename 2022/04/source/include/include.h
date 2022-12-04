#ifndef _AOC_INCLUDE_H_
#define _AOC_INCLUDE_H_
#include <iostream>

using range_t = int;

class Range
{
public:
  Range() = default;
  Range(range_t const, range_t const) noexcept;

  void SetMin(range_t const) noexcept;
  void SetMax(range_t const) noexcept;

  static bool FullyOverlap(Range const&, Range const&) noexcept;
  static bool PartialOverlap(Range const&, Range const&) noexcept;

private:
  range_t m_min{};
  range_t m_max{};
};

std::istream& operator>>(std::istream&, Range&);

#endif