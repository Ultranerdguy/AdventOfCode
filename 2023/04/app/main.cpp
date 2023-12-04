// C++ include files
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <set>
#include <sstream>
#include <numeric>

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

  unsigned int score1 = 0;
  std::vector<unsigned int> cardCounts;

  std::string line;
  while (std::getline(input, line) && !line.empty())
  {
    std::stringstream lineStream(line);
    std::string word;
    unsigned int cardID = 0;
    char symbol = '\0';
    lineStream >> word >> cardID >> symbol;
    if (cardCounts.size() < cardID) cardCounts.resize(cardID, 1);

    std::set<unsigned int> winningNumbers;
    unsigned int value = 0;
    while (lineStream >> value)
    {
      winningNumbers.insert(value);
    }
    lineStream.clear();

    lineStream >> symbol; // Skip the '|'

    int winningCount = 0;
    while (lineStream >> value)
    {
      if (winningNumbers.contains(value)) ++winningCount;
    }

    // Part 1 counting
    if (winningCount > 0) score1 += (1<<(winningCount-1));

    // Part 2 card incrementing
    if (cardCounts.size() < (cardID+winningCount)) cardCounts.resize(cardID+winningCount, 1);
    for (int i=0; i<winningCount; ++i)
    {
      cardCounts[cardID + i] += cardCounts[cardID - 1];
    }
  }

  std::cout << "Day 4 Part 1: " << score1 << '\n';

  std::cout << "Day 4 Part 2: " << std::accumulate(cardCounts.begin(), cardCounts.end(), 0) << '\n';

  return 0;
}