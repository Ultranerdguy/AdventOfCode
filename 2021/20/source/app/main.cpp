// C++ include files
#include <iostream>
#include <fstream>
#include <string>

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
  
  std::string rulesetString;
  std::getline(input, rulesetString);
  bool ruleset[512]{};
  for (int i = 0; i < 512; ++i)
  {
    ruleset[i] = rulesetString[i] == '#';
  }
  std::getline(input, rulesetString); // skip empty line

  Image image;
  std::string imageLine;
  signed long long int index = 0;
  while (std::getline(input, imageLine))
  {
    image.AddRow(imageLine, index);
    ++index;
  }

  // Part 1
  image.Step(ruleset);
  image.Step(ruleset);

  std::cout << "Day 20 Part 1: " << image.CountTrue() << '\n';

  // Part 2
  for (int i = 2; i < 50; ++i)
  {
    image.Step(ruleset);
  }
  std::cout << "Day 20 Part 2: " << image.CountTrue() << '\n';

  return 0;
}