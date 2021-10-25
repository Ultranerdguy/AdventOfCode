// C++ include files
#include <iostream>
#include <fstream>
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
  std::vector<OPCODE> initialCode;
  OPCODE val = 0;
  while (input >> val)
  {
    initialCode.push_back(val);
    input.get(); // Skip char
  }

  // Part 1
  auto opCode = initialCode;
  const size_t size = opCode.size();
  opCode[1] = 12;
  opCode[2] = 02;
  std::cout << "Part 1: " << ParseOpcode(opCode.data(), opCode.size()) << '\n';

  // Part 2
  int inputCombo = [&initialCode]()
  {
    for (OPCODE i=0; i<100; ++i)
    {
      for (OPCODE j=0; j<100; ++j)
      {
        auto opCode = initialCode;
        opCode[1] = i;
        opCode[2] = j;
        if (ParseOpcode(opCode.data(), opCode.size()) == 19690720)
        {
          return opCode[1] * 100 + opCode[2];
        }
      }
    }
    return 0;
  }();
  std::cout << "Part 2: " << inputCombo << '\n';
}