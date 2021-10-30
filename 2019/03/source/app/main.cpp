// C++ include files
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <limits>

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

  // Read and parse input
  std::ifstream input(argv[1]);
  WireManager wires;
  std::string line;
  size_t lineCount = 0;
  while ((std::getline(input, line),!line.empty()))
  {
    Point currentPosition;
    std::stringstream lineStream(line);
    while (lineStream)
    {
      Point direction;
      switch (lineStream.get())
      {
        case 'U':
          direction.y = 1;
          break;
        case 'L':
          direction.x = -1;
          break;
        case 'R':
          direction.x = 1;
          break;
        case 'D':
        direction.y = -1;
          break;        
      }
      int distance;
      lineStream >> distance;
      if (distance > 0)
      {
        currentPosition = currentPosition + (distance*direction);
        wires.AddWirePoint(lineCount, currentPosition);
      }
      lineStream.get();
    }
    ++lineCount;
  }

  auto intersections = wires.GetIntersections(0,1);
  int closest = std::numeric_limits<int>::max();
  Point closestPoint;
  for (auto& i : intersections)
  {
    if (i.x != 0 && i.y != 0)
    {
      int dist = abs(i.x) + abs(i.y);
      if (dist < closest)
      {
        closestPoint = i;
        closest = dist;
      }
    }
  }
  std::cout << closestPoint.x << " " << closestPoint.y << " " << closest << '\n';

  return 0;
}