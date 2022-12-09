// C++ include files
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

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
  
  std::vector<bool> visible;
  std::vector<std::vector<unsigned char>> grid;

  // Read the grid into a 2D array (row,column)
  std::string line;
  while (std::getline(input, line) && !line.empty())
  {
    std::vector<unsigned char> numLine;
    for (auto c : line)
    {
      numLine.push_back(c-'0');
    }
    grid.emplace_back(numLine);
  }

  // Naive process
  std::size_t const height = grid.size();
  std::size_t const width = grid.front().size();
  visible.resize(height*width, false);
  for (std::size_t y = 0; y < height; ++y)
  {
    for (std::size_t x = 0; x < width; ++x)
    {
      auto const treeHeight = grid[y][x];

      auto& visibleCheck = visible[(y*width) + x];

      // Tree sits on the edge, already visible
      if (x==0 || y==0 || x==(width-1) || y==(height-1))
      {
        visibleCheck = true;
        continue;
      }
      bool canSee = true;
      for (std::size_t i = 0; i < x && canSee && !visibleCheck; ++i)
      {
        if (grid[y][i] >= treeHeight)
        {
          canSee = false;
        }
      }
      if (canSee) visibleCheck = true;
      canSee = true;
      for (std::size_t i = x+1; i < width && canSee && !visibleCheck; ++i)
      {
        if (grid[y][i] >= treeHeight)
        {
          canSee = false;
        }
      }
      if (canSee) visibleCheck = true;
      canSee = true;
      for (std::size_t i = 0; i < y && canSee && !visibleCheck; ++i)
      {
        if (grid[i][x] >= treeHeight)
        {
          canSee = false;
        }
      }
      if (canSee) visibleCheck = true;
      canSee = true;
      for (std::size_t i = y+1; i < height && canSee && !visibleCheck; ++i)
      {
        if (grid[i][x] >= treeHeight)
        {
          canSee = false;
        }
      }
      if (canSee) visibleCheck = true;
    }
  }

  std::cout << "Day 08 Part 1: " << std::count(visible.begin(), visible.end(), true) << '\n';

  std::vector<unsigned long long> score(width*height, 1);
  for (std::size_t y = 0; y < height; ++y)
  {
    for (std::size_t x = 0; x < width; ++x)
    {
      auto const treeHeight = grid[y][x];

      auto& treeScore = score[(y*width) + x];

      // Tree sits on the edge, one viewing distance is zero, so score is zero
      if (x==0 || y==0 || x==(width-1) || y==(height-1))
      {
        treeScore = 0;
        continue;
      }
      std::size_t i = 0;
      for (i = 1; i < x; ++i)
      {
        if (grid[y][x-i] >= treeHeight)
        {
          break;
        }
      }
      treeScore *= i;
      for (i = 1; i < width-x-1; ++i)
      {
        if (grid[y][x+i] >= treeHeight)
        {
          break;
        }
      }
      treeScore *= i;
      for (i = 1; i < y; ++i)
      {
        if (grid[y-i][x] >= treeHeight)
        {
          break;
        }
      }
      treeScore *= i;
      for (i = 1; i < height-y-1; ++i)
      {
        if (grid[y+i][x] >= treeHeight)
        {
          break;
        }
      }
      treeScore *= i;
    }
  }
  auto maxItr = std::max_element(score.begin(), score.end());
  std::cout << "Day 08 Part 2: " << *maxItr << '\n';
}