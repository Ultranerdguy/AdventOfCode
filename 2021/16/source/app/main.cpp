// C++ include files
#include <iostream>
#include <fstream>
#include <string>
#include <bitset>
#include <sstream>

// Project specific files
#include "include.h"
#include "config.h"

int main(int argc, char* argv[])
{
  if (argc < 2)
  {
    std::cout << "Usage: \n";
    std::cout << "  " << EXECUTABLE << " <input file>\n";
    return 1;
  }
  std::ifstream input(argv[1]);
  
  std::string hex;;
  std::getline(input, hex);
  std::stringstream binStream;
  for (char c : hex)
  {
    std::stringstream charStrm;
    charStrm << c;
    uint16_t n;
    charStrm >> std::hex >> n;
    std::bitset<4> bits{ n };
    binStream << bits;
  }
  PacketReader reader(binStream.str());
  reader.EvaluatePacket();
  std::cout << "Day 16 Part 1: " << reader.CountVersions() << '\n';
  std::cout << "Day 16 Part 2: " << reader.Evaluate() << '\n';
  return 0;
}