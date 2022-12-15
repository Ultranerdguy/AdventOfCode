#include "include.h"

bool operator<(XY const& lhs, XY const& rhs)
{
  return (lhs.x != rhs.x) ? (lhs.x < rhs.x) : (lhs.y < rhs.y);
}

std::istream& operator>>(std::istream& lhs, XY& rhs)
{
  char c;
  lhs >> std::skipws >> c >> c >> rhs.x >> c >> std::skipws >> c >> c >> rhs.y;
  return lhs;
}

bool operator<(Range const& lhs, Range const& rhs)
{
  return (lhs.start != rhs.start) ? (lhs.start < rhs.start) : (lhs.end < rhs.end);
}

bool Overlaps(Sensor const& sensor, signed long long yValue)
{
  return std::abs(sensor.position.y - yValue) <= sensor.radius;
}

Range GetOverlap(Sensor const& sensor, signed long long yValue)
{
  auto delta = sensor.radius - std::abs(sensor.position.y - yValue);
  Range range{sensor.position.x-delta, sensor.position.x+delta};
  return range;
}

bool Overlaps(Range const& r1, Range const& r2)
{
  return (r1.start <= r2.end) && (r2.start <= r1.end);
}

Range Combine(Range const& r1, Range const& r2)
{
  return Range{std::min(r1.start, r2.start), std::max(r1.end, r2.end)};
}

Range ClipRange(Range const& outer, Range const& inner)
{
  Range ret = inner;
  if (inner.start < outer.start) ret.start = outer.start;
  if (outer.end < inner.end) ret.end = outer.end;
  return ret;
}