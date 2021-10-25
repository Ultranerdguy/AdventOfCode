// C++ include files
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

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
  std::string line;
  int part1Total = 0;
  int part2Total = 0;
  while (std::getline(input, line) && !line.empty())
  {
    std::stringstream lineStream(line);
    int mass;
    lineStream >> mass;
    part1Total += (mass/3)-2;
    while (mass > 8)
    {
      mass = mass/3 - 2;
      part2Total += mass;
    }
  }
  std::cout << "Part 1: " << part1Total << '\n';
  std::cout << "Part 2: " << part2Total << '\n';
}