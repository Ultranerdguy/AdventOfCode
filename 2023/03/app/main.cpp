// C++ include files
#include <iostream>
#include <string>
#include <fstream>
#include <stack>
#include <vector>
#include <sstream>

// Project specific files
#include "include.h"
#include "config.h"

unsigned int readNumber(char const* pStr)
{
  std::stringstream stream(pStr);
  unsigned int v = 0;
  stream >> v;
  return v;
}

unsigned int findFullNumber(char const* pStrStart, std::size_t offset)
{
  char const* pStr = pStrStart + offset;
  if (!std::isdigit(*pStr)) return 0;
  while (std::isdigit(*pStr))
  {
    if (pStr > pStrStart)
      --pStr;
    else
      break;
  } 
  ++pStr;
  return readNumber(pStr);
}

int main(int argc, char* argv[])
{
  if (argc < 2)
  {
    std::cout << "Usage: \n";
    std::cout << "  " << EXECUTABLE << " <input file>\n";
    return 1;
  }
  std::ifstream input(argv[1]);

  // Read grid as one long line
  std::string grid;
  std::string line;
  std::size_t height = 0;
  while (std::getline(input, line) && !line.empty())
  {
    grid += line;
    grid += '.'; // Add an extra . to make handling wrapping easier
    ++height;
  }
  std::string grid2 = grid; // Copy for Part 2

  // Find the sum of all numbers
  std::stringstream fullGridStream(grid);
  unsigned int fullSum = 0;
  unsigned int readValue = 0;
  while (fullGridStream)
  {
    if (std::isdigit(fullGridStream.peek()) && fullGridStream >> readValue)
    {
      fullSum += readValue;
    }
    else
      fullGridStream.get(); // skip otherwise
  }

  // Create a stack of number positions
  std::size_t width = grid.size()/height;
  std::stack<std::size_t> positions;
  for (std::size_t i=0; i<grid.size(); ++i)
  {
    if (!std::isdigit(grid[i]) && grid[i] != '.')
    {
      for (int dx = -1; dx < 2; ++dx) for (int dy = -1; dy < 2; ++dy)
      {
        unsigned int x = (i%width) + dx;
        unsigned int y = (i/width) + dy;
        unsigned int p = y*width + x;
        if (0 <= x && x < width && 0 <= y && y < height && std::isdigit(grid[p]))
        positions.push(p);
        grid[i] = '.';
      }
    }
  }

  // Flood fill
  while (!positions.empty())
  {
    auto top = positions.top();
    positions.pop();

    unsigned int x = top%width;
    if (0 < x && std::isdigit(grid[top-1])) positions.push(top-1);
    if (x+1 < width && std::isdigit(grid[top+1])) positions.push(top+1);
    grid[top] = '.';
  }

  // Replace all . with empty space
  for (auto& c : grid)
  {
    if (c == '.') c = ' ';
  }

  // Read remaining numbers
  std::stringstream gridStream(grid);
  unsigned int badParts = 0;
  readValue = 0;
  while (gridStream >> readValue) badParts += readValue;

  std::cout << "Day 3 Part 1: " << (fullSum-badParts) << '\n';

  // Part 2

  unsigned int total2 = 0;
  for (std::size_t i=0; i<grid2.size(); ++i)
  {
    if (grid2[i] == '*')
    {
      // Get all neighbouring values
      std::vector<unsigned int> neighbours;
      unsigned int x = i%width;
      unsigned int y = i/width;

      auto GetPosition = [width](unsigned int x, unsigned int y){return y*width+x;};
      auto IsDigit = [&, width, height](unsigned int X, unsigned int Y){return 0 <= X && X < width && 0 <= Y && Y < height && std::isdigit(grid2[GetPosition(X,Y)]);};
      
      unsigned int value = 0;
      if (IsDigit(x,y-1)) neighbours.push_back(findFullNumber(grid2.c_str(), GetPosition(x,y-1)));
      else
      {
        if (IsDigit(x-1,y-1)) neighbours.push_back(findFullNumber(grid2.c_str(), GetPosition(x-1,y-1)));
        if (IsDigit(x+1,y-1)) neighbours.push_back(findFullNumber(grid2.c_str(), GetPosition(x+1,y-1)));
      }
      
      if (IsDigit(x-1,y)) neighbours.push_back(findFullNumber(grid2.c_str(), GetPosition(x-1,y)));
      if (IsDigit(x+1,y)) neighbours.push_back(findFullNumber(grid2.c_str(), GetPosition(x+1,y)));
      
      if (IsDigit(x,y+1)) neighbours.push_back(findFullNumber(grid2.c_str(), GetPosition(x,y+1)));
      else
      {
        if (IsDigit(x-1,y+1)) neighbours.push_back(findFullNumber(grid2.c_str(), GetPosition(x-1,y+1)));
        if (IsDigit(x+1,y+1)) neighbours.push_back(findFullNumber(grid2.c_str(), GetPosition(x+1,y+1)));
      }

      if (neighbours.size() == 2)
      {
        unsigned int prod = 1;
        for (auto v : neighbours) prod *= v;
        total2 += prod;
      }
    }
  }
  std::cout << "Day 3 Part 2: " << total2 << '\n';

  return 0;
}