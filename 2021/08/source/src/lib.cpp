#include "include.h"
#include <algorithm>

void NumberCode::AddSegment(char s)
{
  m_segments.push_back(s);
}

std::string const& NumberCode::GetSegments() const
{
  return m_segments;
}

std::string& NumberCode::GetSegments()
{
  return m_segments;
}

std::istream& operator>>(std::istream& lhs, NumberCode& rhs)
{
  std::string word;
  if (lhs >> word)
  {
    for (char c : word)
    {
      rhs.AddSegment(c);
    }
  }
  return lhs;
}

void Display::Reset()
{
  m_inputs.clear();
  m_output.clear();
  std::fill(m_mapping, m_mapping+10, -1);
}

void Display::AddInput(NumberCode const& code)
{
  NumberCode cpy = code;
  auto& seg = cpy.GetSegments();
  std::sort(seg.begin(), seg.end());
  m_inputs.emplace_back(cpy);
}

void Display::AddOutput(NumberCode const& code)
{
  NumberCode cpy = code;
  auto& seg = cpy.GetSegments();
  std::sort(seg.begin(), seg.end());
  m_output.emplace_back(cpy);
}

void Display::MapValues()
{
  std::sort(m_inputs.begin(), m_inputs.end(), 
  [](NumberCode const& lhs, NumberCode const& rhs)
  {
    return lhs.GetSegments().size() < rhs.GetSegments().size();
  });
  // After sorting, the inputs are in order {1,7,4,?,?,?,?,?,?,8}
  m_mapping[1] = 0;
  m_mapping[4] = 2;
  m_mapping[7] = 1;
  m_mapping[8] = 9;

  // Now go through all the inputs by size, and map them
  for (int i = 3; i<6; ++i)
  {
    // size 5 inputs
    NumberCode& code = m_inputs[i];
    std::string const& seg = code.GetSegments();
    // Union with "1"
    auto out1 = Union(seg, m_inputs[0].GetSegments());
    auto out4 = Union(seg, m_inputs[2].GetSegments());
    if (out1.size() == 5)
    {
      m_mapping[3] = i;
    }
    else if (out4.size() == 7)
    {
      m_mapping[2] = i;
    }
    else
    {
      m_mapping[5] = i;
    }
  }

  for (int i = 6; i<9; ++i)
  {
    // size 6 inputs
    NumberCode& code = m_inputs[i];
    std::string out(' ',7);
    std::string const& seg = code.GetSegments();
    auto out1 = Union(seg, m_inputs[0].GetSegments());
    auto out5 = Union(seg, m_inputs[m_mapping[5]].GetSegments());
    if (out1.size() == 7)
    {
      m_mapping[6] = i;
    }
    else if (out5.size() == 7)
    {
      m_mapping[0] = i;
    }
    else
    {
      m_mapping[9] = i;
    }
  }
}

unsigned int Display::GetOutputValue() const
{
  unsigned int out = 0;
  for (auto& v : m_output)
  {
    auto const& seg = v.GetSegments();
    out *= 10;
    for (int i=0; i<10; ++i)
    {
      if (m_inputs[m_mapping[i]].GetSegments() == seg)
      {
        out += i;
        break;
      }
    }
  }
  return out;
}

std::vector<NumberCode> const& Display::GetInputs() const
{
  return m_inputs;
}

std::vector<NumberCode> const& Display::GetOutput() const
{
  return m_output;
}

std::istream& operator>>(std::istream& lhs, Display& rhs)
{
  rhs.Reset();
  for (int i=0; i<10 && lhs; ++i)
  {
    NumberCode code;
    if (lhs >> code)
    {
      rhs.AddInput(code);
    }
  }

  lhs.ignore(3,'|');

  for (int i=0; i<4 && lhs; ++i)
  {
    NumberCode code;
    if (lhs >> code)
    {
      rhs.AddOutput(code);
    }
  }
  return lhs;
}

std::string Display::Union(std::string const& lhs, std::string const& rhs)
{
  std::string out(' ', 7);
  auto e = std::set_union(begin(lhs), end(lhs), begin(rhs), end(rhs), begin(out));
  out.resize(e-begin(out));
  return out;
}