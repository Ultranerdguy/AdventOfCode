// C++ include files
#include <iostream>
#include <fstream>
#include <vector>
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

  Grid grid;
  std::string line;
  std::size_t height = 0;
  std::size_t width = 0;
  std::vector<int> values;
  while (std::getline(input, line))
  {
    ++height;
    auto const lineSize = line.size();
    width = lineSize > width ? lineSize : width;
    std::stringstream lineStream(line);
    char val[2]{ 0,0 };
    while (lineStream >> val[0])
    {
      values.push_back(atoi(val));
    }
  }
  grid.SetWidth(width);
  grid.SetHeight(height);
  grid.SetNodeWeights(values);

  std::cout << "Day 15 Part 1: " << grid.GetPathLength({ 0,0 }, { width - 1, height - 1 }) << '\n';
  std::cout << "Day 15 Part 2: " << grid.GetWrappedPathLength({ 0,0 }, { 5*width - 1, 5*height - 1 }) << '\n';
}