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
   NumberReader reader;
  {
    std::ifstream input(argv[1]);
    Number sum;
    std::string line;
    while (std::getline(input, line))
    {
      auto N = reader.ReadFromString(line);
      sum = sum + N;
    }
    std::cout << "Day 18 Part 1: " << sum.Evaluate() << '\n';
  }
  {
    std::ifstream input(argv[1]);
    std::vector<Number> numbers;
    std::string line;
    while (std::getline(input, line))
    {
      auto N = reader.ReadFromString(line);
      numbers.push_back(N);
    }

    Node::value_t maxSum = 0;
    for (auto& n1 : numbers)
    {
      for (auto& n2 : numbers)
      {
        if (!(n1 == n2))
        {
          auto sum = (Number(n1) + Number(n2)).Evaluate();
          if (sum > maxSum) maxSum = sum;
        }
      }
    }
    std::cout << "Day 18 Part 2: " << maxSum << '\n';
  }
  return 0;
}