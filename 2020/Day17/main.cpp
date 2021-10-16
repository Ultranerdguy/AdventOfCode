#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>

#include "Adjacents.h"

struct pos3
{
  int64_t x, y, z;
};

struct pos4 : pos3
{
  int64_t w;
};

struct Pos3Hash
{
  bool operator()(const pos3& pos) const
  {
    auto h = std::hash<int64_t>();
    return h(pos.x) << 13 ^ h(pos.y) << 7 ^ h(pos.z); 
  }
};

struct Pos4Hash
{
  bool operator()(const pos4& pos) const
  {
    auto h = std::hash<int64_t>();
    return h(pos.x) << 13 ^ h(pos.y) << 7 ^ h(pos.z) << 5 ^ h(pos.w);
  }
};

struct pos3Equal
{
  constexpr bool operator()(const pos3& l, const pos3& r) const
  {
    return l.x == r.x && l.y == r.y && l.z == r.z;
  }
};

struct pos4Equal
{
  constexpr bool operator()(const pos4& l, const pos4& r) const
  {
    return pos3Equal()(l, r) && l.w == r.w;
  }
};

class CConCubes
{
protected:
  typedef std::unordered_map<pos3, bool, Pos3Hash, pos3Equal> TCubeMap3;
  typedef std::unordered_map<pos4, bool, Pos4Hash, pos4Equal> TCubeMap4;
  TCubeMap3 m_cubeMap3;
  TCubeMap4 m_cubeMap4;
public:


  void Set(int64_t x, int64_t y, int64_t z, int64_t w = 0)
  {
    m_cubeMap3[{x, y, z}] = true;
    m_cubeMap4[{x, y, z, w}] = true;
  }

  bool Get(int64_t x, int64_t y, int64_t z) const
  {
    bool ret = false;
    auto itr = m_cubeMap3.find({ x,y,z });

    if (itr != m_cubeMap3.end())
    {
      ret = itr->second;
    }
    return ret;
  }


  bool Get(int64_t x, int64_t y, int64_t z, int64_t w) const
  {
    bool ret = false;
    auto itr = m_cubeMap4.find({ x,y,z,w });

    if (itr != m_cubeMap4.end())
    {
      ret = itr->second;
    }
    return ret;
  }

  size_t CountAdjacent(int64_t x, int64_t y, int64_t z) const
  {
    size_t count = 0;
    for (auto [dx, dy, dz] : adjacents3d)
    {
      if (Get(x + dx, y + dy, z + dz))
      {
        ++count;
      }
    }
    return count;
  }

  size_t CountAdjacent(int64_t x, int64_t y, int64_t z, int64_t w) const
  {
    size_t count = 0;
    for (auto [dx, dy, dz, dw] : adjacents4d)
    {
      if (Get(x + dx, y + dy, z + dz, w + dw))
      {
        ++count;
      }
    }
    return count;
  }

  void StepCycle3()
  {
    TCubeMap3 nextCycle;
    for (auto& [p,b] : m_cubeMap3)
    {
      const auto x = p.x;
      const auto y = p.y;
      const auto z = p.z;
      const size_t count = CountAdjacent(x, y, z);
      if (count == 3 || (b && count == 2))
      {
        nextCycle[{x, y, z}] = true;
      }

      // Update inactives nearby
      for (auto [dx, dy, dz] : adjacents3d)
      {
        if (!Get(x + dx, y + dy, z + dz) 
          && CountAdjacent(x+dx, y+dy, z+dz) == 3)
        {
          nextCycle[{x + dx,y + dy,z + dz}] = true;
        }
      }
    }
    m_cubeMap3 = nextCycle;
  }

  void StepCycle4()
  {
    TCubeMap4 nextCycle;
    for (auto& [p, b] : m_cubeMap4)
    {
      const auto x = p.x;
      const auto y = p.y;
      const auto z = p.z;
      const auto w = p.w;
      const size_t count = CountAdjacent(x, y, z, w);
      if (count == 3 || (b && count == 2))
      {
        nextCycle[{x, y, z, w}] = true;
      }

      // Update inactives nearby
      for (auto [dx, dy, dz, dw] : adjacents4d)
      {
        if (!Get(x + dx, y + dy, z + dz, w + dw)
          && CountAdjacent(x + dx, y + dy, z + dz, w + dw) == 3)
        {
          nextCycle[{x + dx, y + dy, z + dz, w + dw}] = true;
        }
      }
    }
    m_cubeMap4 = nextCycle;
  }

  size_t CountActive3() const
  {
    size_t count = 0;
    for (auto& [p, b] : m_cubeMap3)
    {
      if (b) ++count;
    }
    return count;
  }

  size_t CountActive4() const
  {
    size_t count = 0;
    for (auto& [p, b] : m_cubeMap4)
    {
      if (b) ++count;
    }
    return count;
  }
};

int main()
{
  constexpr char CUBE = '#';

  std::ifstream file("Input.txt");

  CConCubes engine;
  int64_t y = 0;
  while (file)
  {
    std::string line;
    std::getline(file, line);
    if (line.empty()) break;

    const size_t lineSize = line.size();
    for (size_t x = 0; x < lineSize; ++x)
    {
      if (line[x] == CUBE)
      {
        engine.Set(x, y, 0);
      }
    }
    ++y;
  }

  // Part 1
  for (int i = 0; i < 6; ++i)
  {
    engine.StepCycle3();
  }
  std::cout << "Part 1: " << engine.CountActive3() << '\n';

  // Part 1
  for (int i = 0; i < 6; ++i)
  {
    engine.StepCycle4();
  }
  std::cout << "Part 1: " << engine.CountActive4() << '\n';
}