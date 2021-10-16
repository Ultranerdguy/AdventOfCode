#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

struct passwordLines
{
  int firstValue;
  int secondValue;
  char letter;
  std::string password;
};

int main()
{
  // Open the passwords file
  std::ifstream passwordsFile("Passwords.txt");
  // Store passwords
  std::vector<passwordLines> allPasswordLines;

  // Read a line from the file
  std::string line;
  while (std::getline(passwordsFile, line))
  {
    // Convert line to a stream for easy reading
    std::stringstream stream;
    stream << line;

    // Setup variables for this line
    passwordLines passwordLine;

    // Read the variables from the line
    stream >> passwordLine.firstValue;
    stream.ignore(std::numeric_limits<std::streamsize>::max(), '-'); // Skip the -
    stream >> passwordLine.secondValue;
    stream >> passwordLine.letter;
    stream.ignore(std::numeric_limits<std::streamsize>::max(), ':'); // Skip the :
    stream >> passwordLine.password;

    allPasswordLines.push_back(passwordLine);
  }

  // Part 1
  size_t validPasswordCountPart1 = 0;
  for (passwordLines& p : allPasswordLines)
  {
    auto letterCount = std::count(p.password.begin(), p.password.end(), p.letter);
    if (p.firstValue <= letterCount && letterCount <= p.secondValue)
    {
      ++validPasswordCountPart1;
    }
  }

  std::cout << "Part1 - Valid passwords: " << validPasswordCountPart1 << std::endl;

  // Part 2
  size_t validPasswordCountPart2 = 0;
  for (passwordLines& p : allPasswordLines)
  {
    if ((p.password[p.firstValue-1] == p.letter) ^ (p.password[p.secondValue-1] == p.letter))
    {
      ++validPasswordCountPart2;
    }
  }

  std::cout << "Part2 - Valid passwords: " << validPasswordCountPart2 << std::endl;

  return 0;
}