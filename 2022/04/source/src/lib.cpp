#include "include.h"

Range::Range(range_t const _min, range_t const _max) noexcept
  : m_min(_min)
  , m_max(_max)
{}

void Range::SetMin(range_t const value) noexcept
{
  m_min = value;
}

void Range::SetMax(range_t const value) noexcept
{
  m_max = value;
}

bool Range::FullyOverlap(Range const& lhs, Range const& rhs) noexcept
{
  return ((lhs.m_min - rhs.m_min) * (rhs.m_max - lhs.m_max)) >= 0;
}

bool Range::PartialOverlap(Range const& lhs, Range const& rhs) noexcept
{
  return FullyOverlap(lhs, Range{rhs.m_min, rhs.m_min}) || FullyOverlap(lhs, Range{rhs.m_max, rhs.m_max});
}

std::istream& operator>>(std::istream& lhs, Range& rhs)
{
  range_t _min{};
  range_t _max{};
  char dash;
  lhs >> _min >> dash >> _max;
  rhs.SetMin(_min);
  rhs.SetMax(_max);
  return lhs;
}
