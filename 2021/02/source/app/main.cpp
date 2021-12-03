// C++ include files
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <numeric>

// Project specific files
#include "include.h"
#include "config.h"

struct Vec2
{
  int x = 0;
  int y = 0;
};

std::istream& operator>>(std::istream& lhs, Vec2& rhs)
{
  std::string direction;
  int distance = 0;
  if (lhs >> direction && !direction.empty() && lhs >> distance)
  {
    switch(direction[0])
    {
      case 'f': // forward
        rhs = {distance, 0};
        break;
      case 'u': // up
        rhs = {0, -distance};
        break;
      case 'd': // down
        rhs = {0, distance};
        break;
    }
  }
  return lhs;
}

Vec2 operator+(Vec2 const& lhs, Vec2 const& rhs)
{
  return Vec2{lhs.x + rhs.x, lhs.y + rhs.y};
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
  
  // Parse input
  std::vector<Vec2> deltas;
  Vec2 line;
  while (input >> line)
  {
    deltas.push_back(line);
  }

  // Part 1
  auto vecsum1 = std::accumulate(deltas.begin(), deltas.end(), Vec2());
  std::cout << "Day 2 Part 1: " << (vecsum1.x * vecsum1.y) << '\n';

  // Part 2
  int aim = 0;
  auto vecsum2 = std::accumulate(deltas.begin(), deltas.end(), Vec2(),
  [&aim](Vec2 const& lhs, Vec2 const& rhs)
  {
    Vec2 out = lhs;
    aim += rhs.y;
    out.x += rhs.x;
    out.y += rhs.x * aim;
    return out;
  });
  std::cout << "Day 2 Part 2: " << (vecsum2.x * vecsum2.y) << '\n';
  return 0;
}
