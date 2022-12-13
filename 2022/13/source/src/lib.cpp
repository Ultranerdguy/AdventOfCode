#include "include.h"
#include <sstream>

List::List(std::string const& l)
{
  Parse(std::stringstream{l});
}

void List::Parse(std::stringstream& line)
{
  // Assumes line starts with '[' and ends with ']'
  line.get();
  char c;
  while (line && (c = std::stringstream::traits_type::to_char_type(line.peek())) != ']')
  {
    if (c == '[')
    {
      children.push_back(List{});
      children.back().Parse(line);
    }
    else if (c == ',')
    {
      line.get();
    }
    else
    {
      List value;
      line >> value.value;
      children.push_back(value);
    }
  }
  line.get();
}

int Compare(List const& lhs, List const& rhs)
{
  // If both are values, compare directly
  if (lhs.value != -1 && rhs.value != -1)
    return lhs.value < rhs.value ? -1 : (lhs.value == rhs.value) ? 0 : 1;

  // If one is a value and the other isn't, promote the value to a list, and compare
  if (lhs.value != -1 || rhs.value != -1)
  {
    List const* pL = &lhs;
    List const* pR = &rhs;
    List lSub;
    List rSub;
    if (lhs.value != -1)
    {
      lSub.children.push_back(lhs);
      pL = &lSub;
    }
    if (rhs.value != -1)
    {
      rSub.children.push_back(rhs);
      pR = &rSub;
    }
    return Compare(*pL, *pR);
  }
  
  // Compare lists directly
  auto lSize = lhs.children.size();
  auto rSize = rhs.children.size();
  std::size_t minLen = std::min(lSize, rSize);
  for (std::size_t i = 0; i < minLen; ++i)
  {
    int cVal = Compare(lhs.children[i], rhs.children[i]);
    if (cVal == 0) continue;
    return cVal;
  }

  // Compare list lengths
  return lSize < rSize ? -1 : (lSize == rSize) ? 0 : 1;
}