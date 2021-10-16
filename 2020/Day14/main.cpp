#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <bitset>
#include <unordered_map>

int main()
{
  std::ifstream file("Input.txt");

  enum state : char {T,F,X};

  std::bitset<36> maskbits;
  std::bitset<36> maskstate;
  
  std::unordered_map<uint64_t, uint64_t> mem;

  std::vector<std::string> lines;
  while (file)
  {
    std::string line;
    std::getline(file, line);
    if (!line.empty())
    {
      lines.push_back(line);
    }
  }

  // Part 1
  for (auto line : lines)
  {
    if (line.substr(0, 4) == "mask")
    {
      auto mask = line.substr(7);
      maskbits = 0;
      maskstate = 0;
      const size_t masklen = mask.size();
      for (size_t i = 0; i < masklen; ++i)
      {
        const char c = mask[masklen - 1 - i];
        maskbits[i] = (c == 'X');
        maskstate[i] = (!maskbits[i] && c == '1');
      }
    }
    else
    {
      std::stringstream str(line.substr(4));
      uint64_t index;
      str >> index;
      str.ignore(4);
      uint64_t val;
      str >> val;
      val &= maskbits.to_ullong();
      val |= maskstate.to_ullong();
      mem[index] = val;
    }
  }
  uint64_t sm = 0;
  for (auto& [key, val] : mem)
  {
    sm += val;
  }
  std::cout << "Part 1: " << sm << '\n';

  // Part 2
  maskbits = 0;
  maskstate = 0;
  mem.clear();
  char xCount = 0;
  for (auto line : lines)
  {
    if (line.substr(0, 4) == "mask")
    {
      auto mask = line.substr(7);
      maskbits = 0;
      maskstate = 0;
      xCount = 0;
      const size_t masklen = mask.size();
      for (size_t i = 0; i < masklen; ++i)
      {
        const char c = mask[masklen - 1 - i];
        if (c == 'X')
        {
          maskbits[i] = 1;
          ++xCount;
        }
        maskstate[i] = (!maskbits[i] && c == '1');
      }
    }
    else
    {
      std::stringstream str(line.substr(4));
      uint64_t index;
      str >> index;
      str.ignore(4);
      uint64_t val;
      str >> val;

      index |= maskstate.to_ullong();
      const uint64_t lim = (unsigned long long)2 << xCount;
      for (uint64_t i = 0; i < lim; ++i)
      {
        std::bitset<36> bits = i;
        std::bitset<36> modifier = index;
        uint64_t bindex = 0;
        for (uint64_t j = 0; j < 36; ++j)
        {
          if (maskbits[j]) // If 'X'
          {
            modifier[j] = bits[bindex];
            ++bindex;
          }
        }
        mem[modifier.to_ullong()] = val;
      }
    }
  }

  sm = 0;
  for (auto& [key, val] : mem)
  {
    sm += val;
  }
  std::cout << "Part 2: " << sm << '\n';
}