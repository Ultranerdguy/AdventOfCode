// C++ include files
#include <iostream>
#include <fstream>
#include <string>

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

  
  CommandParser cmd;
  std::string line;
  while (std::getline(input, line))
  {
    cmd.ParseLine(line);
  }

  auto dirs = cmd.GetDirectories();
  std::size_t totalSize = 0;
  for (auto pDir : dirs)
  {
    auto size = cmd.GetDirectorySize(pDir);
    if (size <= 100000)
      totalSize += size;
  }

  std:: cout << "Day 07 Part 1: " << totalSize << '\n';

  constexpr std::size_t maxSpace = 70000000;
  constexpr std::size_t requiredSpace = 30000000;
  std::size_t const minimumDelete = requiredSpace - (maxSpace - cmd.GetDirectorySize());

  std::size_t candidateSize = std::numeric_limits<std::size_t>::max();
  for (auto pDir : dirs)
  {
    auto size = cmd.GetDirectorySize(pDir);
    if (size < candidateSize && size >= minimumDelete)
    {
      candidateSize = size;
    }
  }

  std::cout << "Day 07 Part 2: " << candidateSize << '\n';
}