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

  VentGrid vents;
  vec2 s;
  vec2 e;
  while (input >> s && input.ignore(4) && input >> e)
  {
    vents.AddVent(s,e);
  }

  // Part 1
  vents.WalkGrid(false);
  std::cout << "Day 5 Part 1: " << vents.CountCollisions() << '\n';

  // Part 2
  vents.WalkGrid(true);
  std::cout << "Day 5 Part 2: " << vents.CountCollisions() << '\n';
  
  // TODO: Solve problem
}