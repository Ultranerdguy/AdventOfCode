#include <iostream>
#include <fstream>
#include <unordered_map>

int main()
{
  std::ifstream file("Input.txt");

  std::unordered_map<uint64_t, int> lastSpoken;
  int position = 1;
  uint64_t lastDigit;
  while (file)
  {
    file >> lastDigit;
    lastSpoken[lastDigit] = position++;
    file.ignore(1);
  }
  std::unordered_map<uint64_t, int> previousSpoken;
  
  // Part 1
  while (position <= 2020)
  {
    // What digit to say next
    uint64_t nextDigit = 0;
    if (previousSpoken.find(lastDigit) != previousSpoken.end())
    {
      nextDigit = lastSpoken[lastDigit] - previousSpoken[lastDigit];
    }

    // Say Digit

    // Update arrays
    if (lastSpoken.find(nextDigit) != lastSpoken.end())
    {
      previousSpoken[nextDigit] = lastSpoken[nextDigit];
    }
    lastSpoken[nextDigit] = position;
    ++position;
    lastDigit = nextDigit;
  }
  std::cout << "Part 1: " << lastDigit << '\n';

  // Part 2
  while (position <= 30000000)
  {
    // What digit to say next
    uint64_t nextDigit = 0;
    if (previousSpoken.find(lastDigit) != previousSpoken.end())
    {
      nextDigit = lastSpoken[lastDigit] - previousSpoken[lastDigit];
    }

    // Say Digit

    // Update arrays
    if (lastSpoken.find(nextDigit) != lastSpoken.end())
    {
      previousSpoken[nextDigit] = lastSpoken[nextDigit];
    }
    lastSpoken[nextDigit] = position;
    ++position;
    lastDigit = nextDigit;
  }
  std::cout << "Part 2: " << lastDigit << '\n';
}