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
    std::cout << "  " << EXECUTABLE << " <input file> [<output file>]";
    return 1;
  }
  std::ifstream input(argv[1]);
  
  // TODO: Solve problem
}