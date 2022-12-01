// C++ include files
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

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
  
  // Part 1
  // storage for all the elves, and how many calories they have
  using calorie_t = unsigned long long;
  std::vector<calorie_t> elfCalories{calorie_t{}};

  // Read all the calories that each elf is carrying
  std::string line;
  while (std::getline(input, line))
  {
    if (line.empty())
    {
      elfCalories.push_back(0);
    }
    else
    {
      std::stringstream lineStream(line);
      calorie_t calories;
      lineStream >> calories;
      elfCalories.back() += calories;
    }
  }

  // Find the highest calorie count
  calorie_t maxCalories{};
  for (auto calories : elfCalories)
  {
    if (calories > maxCalories)
    {
      maxCalories = calories;
    }
  }
  std::cout << "Day 01 Part 1: " << maxCalories << " calories\n";

  // Sort in decreasing order, so the largest three are at the front
  std::sort(elfCalories.begin(), elfCalories.end(), std::greater<calorie_t>());

  if (elfCalories.size() >= 3)
  {
    std::cout << "Day 01 Part 2: " << (elfCalories[0] + elfCalories[1] + elfCalories[2]) << " calories\n";
  }
}