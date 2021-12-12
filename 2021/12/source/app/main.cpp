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
  
  Graph graph;
  std::string line;
  while (std::getline(input, line))
  {
    graph.AddConnection(line);
  }
  std::cout << "Day 12 Part 1: " << graph.CountPaths(false) << '\n';
  std::cout << "Day 12 Part 2: " << graph.CountPaths(true) << '\n';
}