// C++ include files
#include <iostream>
#include <fstream>
#include <sstream>

// Project specific files
#include "include.h"
#include "config.h"

std::size_t GetUniqueSubStringIndex(std::string const& content, std::size_t length)
{
  std::size_t const contentSize = content.size();
  std::size_t index = 0;
  for (; index < contentSize-3; ++index)
  {
    bool matched = false;
    for (std::size_t i = 0; i < length-1; ++i)
    {
      for (std::size_t j = i+1; j < length; ++j)
      {
        if (content[index+i] == content[index+j])
        {
          index += i;
          matched = true;
          break;
        }
      }
      if (matched)
      {
        break;
      }
    }
    if (!matched)
    {
      break;
    }
  }
  return index+length;
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
  
  std::stringstream fileContentStream;
  fileContentStream << input.rdbuf();
  std::string fileContent = fileContentStream.str();

  std::size_t index = GetUniqueSubStringIndex(fileContent, 4);
  std::cout << "Day 06 Part 1: " << index << '\n';

  index = GetUniqueSubStringIndex(fileContent, 14);
  std::cout << "Day 06 Part 2: " << index << '\n';
}