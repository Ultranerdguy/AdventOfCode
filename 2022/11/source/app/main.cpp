// C++ include files
#include <iostream>
#include <fstream>
#include <algorithm>

// Project specific files
#include "include.h"
#include "config.h"

worry_t GetMonkeyBusiness(Environment& env, std::size_t rounds, bool tooWorried)
{
  auto monkeyCount = env.GetMonkeyCount();
  for (int round = 0; round < rounds; ++round)
  {
    for (int monkeyIndex = 0; monkeyIndex < monkeyCount; ++monkeyIndex)
    {
      env.GetMonkey(monkeyIndex).InspectAll(tooWorried);
    }
    env.UpdateItemWorry();
  }

  std::vector<std::size_t> allInspections;
  allInspections.reserve(monkeyCount);
  for (int monkeyIndex = 0; monkeyIndex < monkeyCount; ++monkeyIndex)
  {
    allInspections.push_back(env.GetMonkey(monkeyIndex).GetTotalInspections());
  }
  std::sort(allInspections.begin(), allInspections.end(), std::greater<std::size_t>());
  return allInspections[0] * allInspections[1];
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

  Environment env1;
  env1.Parse(input);
  auto env2 = env1;

  std::cout << "Day 11 Part 1: " << GetMonkeyBusiness(env1, 20, false) << '\n';
  std::cout << "Day 11 Part 2: " << GetMonkeyBusiness(env2, 10000, true) << '\n';
}