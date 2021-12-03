#ifndef _AOC_INCLUDE_H_
#define _AOC_INCLUDE_H_

#include <cmath>
#include <vector>

class Point
{
public:
  inline constexpr Point(const int _x = 0, const int _y = 0);
  inline int Length2();
  int x;
  int y;
};

inline constexpr int Dot(const Point& lhs, const Point& rhs);
inline constexpr Point operator+(const Point& lhs, const Point& rhs);
inline constexpr Point operator-(const Point& lhs, const Point& rhs);
inline constexpr Point operator-(const Point& pnt);
inline constexpr Point operator*(const int lhs, const Point& rhs);
inline constexpr Point operator*(const Point& lhs, const int rhs);
inline constexpr bool operator==(const Point& lhs, const Point& rhs);
inline constexpr bool operator!=(const Point& lhs, const Point& rhs);

class WireManager
{
public:
  void AddWirePoint(std::size_t wire, const Point& point);

  std::vector<Point> GetIntersections(std::size_t wire1, std::size_t wire2);
  std::vector<Point> GetIntersections(const Point& A1, const Point& A2, const Point& B1, const Point& B2);
  std::vector<Point>& GetWire(std::size_t wire);
  
protected:
  std::vector<std::vector<Point>> m_wires;
};

// Implementation
// For templates and constexpr only

constexpr Point::Point(const int _x, const int _y)
  : x(_x)
  , y(_y)
{}

int Point::Length2()
{
  return x*x + y*y;
}

constexpr int Dot(const Point& lhs, const Point& rhs)
{
  return lhs.x*rhs.x + lhs.y*rhs.y;
}

constexpr Point operator+(const Point& lhs, const Point& rhs)
{
  return Point(lhs.x + rhs.x, lhs.y + rhs.y);
}

constexpr Point operator-(const Point& lhs, const Point& rhs)
{
  return Point(lhs.x - rhs.x, lhs.y - rhs.y);
}

constexpr Point operator-(const Point& pnt)
{
  return Point(-pnt.x, -pnt.y);
}

constexpr Point operator*(const int lhs, const Point& rhs)
{
  return Point(rhs.x * lhs, rhs.y * lhs);
}

constexpr Point operator*(const Point& lhs, const int rhs)
{
  return rhs * lhs;
}

constexpr bool operator==(const Point& lhs, const Point& rhs)
{
  return lhs.x == rhs.x && lhs.y == rhs.y;
}

constexpr bool operator!=(const Point& lhs, const Point& rhs)
{
  return !(lhs == rhs);
}

#endif