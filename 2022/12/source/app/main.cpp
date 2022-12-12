// C++ include files
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>

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

  std::size_t width = 0;
  std::size_t height = 0;
  std::vector<int> heightMap;
  std::size_t startIndex = 0;
  std::size_t endIndex = 0;

  std::string line;
  while (std::getline(input, line) && !line.empty())
  {
    std::size_t lineLength = line.size();
    if (width == 0) width = lineLength;
    heightMap.reserve(heightMap.size() + lineLength);
    for (std::size_t i = 0; i < lineLength; ++i)
    {
      if (line[i] == 'S')
      {
        startIndex = i + (heightMap.size()/width)*width;
        line[i] = 'a';
      }
      if (line[i] == 'E')
      {
        endIndex   = i + (heightMap.size()/width)*width;
        line[i] = 'z';
      }

      heightMap.push_back(line[i]-'a');
    }
  }
  height = heightMap.size()/width;

  {
    std::vector<std::size_t> previous(heightMap.size(), -1);

    // BFS
    std::queue<std::size_t> positions;
    positions.push(startIndex);
    while (!positions.empty())
    {
      auto next = positions.front();
      positions.pop();
      auto up = next >= width ? next - width : -1;
      auto down = next < (heightMap.size() - width) ? next + static_cast<int>(width) : -1;
      auto left = next % width != 0 ? next - 1 : -1;
      auto right = next % width != (width - 1) ? next + 1 : -1;

      for (auto p : { up, down, left, right })
      {
        if ((p != -1)
          && (previous[p] == -1)
          && heightMap[p] < (heightMap[next] + 2))
        {
          previous[p] = next;
          positions.push(p);
        }
      }
    }

    std::size_t stepCounter = 0;
    auto currPos = endIndex;
    while (currPos != startIndex)
    {
      currPos = previous[currPos];
      ++stepCounter;
    }

    std::cout << "Day 12 Part 1: " << stepCounter << '\n';
  }

  {
    std::vector<std::size_t> previous(heightMap.size(), -1);

    // BFS
    std::size_t idealStart = -1;
    std::queue<std::size_t> positions;
    positions.push(endIndex);
    while (!positions.empty())
    {
      auto next = positions.front();
      positions.pop();
      auto up = next >= width ? next - width : -1;
      auto down = next < (heightMap.size() - width) ? next + static_cast<int>(width) : -1;
      auto left = next % width != 0 ? next - 1 : -1;
      auto right = next % width != (width - 1) ? next + 1 : -1;

      for (auto p : { up, down, left, right })
      {
        if ((p != -1)
          && (previous[p] == -1)
          && (heightMap[p] + 2) > heightMap[next])
        {
          previous[p] = next;
          positions.push(p);
          if (heightMap[p] == 0) 
          {
            idealStart = p; 
            break;
          }
        }
      }

      if (idealStart != -1)
      {
        break;
      }
    }

    std::size_t stepCounter = 0;
    auto currPos = idealStart;
    while (currPos != endIndex)
    {
      currPos = previous[currPos];
      ++stepCounter;
    }

    std::cout << "Day 12 Part 2: " << stepCounter << '\n';
  }
}