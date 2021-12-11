// C++ include files
#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <vector>
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
  
  unsigned long long score = 0;
  std::vector<unsigned long long> autocompleteScores;
  char const open_brackets[]  = {'(','[','{','<'};
  char const close_brackets[] = {')',']','}','>'};
  std::string line;
  while (std::getline(input, line))
  {
    bool corrupt = false;
    std::stack<char> bracketStack;
    for (char c : line)
    {
      if (std::find(open_brackets, open_brackets+4, c) != open_brackets+4)
      {
        bracketStack.push(c);
      }
      else
      {
        auto index = std::find(close_brackets, close_brackets+4, c) - close_brackets;
        if (index < 4 && bracketStack.top() == open_brackets[index])
        {
          bracketStack.pop();
        }
        else
        {
          corrupt = true;
          switch (c)
          {
            case ')': score += 3; break;
            case ']': score += 57; break;
            case '}': score += 1197; break;
            case '>': score += 25137; break;
          }
          break;
        }
      }
    }
    if (!corrupt && !bracketStack.empty()) // not corrupt, but incomplete
    {
      unsigned long long acScore = 0;
      while (!bracketStack.empty())
      {
        acScore *= 5;
        auto top = bracketStack.top();
        bracketStack.pop();
        switch (top)
        {
          case '(': acScore += 1; break;
          case '[': acScore += 2; break;
          case '{': acScore += 3; break;
          case '<': acScore += 4; break;
        }
      }
      autocompleteScores.push_back(acScore);
    }
  }
  std::cout << "Day 10 Part 1: " << score << '\n';
  std::sort(begin(autocompleteScores), end(autocompleteScores));
  std::cout << "Day 10 Part 2: " << autocompleteScores[autocompleteScores.size()/2] << '\n';
}