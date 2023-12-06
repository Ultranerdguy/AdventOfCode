// C++ include files
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <numeric>

// Project specific files
#include "include.h"
#include "config.h"

int main(int argc, char* argv[])
{
  if (argc < 2)
  {
    std::cout << "Usage: \n";
    std::cout << "  " << EXECUTABLE << " <input file>\n";
    return 1;
  }
  std::ifstream input(argv[1]);

  std::vector<value_t> seeds;
  std::string word;
  input >> word; // skip "seeds:"
  value_t value = 0;
  while (input >> value) seeds.push_back(value);

  input.clear();

  PiecewiseFunction g;
  PiecewiseFunction function;
  while (input >> function) g = Compose(g,function);

  // Part 1 solution
  value_t target1 = std::numeric_limits<value_t>::max();
  for (auto s : seeds)
  {
    auto v = g(s);
    if (v < target1) target1 = v;
  }

  std::cout << "Day 5 Part 1: " << target1 << '\n';

  PiecewiseFunction::ranges_t minimumPoints;
  for (std::size_t i=0; i<seeds.size(); i += 2)
  {
    auto r = g.GetRanges(seeds[i], seeds[i]+seeds[i+1]);
    minimumPoints.insert(minimumPoints.end(), r.begin(), r.end());
  }

  value_t target2 = std::numeric_limits<value_t>::max();
  for (auto s : minimumPoints)
  {
    auto v = g(s.start);
    if (v < target2) target2 = v;
  }
  std::cout << "Day 5 Part 2: " << target2 << '\n';

  return 0;
}