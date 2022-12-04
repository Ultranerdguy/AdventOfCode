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
  
  int fullOverlapCounterPart1{};
  int partOverlapCounterPart2{};
  Range range1;
  Range range2;
  char comma;
  while (input >> range1 >> comma >> range2)
  {
    if (Range::FullyOverlap(range1,range2))
    {
      ++fullOverlapCounterPart1;
      ++partOverlapCounterPart2;
    }
    else if (Range::PartialOverlap(range1,range2))
    {
      ++partOverlapCounterPart2;
    }
  }

  std::cout << "Day 04 Part 1: " << fullOverlapCounterPart1 << '\n';
  std::cout << "Day 04 Part 2: " << partOverlapCounterPart2 << '\n';
}