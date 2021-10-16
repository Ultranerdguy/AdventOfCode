#include <iostream>
#include <fstream>
#include <string>

size_t countBits(uint32_t val)
{
  // SWAR algorithm to count bits
  val = val - ((val >> 1) & 0x55555555);
  val = (val & 0x33333333) + ((val >> 2) & 0x33333333);
  return (((val + (val >> 4)) & 0x0F0F0F0F) * 0x01010101) >> 24;
}

int main()
{
  std::ifstream file("Input.txt");

  uint32_t answersP1 = 0;
  uint32_t answersP2 = -1; // All bits set
  size_t sumP1 = 0;
  size_t sumP2 = 0;
  std::string line;
  while (file)
  {
    std::getline(file, line);
    if (!line.empty() && file)
    {
      uint32_t thisLine = 0;
      for (char& c : line)
      {
        answersP1 |= 1 << (c - 'a');
        thisLine  |= 1 << (c - 'a');
      }
      answersP2 &= thisLine;
    }
    else
    {
      sumP1 += countBits(answersP1);
      answersP1 = 0;
      sumP2 += countBits(answersP2);
      answersP2 = -1;
    }
  }
  std::cout << "Part 1: " << sumP1 << '\n';
  std::cout << "Part 2: " << sumP2 << '\n';
}