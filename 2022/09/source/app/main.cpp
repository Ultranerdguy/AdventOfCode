// C++ include files
#include <iostream>
#include <fstream>
#include <unordered_set>

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
  
  {
    XY head;
    XY tail{head};
    std::unordered_set<XY> visited{tail};
    Direction dir{};
    int dist{};
    while (input >> dir >> dist)
    {
      auto delta = XYFromDirection(dir);
      for (int i = 0; i < dist; ++i)
      {
        head.x += delta.x;
        head.y += delta.y;
        StepTailToHead(head, tail);
        visited.insert(tail);
      }
    }
    std::cout << "Day 09 Part 1: " << visited.size() << '\n';
  }

  // reset the file reader
  input.clear();
  input.seekg(0,std::ios::beg);
  {
    constexpr int knotCount = 10;
    XY knots[knotCount]{};
    std::unordered_set<XY> visited{knots[knotCount-1]};

    Direction dir{};
    int dist{};
    while (input >> dir >> dist)
    {
      auto delta = XYFromDirection(dir);
      for (int i = 0; i < dist; ++i)
      {
        knots[0].x += delta.x;
        knots[0].y += delta.y;
        for (int i=1;i<knotCount;++i)
        {
          StepTailToHead(knots[i-1], knots[i]);
        }
        visited.insert(knots[knotCount-1]);

        // std::ofstream output("output.txt", std::ios::app);
        // // Print (debug)
        // XY min{1000000,100000};
        // XY max{-100000,-100000};
        // for (int i=0;i<knotCount;++i)
        // {
        //   min.x = std::min(min.x, knots[i].x);
        //   min.y = std::min(min.y, knots[i].y);
        //   max.x = std::max(max.x, knots[i].x);
        //   max.y = std::max(max.y, knots[i].y);
        // }
        // for (XY::coord_t y = max.y; y >= min.y; --y)
        // {
        //   for (XY::coord_t x = min.x; x <= max.x; ++x)
        //   {
        //     char c = '.';
        //     for (int i=0;i<knotCount;++i)
        //       if (knots[i].x == x && knots[i].y == y)
        //       {
        //         c = i+'0';
        //         break;
        //       }
        //     output << c;
        //   }
        //   output << '\n';
        // }
        // output << "\n\n";
      }
    }
    std::cout << "Day 09 Part 2: " << visited.size() << '\n';
  }
}