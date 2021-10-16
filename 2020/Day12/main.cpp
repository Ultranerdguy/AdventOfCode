#include <iostream>
#include <fstream>
#include <vector>
#include <string>

struct Point
{
  double x = 0, y = 0;
};

Point& operator+=(Point& lhs, const Point& rhs)
{
  lhs.x += rhs.x;
  lhs.y += rhs.y;
  return lhs;
}

Point operator*(const double lhs, const Point& rhs)
{
  return Point{ lhs * rhs.x, lhs * rhs.y };
}

inline double degToRad(const double d)
{
  constexpr double ratio = 3.141592653589 / 180.0;
  return ratio * d;
}

int main()
{
  std::ifstream file("Input.txt");

  // Read from file
  std::vector<std::string> instructions;
  while (file)
  {
    std::string line;
    std::getline(file, line);
    if (!line.empty())
    {
      instructions.push_back(line);
    }
  }

  // Part 1
  Point pos;
  int rotation = 0;
  for (auto& line : instructions)
  {
    double value = static_cast<double>(std::stoi(line.substr(1)));

    switch (line[0])
    {
      case 'N':
        pos += Point{ 0,value };
        break;
      case 'S':
        pos += Point{ 0,-value };
        break;
      case 'E':
        pos += Point{ value, 0 };
        break;
      case 'W':
        pos += Point{ -value, 0 };
        break;
      case 'R':
        value = -value;
        [[fallthrough]];
      case 'L':
        rotation += value;
        break;
      case 'F':
        pos += Point{ value * cos(degToRad(static_cast<double>(rotation))), value * sin(degToRad(static_cast<double>(rotation))) };
        break;
    }
  }
  std::cout << "Part 1: " << (abs(pos.x) + abs(pos.y)) << '\n';

  // Part 2
  pos = Point{ 0,0 };
  Point waypoint{ 10,1 };
  for (auto& line : instructions)
  {
    double value = static_cast<double>(std::stoi(line.substr(1)));
    double angle = degToRad(value);
    switch (line[0])
    {
      case 'N':
        waypoint += Point{ 0,value };
        break;
      case 'S':
        waypoint += Point{ 0,-value };
        break;
      case 'E':
        waypoint += Point{ value, 0 };
        break;
      case 'W':
        waypoint += Point{ -value, 0 };
        break;
      case 'R':
        angle = -angle;
        [[fallthrough]];
      case 'L':
        waypoint = Point{ waypoint.x * cos(angle) - waypoint.y * sin(angle),
          waypoint.x * sin(angle) + waypoint.y * cos(angle) };
        break;
      case 'F':
        pos += value * waypoint;
        break;
    }
  }
  std::cout << "Part 2: " << (abs(pos.x) + abs(pos.y)) << '\n';
}