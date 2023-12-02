// C++ include files
#include <iostream>
#include <string>
#include <fstream>
#include <string_view>

// Project specific files
#include "include.h"
#include "config.h"

struct NumberWord
{
  std::string_view word;
  unsigned int number;
};

unsigned int FindValue(std::string_view source)
{
  NumberWord numberWords[] = {
    {"one",1},
    {"two",2},
    {"three",3},
    {"four",4},
    {"five",5},
    {"six",6},
    {"seven",7},
    {"eight",8},
    {"nine",9}
  };
  for (auto& nw : numberWords)
  {
    if (source.substr(0, nw.word.size()) == nw.word)
      return nw.number;
  }
  return 0;
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

  unsigned int runningTotal1 = 0;
  std::string line;
  while (std::getline(input, line) && !line.empty())
  {
    // forward iterate to find the first character
    for (char c : line)
    {
      if (std::isdigit(c))
      {
        runningTotal1 += (c-'0')*10;
        break;
      }
    }

    // backwards iterate to find last character, using reverse iterator
    for (auto itr = line.rbegin(); itr != line.rend(); ++itr)
    {
      if (std::isdigit(*itr))
      {
        runningTotal1 += (*itr-'0');
        break;
      }
    }
  }

  std::cout << "Day 1 Part 1: " << runningTotal1 << '\n';
  
  input.clear();
  input.seekg(0, input.beg);

  unsigned int runningTotal2 = 0;
  while(std::getline(input, line) && !line.empty())
  {
    unsigned int value = 0;
    unsigned int lastFound = 0;
    for (char& c : line)
    {
      if (value == 0) // First value found
      {
        unsigned int i = 0;
        if (std::isdigit(c))
          value = (c-'0');
        else if ((i = FindValue(&c)) != 0)
          value = i;
        lastFound = value;
        value *= 10;
      }
      else
      {
        unsigned int i = 0;
        if (std::isdigit(c))
          lastFound = (c-'0');
        else if ((i = FindValue(&c)) != 0)
          lastFound = i;
      }
    }
    value += lastFound;
    runningTotal2 += value;
  }

  std::cout << "Day 1 Part 2: " << runningTotal2 << '\n';
}