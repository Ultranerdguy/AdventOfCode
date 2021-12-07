// C++ include files
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
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
  std::vector<int> v;
  int i;
  while (input >> i)
  {
    v.push_back(i);
    input.ignore(1,',');
  }

  // Part 1
  std::sort(v.begin(), v.end());
  int const opt = v[v.size()/2];
  unsigned long long fuel = 0;
  for (auto i : v)
  {
    fuel += abs(i-opt);
  }
  std::cout << "Day 7 Part 1: " << fuel << '\n';

  // Part 2
  auto mean = std::accumulate(v.begin(), v.end(), 0.0)/v.size();
  mean = mean > opt ? floor(mean) : ceil(mean);
  fuel = 0;
  for (auto i : v)
  {
    unsigned long long dist = abs(static_cast<long long>(i-mean));
    fuel += (dist*(dist+1)) / 2;
  }
  std::cout << "Day 7 Part 2: " << fuel << '\n';
}