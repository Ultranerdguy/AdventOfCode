// C++ include files
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <set>
#include <algorithm>

// Project specific files
#include "include.h"
#include "config.h"

template <typename RegionContainer, typename Container>
unsigned long long GetVolume(RegionContainer const& regions, Container const& xCoords, Container const& yCoords, Container const& zCoords)
{
  unsigned long long volume = 0;
  for (auto xMin = xCoords.begin(), xMax = ++xCoords.begin(); xMax != xCoords.end(); ++xMin, ++xMax)
  {
    Vec3D pos;
    pos.x = *xMin;
    for (auto yMin = yCoords.begin(), yMax = ++yCoords.begin(); yMax != yCoords.end(); ++yMin, ++yMax)
    {
      pos.y = *yMin;
      for (auto zMin = zCoords.begin(), zMax = ++zCoords.begin(); zMax != zCoords.end(); ++zMin, ++zMax)
      {
        pos.z = *zMin;
        for (auto last = regions.rbegin(); last != regions.rend(); ++last) // It iterates backwards, I swear
        {
          if (last->second.Contains(pos))
          {
            if (last->first)
            {
              volume += (*zMax - *zMin) * (*yMax - *yMin) * (*xMax - *xMin);
            }
            break;
          }
        }
      }
    }
  }
  return volume;
}

int main(int argc, char* argv[])
{
  if (argc < 2)
  {
    std::cout << "Usage: \n";
    std::cout << "  " << EXECUTABLE << " <input file>\n";
    return 1;
  }
  std::ifstream input(argv[1]);
  
  std::vector<std::pair<bool, Cuboid>> regions;
  std::set<int> xCoords;
  std::set<int> yCoords;
  std::set<int> zCoords;
  std::string line;
  while (std::getline(input, line))
  {
    std::stringstream lineStream(line);
    std::string state;
    lineStream >> state;
    Cuboid lineRegion;
    lineStream.ignore(std::numeric_limits<std::streamsize>::max(), '=');
    lineStream >> lineRegion.m_min.x;
    lineStream.ignore(2);
    lineStream >> lineRegion.m_max.x;
    lineStream.ignore(std::numeric_limits<std::streamsize>::max(), '=');
    lineStream >> lineRegion.m_min.y;
    lineStream.ignore(2);
    lineStream >> lineRegion.m_max.y;
    lineStream.ignore(std::numeric_limits<std::streamsize>::max(), '=');
    lineStream >> lineRegion.m_min.z;
    lineStream.ignore(2);
    lineStream >> lineRegion.m_max.z;
    regions.push_back(std::make_pair(state == "on", lineRegion));
    xCoords.insert(lineRegion.m_min.x);
    xCoords.insert(lineRegion.m_max.x + 1);
    yCoords.insert(lineRegion.m_min.y);
    yCoords.insert(lineRegion.m_max.y + 1);
    zCoords.insert(lineRegion.m_min.z);
    zCoords.insert(lineRegion.m_max.z + 1);
  }
  decltype(xCoords) xCoordsTrim;
  decltype(yCoords) yCoordsTrim;
  decltype(zCoords) zCoordsTrim;
  xCoordsTrim.insert(-50);
  xCoordsTrim.insert(51);
  yCoordsTrim.insert(-50);
  yCoordsTrim.insert(51);
  zCoordsTrim.insert(-50);
  zCoordsTrim.insert(51);
  auto rangePred = [](signed long long val) {return -51 < val && val < 51; };
  for (auto x : xCoords) if (rangePred(x)) xCoordsTrim.insert(x);
  for (auto x : yCoords) if (rangePred(x)) yCoordsTrim.insert(x);
  for (auto x : zCoords) if (rangePred(x)) zCoordsTrim.insert(x);

  std::cout << "Day 22 Part 1: " << GetVolume(regions, xCoordsTrim, yCoordsTrim, zCoordsTrim) << '\n';
  std::cout << "Day 22 Part 2: " << GetVolume(regions, xCoords, yCoords, zCoords) << '\n';

  
  return 0;
}