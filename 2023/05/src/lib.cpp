#include "include.h"
#include <string>
#include <iostream>

PiecewiseFunction::PiecewiseFunction()
{
  Reset();
}

void PiecewiseFunction::Reset()
{
  m_map.clear();
  m_map.push_back({std::numeric_limits<value_t>::lowest(),0});
}

void PiecewiseFunction::Insert(value_t start, value_t offset, value_t count)
{
  auto itr = m_map.begin();

  value_t oldOffset = (*this)(start+count) - (start+count);
  InsertForce(start, offset);
  InsertIfNotFound(start+count, oldOffset);
}

value_t PiecewiseFunction::operator()(value_t index) const
{
  value_t output = index;

  value_t lastOffset = 0;
  for (auto& p : m_map) 
  {
    if (index < p.start)
    {
      output += lastOffset;
      break;
    }
    lastOffset = p.offset;
  }

  return output;
}

void PiecewiseFunction::Reduce()
{
  if (m_map.size() < 2) return;
  auto itr = ++m_map.begin();
  auto jtr = m_map.begin();
  while (itr != m_map.end())
  {
    if (jtr->offset == itr->offset) itr = m_map.erase(itr);
    if (itr == m_map.end()) break;
    jtr = itr++;
  }
}

PiecewiseFunction::ranges_t PiecewiseFunction::GetRanges(value_t start, value_t end) const
{
  ranges_t output;
  if (end <= start) return output;

  for (auto& r : m_map)
  {
    if (start <= r.start && r.start < end) output.push_back(r);
  }
  if (output.empty() || output.front().start != start)
    output.insert(output.begin(), {start, (*this)(start)-start});

  return output;
}

void PiecewiseFunction::InsertIfNotFound(value_t start, value_t offset)
{
  auto itr = m_map.begin();
  while (itr != m_map.end() && itr->start < start) ++itr;
  if (itr != m_map.end() && itr->start == start) return;
  m_map.insert(itr, {start, offset});
}

void PiecewiseFunction::InsertForce(value_t start, value_t offset)
{
  auto itr = m_map.begin();
  while (itr != m_map.end() && itr->start < start) ++itr;
  if (itr != m_map.end() && itr->start == start) itr->offset = offset;
  else m_map.insert(itr, {start, offset});
}

PiecewiseFunction Compose(PiecewiseFunction const& first, PiecewiseFunction const& second)
{
  PiecewiseFunction output;
  for (std::size_t i=0; i<first.m_map.size(); ++i)
  {
    auto const& range = first.m_map[i];
    auto const& range2 = (i+1) < first.m_map.size() ? first.m_map[i+1] : PiecewiseFunction::StartOffsetPair{std::numeric_limits<value_t>::max(), 0};
    auto intersectingRanges = second.GetRanges(range.start+range.offset, range2.start+range.offset);
    for (auto& r : intersectingRanges)
    {
      output.InsertForce(r.start - range.offset, r.offset + range.offset);
    }
  }
  return output;
}

std::istream& operator>>(std::istream& input, PiecewiseFunction& function)
{
  function.Reset();
  std::string word;
  if (!(input >> word) || !(input >> word)) return input;

  value_t dest, start, count;
  while (input >> dest >> start >> count)
  {
    function.Insert(start, dest-start, count);
  }

  function.Reduce();

  input.clear();

  return input;
}