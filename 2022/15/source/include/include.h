#ifndef _AOC_INCLUDE_H_
#define _AOC_INCLUDE_H_

#include <iostream>

struct XY
{
  signed long long x = 0;
  signed long long y = 0;
};

bool operator<(XY const& lhs, XY const& rhs);

std::istream& operator>>(std::istream& lhs, XY& rhs);

struct Sensor
{
  XY position;
  unsigned long long radius = 0;
};

struct Range
{
  signed long long start = 0;
  signed long long end = 0;
};

bool operator<(Range const& lhs, Range const& rhs);

bool Overlaps(Sensor const& sensor, signed long long yValue);

Range GetOverlap(Sensor const& sensor, signed long long yValue);

bool Overlaps(Range const& r1, Range const& r2);

Range Combine(Range const& r1, Range const& r2);

Range ClipRange(Range const& outer, Range const& inner);

#endif