// C++ include files
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>

// Project specific files
#include "include.h"
#include "config.h"

std::vector<Range> GetRanges(std::vector<Sensor> const& sensors, signed long long yValue)
{
  std::vector<Range> ranges;
  for (auto& s : sensors)
  {
    if (Overlaps(s, yValue))
    {
      ranges.push_back(GetOverlap(s, yValue));
    }
  }

  std::sort(ranges.begin(), ranges.end());

  std::vector<Range> reducedRanges;
  if (!ranges.empty())
  {
    reducedRanges.push_back(ranges.front());
    std::size_t rIndex = 1;
    for (std::size_t i = 0; i < reducedRanges.size(); ++i)
    {
      for (; rIndex < ranges.size(); ++rIndex)
      {
        if (Overlaps(reducedRanges[i], ranges[rIndex]))
        {
          reducedRanges[i] = Combine(reducedRanges[i], ranges[rIndex]);
        }
        else
        {
          reducedRanges.push_back(ranges[rIndex]);
          break;
        }
      }
    }
  }
  return reducedRanges;
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
  
  std::vector<Sensor> sensors;
  std::set<XY> beacons;
  while (input)
  {
    XY sensorpos;
    XY beaconpos;
    std::string word;
    while (input >> word)
    {
      if (word == "at")
      {
        input >> sensorpos;
        break;
      }
    }
    while (input >> word)
    {
      if (word == "at")
      {
        input >> beaconpos;
        break;
      }
    }

    if (input)
    {
      unsigned long long radius = std::abs(sensorpos.x - beaconpos.x) + std::abs(sensorpos.y - beaconpos.y);
      sensors.emplace_back(Sensor{ sensorpos, radius });
      beacons.insert(beaconpos);
    }
  }

  constexpr signed long long yValue = 2000000;
  
  {
    auto reducedRanges = GetRanges(sensors, yValue);
    signed long long sumRangeSizes = 0;
    for (auto& r : reducedRanges)
    {
      sumRangeSizes += (r.end - r.start + 1);
    }

    for (auto& b : beacons)
    {
      if (b.y == yValue) --sumRangeSizes;
    }

    std::cout << "Day 15 Part 1: " << sumRangeSizes << '\n';
  }

  {
    signed long long x = 0;
    signed long long y = 0;
    constexpr signed long long MAXRANGE = 4000000;
    Range clipRange{ 0,MAXRANGE };
    for (; y <= MAXRANGE; ++y)
    {
      auto reducedRanges = GetRanges(sensors, y);
      signed long long sumRangeSizes = 0;
      for (auto& r : reducedRanges)
      {
        r = Overlaps(clipRange, r) ? ClipRange(clipRange, r) : r;
        sumRangeSizes += (r.end - r.start + 1);
      }
      if (sumRangeSizes != (MAXRANGE + 1))
      {
        Range& r = reducedRanges.front();
        if (r.start == 0) x = r.end + 1;
        break;
      }
    }

    std::cout << "Day 15 Part 2: " << (4000000 * x + y) << '\n';
  }
}