#ifndef _AOC_INCLUDE_H_
#define _AOC_INCLUDE_H_

#include <memory>
#include <vector>

struct Vec3D
{
  signed long long x = 0;
  signed long long y = 0;
  signed long long z = 0;
};

class Cuboid
{
public:
  bool Contains(Cuboid const& cuboid) const;
  bool Contains(Vec3D const& point) const;

  Vec3D m_min;
  Vec3D m_max;
};

#endif