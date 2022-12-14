// C++ include files
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <set>
#include <algorithm>

// Project specific files
#include "include.h"
#include "config.h"

using obstacle_map = std::unordered_map<int, std::set<int>>;

int dropSandP1(obstacle_map obstacles)
{
  int restedGrains = 0;
  while (true)
  {
    XY pos{ 500,0 };
    bool fell = false;
    bool rested = false;
    while (!fell && !rested)
    {
      auto& col = obstacles[pos.x];
      int nextWall = -1;
      for (auto i : col)
      {
        if (i > pos.y)
        {
          nextWall = i;
          break;
        }
      }
      if (nextWall == -1) fell = true;
      else
      {
        pos.y = nextWall;
        auto& lCol = obstacles[pos.x - 1];
        auto& rCol = obstacles[pos.x + 1];
        if (lCol.find(pos.y) == lCol.end()) --pos.x; // Left is free
        else if (rCol.find(pos.y) == rCol.end()) ++pos.x; // Right is free
        else
        {
          col.insert(pos.y - 1); // Come to rest in this column
          rested = true;
        }
      }
    }
    if (fell) break;
    ++restedGrains;
  }
  return restedGrains;
}

int dropSandP2(obstacle_map obstacles, int max_y)
{
  int restedGrains = 0;
  while (true)
  {
    XY pos{ 500,0 };
    bool fell = false;
    bool rested = false;
    while (!fell && !rested)
    {
      auto& col = obstacles[pos.x];
      if (col.find(pos.y) != col.end())
      {
        fell = true;
        break;
      }
      col.insert(max_y);
      int nextWall = -1;
      for (auto i : col)
      {
        if (i > pos.y)
        {
          nextWall = i;
          break;
        }
      }
      if (nextWall == -1) fell = true;
      else
      {
        pos.y = nextWall;
        auto& lCol = obstacles[pos.x - 1];
        auto& rCol = obstacles[pos.x + 1];
        lCol.insert(max_y);
        rCol.insert(max_y);
        if (lCol.find(pos.y) == lCol.end()) --pos.x; // Left is free
        else if (rCol.find(pos.y) == rCol.end()) ++pos.x; // Right is free
        else
        {
          col.insert(pos.y - 1); // Come to rest in this column
          rested = true;
        }
      }
    }
    if (fell) break;
    ++restedGrains;
  }
  return restedGrains;
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

  obstacle_map obstaclesOriginal;
  
  std::string line;
  int max_y = 0;
  while (std::getline(input, line) && !line.empty())
  {
    Polyline pointLine;
    std::stringstream lineStrm(line);
    XY pnt;
    while (lineStrm >> pnt)
    {
      pointLine.AddPoint(pnt);
      lineStrm >> (std::string()); // skip next word
    }

    // For each point in the polyline, add to the obstacle map
    for (auto p : pointLine)
    {
      obstaclesOriginal[p.x].insert(p.y);
      if (p.y > max_y) max_y = p.y;
    }
  }

  std::cout << "Day 14 Part 1: " << dropSandP1(obstaclesOriginal) << '\n';
  std::cout << "Day 14 Part 2: " << dropSandP2(obstaclesOriginal, max_y+2) << '\n';

  return 0;
}