// C++ include files
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <algorithm>

// Project specific files
#include "include.h"
#include "config.h"

using patternMap = std::map<std::string, char> ;
unsigned long long LoopPolymer(int loopCount, std::string polymer, patternMap map)
{
  for (int loop=0; loop<loopCount; ++loop)
  {
    for (int i=0; i < polymer.size()-1; ++i)
    {
      auto itr = map.find(polymer.substr(i,2));
      if (itr != map.end())
      {
        polymer.insert(i+1, 1, itr->second);
        ++i;
      }
    }
  }

  std::map<char, unsigned long long> counter;
  for (char c : polymer)
  {
    ++counter[c];
  }
  unsigned long long minCount = std::numeric_limits<int>::max();
  unsigned long long maxCount = 0;
  for (auto& p : counter)
  {
    if (p.second > maxCount) maxCount = p.second;
    if (p.second < minCount) minCount = p.second;
  }
  return maxCount - minCount;
}

unsigned long long LoopMappedPolymer(int loopCount, std::string polymer, patternMap map)
{
  std::map<std::string, unsigned long long> pairCounter;
  std::size_t const polySize = polymer.size();
  char lastChar = polymer[polySize-1];
  for (std::size_t i=0; i<polySize - 1; ++i)
  {
    ++pairCounter[polymer.substr(i, 2)];
  }
  decltype(pairCounter) pairCountTemp;
  
  for (int loop = 0; loop < loopCount; ++loop)
  {
    pairCountTemp.clear();
    for (auto& p : pairCounter)
    {
      auto itr = map.find(p.first);
      if (itr != map.end())
      {
        std::string str1 = std::string() + p.first[0] + itr->second;
        std::string str2 = std::string() + itr->second + p.first[1];
        pairCountTemp[str1] += p.second;
        pairCountTemp[str2] += p.second;
      }
    }
    std::swap(pairCounter, pairCountTemp);
  }

  // Count characters
  std::map<char, unsigned long long> counts;
  ++counts[lastChar];
  for (auto& p : pairCounter)
  {
    counts[p.first[0]] += p.second;
  }

  // Get the max-min difference
  unsigned long long min = std::numeric_limits<unsigned long long>::max();
  unsigned long long max = 0;
  for (auto& p : counts)
  {
    if (p.second > max) max = p.second;
    if (p.second < min) min = p.second;
  }
  return max - min;
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
  
  std::string polymerTemplate;
  input >> polymerTemplate;
  std::map<std::string, char> insertMap;
  std::string pattern;
  std::string insert;
  while (input >> pattern >> insert >> insert)
  {
    insertMap[pattern] = insert[0];
  }
  
  std::cout << "Day 14 Part 1: " << LoopPolymer(10, polymerTemplate, insertMap) << '\n';
  std::cout << "Day 14 Part 2: " << LoopMappedPolymer(40, polymerTemplate, insertMap) << '\n';
}