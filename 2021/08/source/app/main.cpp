// C++ include files
#include <iostream>
#include <fstream>

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
  
  std::vector<Display> displays;
  Display nd;
  while (input >> nd)
  {
    displays.push_back(nd);
  }

  // Part 1
  unsigned long long counter = 0;
  for (auto& d : displays)
  {
    for (auto& c : d.GetOutput())
    {
      std::size_t segCount = c.GetSegments().size();
      if (segCount == 2 || segCount == 3 || segCount == 4 || segCount == 7)
      {
        ++counter;
      }
    }
  }
  std::cout << "Day 8 Part 1: " << counter << '\n';

  // Part 2
  unsigned long long sum = 0;
  for (auto& d : displays)
  {
    d.MapValues();
    sum += d.GetOutputValue();
  }
  std::cout << "Day 8 Part 2: " << sum << '\n';
}