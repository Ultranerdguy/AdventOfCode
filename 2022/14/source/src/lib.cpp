#include "include.h"
#include <iostream>

std::istream& operator>>(std::istream& lhs, XY& rhs)
{
  char c;
  return lhs >> rhs.x >> c >> rhs.y;
}

XY Dir(XY from, XY to)
{
  XY d{to.x-from.x, to.y-from.y};
  if (d.x != 0) d.x /= std::abs(d.x);
  if (d.y != 0) d.y /= std::abs(d.y);
  return d;
}

Polyline::PolylineIterator::PolylineIterator(storage_t const& con, storage_t::const_iterator itrPos)
  : container(con)
{
  itrTarget = itrPos;
  if (itrPos != container.end())
  {
    currentPos = *itrPos;
    itrTarget = ++itrPos;
  }
}

XY Polyline::PolylineIterator::operator*() const
{
  return currentPos;
}

Polyline::PolylineIterator& Polyline::PolylineIterator::operator++()
{
  XY const& target = *itrTarget;
  if (currentPos.x == target.x && currentPos.y == target.y) ++itrTarget;
  if (itrTarget != container.end())
  {
    auto step = Dir(currentPos, *itrTarget);
    currentPos.x += step.x;
    currentPos.y += step.y;
  }
  return *this;
}

bool Polyline::PolylineIterator::operator!=(PolylineIterator const& rhs) const
{
  return (itrTarget != rhs.itrTarget); // Incomplete, but will do for iterating through a whole line
}

Polyline::PolylineIterator Polyline::begin() const
{
  return PolylineIterator(points, points.begin());
}

Polyline::PolylineIterator Polyline::end() const
{
  return PolylineIterator(points, points.end());
}

void Polyline::AddPoint(XY pnt)
{
  points.emplace_back(pnt);
}