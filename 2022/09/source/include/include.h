#ifndef _AOC_INCLUDE_H_
#define _AOC_INCLUDE_H_

#include <utility>
#include <iostream>

enum class Direction { U, D, L, R };

std::istream& operator>>(std::istream&, Direction&);

struct XY
{
  using coord_t = int;
  coord_t x{};
  coord_t y{};
};

bool operator==(XY const&, XY const&);

template <>
struct std::hash<XY>
{
  std::size_t operator()(XY const&) const;
};

XY XYFromDirection(Direction);

void StepTailToHead(XY const&, XY&);

#endif