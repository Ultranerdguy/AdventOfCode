// C++ include files
#include <iostream>

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
  for (int i=0;i<argc;++i) std::cout << argv[i] << '\n';
  std::cout << EXECUTABLE << '\n';
}