// C++ include files
#include <iostream>
#include <fstream>
#include <vector>

// Project specific files
#include "include.h"
#include "config.h"

int countIncreases(std::vector<int> const& data, int const stepsize)
{
  int counter = 0;
  std::size_t const size = data.size();
  for (std::size_t i=stepsize; i<size; ++i)
  {
    if (data[i] > data[i-stepsize])
    {
      ++counter;
    }
  }
  return counter;
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

  // Read input
  std::vector<int> data;
  int i = 0;
  while (input >> i)
  {
    data.push_back(i);
  }
  std::cout << data.size() << '\n';

  // Part 1
  std::cout << "Day 1 Part 1: " << countIncreases(data, 1) << '\n';

  // Part 2
  std::cout << "Day 1 Part 2: " << countIncreases(data, 3) << '\n';
}