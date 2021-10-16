#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

int64_t ProcessLinePart1(std::string line)
{
  int64_t result = 0;
  // First, process brackets
  size_t openBracket = line.find('(', 0);
  while (openBracket != std::string::npos)
  {
    int brackets = 1;
    size_t closeBracket = openBracket;
    // Need to find the corresponding closing bracket
    while (brackets > 0 && ++closeBracket < line.size())
    {
      if (line[closeBracket] == ')') --brackets;
      else if (line[closeBracket] == '(') ++brackets;
    }
    line.replace(openBracket, closeBracket - openBracket + 1, std::to_string(ProcessLinePart1(line.substr(openBracket + 1, closeBracket - openBracket - 1))));

    openBracket = line.find('(', 0);
  }

  // Brackets processed, now for math
  std::stringstream strm(line);

  char op = '+';
  while (strm)
  {
    int64_t value;
    strm >> value;
    switch (op)
    {
      case '+':
        result += value;
        break;
      case '*':
        result *= value;
        break;
    }
    strm >> op;
  }
  return result;
}

int64_t ProcessLinePart2(std::string line)
{
  int64_t result = 0;
  // First, process brackets
  size_t openBracket = line.find('(', 0);
  while (openBracket != std::string::npos)
  {
    int brackets = 1;
    size_t closeBracket = openBracket;
    // Need to find the corresponding closing bracket
    while (brackets > 0 && ++closeBracket < line.size())
    {
      if (line[closeBracket] == ')') --brackets;
      else if (line[closeBracket] == '(') ++brackets;
    }
    line.replace(openBracket, closeBracket - openBracket + 1, std::to_string(ProcessLinePart2(line.substr(openBracket + 1, closeBracket - openBracket - 1))));

    openBracket = line.find('(', 0);
  }

  // Brackets processed, now for math
  // Process addition
  size_t plusPosition = std::string::npos;
  while ((plusPosition = line.find('+')) != std::string::npos)
  {
    size_t start = line.find_last_of("+*", plusPosition - 1);
    start = start == std::string::npos ? 0 : start+1;
    size_t end = line.find_first_of("+*", plusPosition + 1);

    std::stringstream strm(line.substr(start, end - start));
    int64_t value1;
    strm >> value1;
    strm.ignore(10,'+');
    int64_t value2;
    strm >> value2;
    line.replace(start, end - start - 1, std::to_string(value1 + value2));
  }

  // Now multiply
  std::stringstream strm(line);
  strm >> result;
  strm.ignore(10, '*');
  while (strm)
  {
    int64_t value;
    strm >> value;
    result *= value;
    strm.ignore(10, '*');
  }
  return result;
}

int main()
{
  std::ifstream file("Input.txt");

  int64_t sumP1 = 0;
  int64_t sumP2 = 0;
  while (file)
  {
    std::string line;
    std::getline(file, line);
    if (line.empty()) break;

    sumP1 += ProcessLinePart1(line);
    sumP2 += ProcessLinePart2(line);
  }

  std::cout << "Part 1: " << sumP1 << '\n';
  std::cout << "Part 2: " << sumP2 << '\n';
}