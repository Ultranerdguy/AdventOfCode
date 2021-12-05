// C++ include files
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <algorithm>

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
  
  std::vector<int> drawnNumbers;
  std::string line;
  if (std::getline(input, line))
  {
    std::stringstream lineStream(line);
    int val = 0;
    while (lineStream >> val)
    {
      drawnNumbers.push_back(val);
      lineStream.get();
    }
  }
  std::getline(input, line); // Skip empty line
  std::vector<BingoBoard> boards;
  BingoBoard readBoard;
  while (readBoard.Read(input))
  {
    boards.emplace_back(readBoard);
  }

  // For Part 2, to keep track of the boards
  std::vector<bool> hasWon(boards.size(), false); 
  // Part 1
  int winningScore = -1;
  int losingScore = -1;
  for (int val : drawnNumbers)
  {
    std::size_t const boardCount = boards.size();
    for (std::size_t i=0; i<boardCount; ++i)
    {
      if (!hasWon[i])
      {
        BingoBoard& board = boards[i];
        if (board.MarkNumber(val) && board.CheckVictory())
        {
          hasWon[i] = true;
          if (winningScore < 0)
          {
            winningScore = board.GetScore() * val;
          }
          else if (std::none_of(hasWon.begin(), hasWon.end(), [](bool b){return !b;}))
          {
            losingScore = board.GetScore() * val;
          }
        }
      }
    }
  }
  std::cout << "Day 4 Part 1: " << winningScore << '\n';
  std::cout << "Day 4 Part 2: " << losingScore << '\n';
}