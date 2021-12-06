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
  
  std::vector<unsigned long long> ageCounts(9,0);
  unsigned long long age;
  while (input >> age)
  {
    ++ageCounts[age];
    input.ignore(1); // Skip comma
  }

  // Part 1
  for (int i=0; i<80; ++i)
  {
    std::rotate(ageCounts.begin(), ++ageCounts.begin(), ageCounts.end());
    ageCounts[6] += ageCounts[8]; // Spawn new fish
  }

  std::cout << "Day 6 Part 1: " << std::accumulate(ageCounts.begin(), ageCounts.end(), 0ULL) << '\n';

  // Part 2
  for (int i=0; i<256-80; ++i) // We've already simulated 80 days
  {
    std::rotate(ageCounts.begin(), ++ageCounts.begin(), ageCounts.end());
    ageCounts[6] += ageCounts[8]; // Spawn new fish
  }

  std::cout << "Day 6 Part 2: " << std::accumulate(ageCounts.begin(), ageCounts.end(), 0ULL) << '\n';
}