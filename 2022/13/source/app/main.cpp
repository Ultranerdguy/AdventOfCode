// C++ include files
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

// Project specific files
#include "include.h"
#include "config.h"

bool ListPtrCompare(List const* lhs, List const* rhs)
{
  return Compare(*lhs, *rhs) < 0;
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

  std::vector<List> packets;
  
  std::size_t indexSum = 0;
  std::size_t index = 0;
  std::string line1;
  std::string line2;
  while (std::getline(input, line1) && std::getline(input, line2))
  {
    ++index;
    List l1(line1);
    List l2(line2);

    if (Compare(l1,l2) < 0)
    {
      indexSum += index;
    }
    
    packets.emplace_back(l1);
    packets.emplace_back(l2);

    std::getline(input, line1); // Skip empty line
  }

  std::cout << "Day 13 Part 1: " << indexSum << '\n';

  List p1("[[2]]");
  List p2("[[6]]");

  std::vector<List*> packetPointers;
  packetPointers.reserve(packets.size() + 2);
  for (auto& l : packets) packetPointers.push_back(&l);
  packetPointers.push_back(&p1);
  packetPointers.push_back(&p2);

  std::sort(packetPointers.begin(), packetPointers.end(), ListPtrCompare);

  std::size_t p1Index = 0;
  std::size_t p2Index = 0;
  std::size_t const packetCount = packetPointers.size();
  for (std::size_t i = 0; i < packetCount; ++i)
  {
    if (packetPointers[i] == &p1) p1Index = i;
    if (packetPointers[i] == &p2) p2Index = i;
  }

  std::cout << "Day 14 Part 2: " << ((p1Index + 1) * (p2Index + 1)) << '\n';
}