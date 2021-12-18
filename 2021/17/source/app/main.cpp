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
  
  std::string word;
  int xMin = 0;
  int xMax = std::numeric_limits<int>::max();
  int yMin = 0;
  int yMax = std::numeric_limits<int>::max();

  input.ignore(std::numeric_limits<std::streamsize>::max(), '=');
  input >> xMin;
  input.ignore(2);
  input >> xMax;
  input.ignore(std::numeric_limits<std::streamsize>::max(), '=');
  input >> yMin;
  input.ignore(2);
  input >> yMax;

  int maxHeight = 0;
  int counter = 0;
  int yRangeMax = -yMin - 1;
  int xRangeMin = std::floor(std::sqrt(xMin));
  for (int yv = yMin; yv <= yRangeMax; ++yv)
  {
    for (int xv = xRangeMin; xv < xMax+1; ++xv)
    {
      int dx = xv;
      int dy = yv;
      int probeX = 0;
      int probeY = 0;
      while (true)
      {
        if (probeX > xMax || probeY < yMin) break;
        if (probeX <= xMax && probeX >= xMin
        && probeY <= yMax && probeY >= yMin)
        {
          ++counter;
          break;
        }
        probeX += dx;
        probeY += dy;
        dx = dx != 0 ? dx - (abs(dx)/dx) : 0;
        dy -= 1;
        if (probeY > maxHeight) maxHeight = probeY;
      }
    }
  }
  std::cout << "Day 17 Part 1: " << maxHeight << '\n';
  std::cout << "Day 17 Part 2: " << counter << '\n';


  return 0;
}