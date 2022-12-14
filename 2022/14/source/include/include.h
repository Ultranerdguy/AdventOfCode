#ifndef _AOC_INCLUDE_H_
#define _AOC_INCLUDE_H_

#include <vector>
#include <iostream>

struct XY { int x = 0, y = 0; };

std::istream& operator>>(std::istream& lhs, XY& rhs);

XY Dir(XY from, XY to);

class Polyline
{
  using storage_t = std::vector<XY>;
public:
  class PolylineIterator
  {
  public:
    PolylineIterator(storage_t const& container, storage_t::const_iterator itrPos);
    XY operator*() const;
    PolylineIterator& operator++();
    bool operator!=(PolylineIterator const&) const;

  private:
    storage_t const& container;
    storage_t::const_iterator itrTarget;
    XY currentPos;
  };

  PolylineIterator begin() const;
  PolylineIterator end() const;

  void AddPoint(XY);
private:
  storage_t points;
};

#endif