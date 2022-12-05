// C++ include files
#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <string>

// Project specific files
#include "include.h"
#include "config.h"

void Move(std::stack<char>& source, std::stack<char>& dest, int quantity)
{
  for (int i = 0; i < quantity; ++i)
  {
    dest.push(source.top());
    source.pop();
  }
}

void MoveMultiple(std::stack<char>& source, std::stack<char>& dest, int quantity)
{
  std::stack<char> temp;
  Move(source, temp, quantity);
  Move(temp, dest, quantity);
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
  
  std::vector<std::stack<char>> stacks;
  std::vector<Instruction> instructions;

  std::vector<std::string> stackDiagram;
  std::string line;
  while (std::getline(input, line) && !line.empty())
  {
    stackDiagram.emplace_back(line);
  }
  std::size_t columnCount = (stackDiagram.back().size()+2)/3;
  stacks.resize(columnCount-1);
  stackDiagram.pop_back();
  for (auto lineItr = stackDiagram.rbegin(); lineItr != stackDiagram.rend(); ++lineItr)
  {
    std::string& line = *lineItr;
    for (std::size_t i = 0; i < columnCount && (i*4<line.size()); ++i)
    {
      char c = line[4*i + 1];
      if (isalpha(std::char_traits<char>::to_int_type(c)))
        stacks[i].push(c);
    }
  }

  Instruction instruction;
  while (input >> instruction)
  {
    instructions.push_back(instruction);
  }

  // Copy the original data for part 2
  auto stacks2 = stacks;

  // Run instructions
  for (auto& i : instructions)
  {
    Move(stacks[i.source-1], stacks[i.destination-1], i.quantity);
    MoveMultiple(stacks2[i.source-1], stacks2[i.destination-1], i.quantity);
  }

  // Read output
  std::cout << "Day 05 Part 1: ";
  for (auto& s : stacks) if (!s.empty()) std::cout << s.top();
  std::cout << '\n';

  std::cout << "Dat 05 Part 2: ";
  for (auto& s : stacks2) if (!s.empty()) std::cout << s.top();
  std::cout << '\n';
}