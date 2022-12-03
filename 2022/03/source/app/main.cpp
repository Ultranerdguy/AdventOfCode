// C++ include files
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

// Project specific files
#include "include.h"
#include "config.h"

int GetLetterScore(char c)
{
  int const charInt = std::char_traits<char>::to_int_type(c);
  return (tolower(charInt)-'a'+1+(isupper(charInt)*26));
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
  std::vector<std::string> lines;
  
  std::string line;
  while (std::getline(input, line) && !line.empty())
  {
    lines.push_back(line);
  }

  // Part 1
  int priorityScorePart1 = 0;
  for (auto& line : lines)
  {
    bool found[52]{};
    std::size_t const rucksackSize = line.size();

    // First pass, flag each letter
    // Letter score can be used as an index, with an adjustment for zero-index
    for (std::size_t i = 0; i < (rucksackSize/2); ++i)
      found[GetLetterScore(line[i])-1] = true;
    // Second pass, find the duplicate
    for (std::size_t i = (rucksackSize/2); i < rucksackSize; ++i)
    {
      int score = GetLetterScore(line[i]);
      if (found[score-1])
      {
        priorityScorePart1 += score;
        break;
      }
    }
  }

  // Part 2
  int priorityScorePart2 = 0;
  std::size_t const groupCount = lines.size()/3;
  for (std::size_t group = 0; group < groupCount; ++group)
  {
    // Index as [letter][elfIndex]
    bool found[52][3]{};

    // Iterate over the group
    for (int elfIndex = 0; elfIndex < 3; ++elfIndex)
    {
      auto& line = lines[group*3+elfIndex];
      for (char c : line)
      {
        found[GetLetterScore(c)-1][elfIndex] = true;
      }
    }

    // Find which letter has 3 trues
    for (int i = 0; i < 52; ++i)
    {
      if (found[i][0] && found[i][1] && found[i][2])
      {
        priorityScorePart2 += i+1;
      }
    }
  }

  std::cout << "Day 03 Part 1: " << priorityScorePart1 << '\n';
  std::cout << "Day 03 Part 2: " << priorityScorePart2 << '\n';
}