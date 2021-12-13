// C++ include files
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <set>
#include <map>

// Project specific files
#include "include.h"
#include "config.h"

struct Pos
{
  int x = 0;
  int y = 0;
};

bool operator<(Pos const& lhs, Pos const& rhs)
{
  return lhs.x == rhs.x ? lhs.y < rhs.y : lhs.x < rhs.x;
}

bool operator==(Pos const& lhs, Pos const& rhs)
{
  return lhs.x == rhs.x && lhs.y == rhs.y;
}

void PrintPoints(std::set<Pos>& points)
{
  std::stringstream out;
  Pos min;
  Pos max;
  std::map<int, std::map<int, bool>> pointMap;
  for (auto& pos : points)
  {
    pointMap[pos.x][pos.y] = true;
    if (pos.x < min.x) min.x = pos.x;
    if (pos.x > max.x) max.x = pos.x;
    if (pos.y < min.y) min.y = pos.y;
    if (pos.y > max.y) max.y = pos.y;
  }

  for (int y = min.y; y <= max.y; ++y)
  {
    for (int x = min.x; x <= max.x; ++x)
    {
      if (pointMap[x][y]) out << '#';
      else out << ' ';
    }
    out << '\n';
  }
  std::cout << out.str();
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
  
  std::set<Pos> pointsOriginal;
  std::vector<int> xMirror;
  std::vector<int> yMirror;
  std::string line;
  while (std::getline(input, line))
  {
    if (line.empty()) break; // Line break between fold instructions and points

    std::stringstream lineStream(line);
    Pos point;
    lineStream >> point.x;
    lineStream.ignore(std::numeric_limits<std::streamsize>::max(),',');
    lineStream >> point.y;
    pointsOriginal.insert(point);
  }
  enum class FirstMirror {None, X, Y} firstOp = FirstMirror::None;
  // Read in the fold instructions
  while (std::getline(input, line))
  {
    auto const coordPos = line.find_first_of('=') - 1;
    std::stringstream lineStream(line.substr(coordPos+2));
    int val;
    if (lineStream >> val)
    {
      switch (line[coordPos])
      {
        case 'x':
          xMirror.push_back(val);
          if (firstOp == FirstMirror::None) firstOp = FirstMirror::X;
          break;
        case 'y':
          yMirror.push_back(val);
          if (firstOp == FirstMirror::None) firstOp = FirstMirror::Y;
          break;
      }
    }
  }

  {
    std::set<Pos> points;
    switch (firstOp)
    {
      case FirstMirror::X:
      {
        int mirror = xMirror.front();
        for (auto& point : pointsOriginal)
        {
          points.insert({ point.x > mirror ? 2 * mirror - point.x : point.x, point.y });
        }
        break;
      }
      case FirstMirror::Y:
      {
        int mirror = yMirror.front();
        for (auto& point : pointsOriginal)
        {
          points.insert({ point.x, point.y > mirror ? 2 * mirror - point.y : point.y });
        }
        break;
      }
    }
    std::cout << "Day 13 Part 1: " << points.size() << '\n';
  }

  {
    std::set<Pos> points;
    for (auto& point : pointsOriginal)
    {
      Pos newPoint = point;
      for (auto mirror : xMirror)
      {
        newPoint = { newPoint.x > mirror ? 2 * mirror - newPoint.x : newPoint.x, newPoint.y };
      }
      for (auto mirror : yMirror)
      {
        newPoint = { newPoint.x, newPoint.y > mirror ? 2 * mirror - newPoint.y : newPoint.y };
      }
      points.insert(newPoint);
    }
    std::cout << "Day 13 Part 2: " << '\n';
    PrintPoints(points);
  }

  return 0;
}

