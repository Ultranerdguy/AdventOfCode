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

  Grid grid;
  input >> grid;

  std::cout << "Day 9 Part 1: " << grid.CalculateRisk() << '\n';
  std::cout << "Day 9 Part 2: " << grid.Max3Product() << '\n';
}