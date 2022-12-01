#include "include.h"

bool Cuboid::Contains(Cuboid const& cuboid) const
{
  return m_min.x <= cuboid.m_min.x && cuboid.m_max.x <= m_max.x
    && m_min.y <= cuboid.m_min.y && cuboid.m_max.y <= m_max.y
    && m_min.z <= cuboid.m_min.z && cuboid.m_max.z <= m_max.z;
}

bool Cuboid::Contains(Vec3D const& point) const
{
  return m_min.x <= point.x && point.x <= m_max.x
    && m_min.y <= point.y && point.y <= m_max.y
    && m_min.z <= point.z && point.z <= m_max.z;
}


