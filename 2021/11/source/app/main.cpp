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
  if (input >> grid)
  {
    Grid grid2 = grid;
    unsigned long long count = 0;
    for (int i = 0; i<100; ++i)
    {
      count += grid.Step();
    }
    std::cout << "Day 11 Part 1: " << count << '\n';

    int i = 0;
    while (true)
    {
      ++i;
      if (grid2.Step() == 100)
      {
        break;
      }
    }
    std::cout << "Day 11 Part 2: " << i << '\n';
  }
}