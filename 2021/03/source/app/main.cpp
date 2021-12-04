// C++ include files
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

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

  BinaryFilter FilterData;
  std::vector<unsigned long long> data;
  std::string line;
  unsigned long long lineCount = 0;
  while (std::getline(input, line) && !line.empty())
  {
    FilterData.AddLine(line);
    ++lineCount;
    std::size_t const size = line.size();
    data.resize(size);
    
    for (std::size_t i=0; i<size; ++i)
    {
      data[i] += (line[i] == '1' ? 1 : 0);
    }
  }

  // Part 1
  unsigned long long gammaRate = 0;
  unsigned long long epsilonRate = 0;
  std::size_t const size = data.size();
  for (std::size_t i=0; i<size; ++i)
  {
    gammaRate <<= 1;
    epsilonRate <<= 1;
    if (data[i] > lineCount/2)
    {
      gammaRate |= 1;
    }
    else
    {
      epsilonRate |= 1;
    }
  }
  std::cout << "Day 3 Part 1: " << (gammaRate * epsilonRate) << '\n';

  // Part 2
  BinaryFilter OGR = FilterData;
  BinaryFilter CSR = FilterData;
  std::size_t const lineSize = OGR.GetStringLength();
  for (std::size_t i=0; i<lineSize && OGR.GetCount() > 1; ++i)
  {
    char cOGR = OGR.GetCommon(i);
    OGR.FilterChar(i,cOGR); 
  }
  for (std::size_t i=0; i<lineSize && CSR.GetCount() > 1; ++i)
  {
    char cCSR = CSR.GetCommon(i) == '1' ? '0' : '1';
    CSR.FilterChar(i,cCSR);
  }
  std::cout << "Day 3 Part 2: " << (OGR.GetValue() * CSR.GetValue()) << '\n';
}