#include "include.h"

std::istream& operator>>(std::istream& lhs, Direction& dir)
{
  char c;
  lhs >> c;
  switch (c)
  {
    case 'U': dir = Direction::U; break;
    case 'D': dir = Direction::D; break;
    case 'L': dir = Direction::L; break;
    case 'R': dir = Direction::R; break;
  }
  return lhs;
}

bool operator==(XY const& lhs, XY const& rhs)
{
  return (lhs.x == rhs.x) && (lhs.y == rhs.y);
}

std::size_t std::hash<XY>::operator()(XY const& pos) const
{
  auto h = std::hash<XY::coord_t>();
  return (h(pos.x)>>1) ^ (h(pos.y)<<3);
}

XY XYFromDirection(Direction d)
{
  switch (d)
  {
    case Direction::U: return XY{0,1};
    case Direction::D: return XY{0,-1};
    case Direction::L: return XY{-1,0};
    case Direction::R: return XY{1,0};
  }
  return XY{};
}

// Quick and compliant sign function. -1 for <0, 0 for =0, 1 for >0
template <typename T>
int sign(T t)
{
  return (T{} < t) - (t < T{});
}

void StepTailToHead(XY const& head, XY& tail)
{
  // Need to step the shorter of the distances from tail to head 
  // (for diagonal), then 1 step minus the rest
  XY delta{head.x-tail.x, head.y-tail.y};
  int distance = std::max(std::abs(delta.x), std::abs(delta.y));
  if (distance > 1)
  {
    auto diagStep = std::min(std::abs(delta.x), std::abs(delta.y));
    if (std::abs(delta.x) == std::abs(delta.y))
      --diagStep;
    tail.x += diagStep * sign(delta.x);
    tail.y += diagStep * sign(delta.y);

    // Step once step short of head
    delta = XY{head.x-tail.x, head.y-tail.y};
    tail.x += delta.x - sign(delta.x);
    tail.y += delta.y - sign(delta.y);
  }
}