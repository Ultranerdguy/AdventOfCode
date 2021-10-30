#include "include.h"

// -----------------------------------------------------------------------------

void WireManager::AddWirePoint(std::size_t wire, const Point& point)
{
  if (wire >= m_wires.size())
  {
    m_wires.resize(wire+1);
  } 
  m_wires[wire].push_back(point);
}

std::vector<Point> WireManager::GetIntersections(std::size_t wire1, std::size_t wire2)
{
  std::vector<Point> output;
  if (wire1 < m_wires.size() && wire2 < m_wires.size())
  {
    const auto edge1Count = m_wires[wire1].size()-1;
    const auto edge2Count = m_wires[wire2].size()-1;
    for (std::size_t edge1 = 0; edge1 < edge1Count; ++edge1)
    {
      for (std::size_t edge2 = 0; edge2 < edge2Count; ++edge2)
      {
        auto intersections = GetIntersections(m_wires[wire1][edge1], m_wires[wire1][edge1+1], m_wires[wire2][edge2], m_wires[wire2][edge2+1]);
        output.resize(output.size() + intersections.size());
        for (auto& i : intersections)
        {
          output.push_back(i);
        }
      }
    }
  }
  return output;
}

std::vector<Point> WireManager::GetIntersections(const Point& A1, const Point& A2, const Point& B1, const Point& B2)
{
  std::vector<Point> output;
  auto E = B1-A1;
  auto F = A2-A1;
  auto G = B2-B1;
  double DetRecip = (G.x*F.y - F.x*G.y);
  if (DetRecip > 0)
  {
    auto S = (G.x*E.y - E.x*G.y)/DetRecip;
    auto T = (F.x*E.y - E.x*F.y)/DetRecip;
    if (0 <= S && S <= 1 && 0 <= T && T <= 1)
    {
      // Intersection success
      Point delta = A2 - A1;
      delta.x = std::round(S*delta.x);
      delta.y = std::round(S*delta.y);
      output.push_back(A1 + delta);
    }
  }
  else
  {
    // Lines parallel, check for overlap
    auto B = B2 - B1;
    auto A = A2 - A1;
    // Is A1 on B
    auto B1A1 = A1 - B1;
    if (B1A1.x*B.y == B1A1.y*B.x && 0 <= B1A1.x && B1A1.x < B.x) output.push_back(A1);
    auto B1A2 = A2 - B1;
    if (B1A2.x*B.y == B1A2.y*B.x && 0 <= B1A2.x && B1A2.x < B.x) output.push_back(A2);
    auto A1B1 = B1 - A1;
    if (A1B1.x*A.y == A1B1.y*A.x && 0 <= A1B1.x && A1B1.x < A.x) output.push_back(B1);
    auto A1B2 = B2 - A1;
    if (A1B2.x*A.y == A1B2.y*A.x && 0 <= A1B2.x && A1B2.x < A.x) output.push_back(B2);
  }
  return output;

}
Point WireManager::GetClosestPoint(const std::vector<Point>& points)
{
  return Point(0,0);
}