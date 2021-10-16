#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>

int main()
{
  std::ifstream file("Input.txt");
  std::vector<bool> seats;
  seats.resize(2<<10, false);

  int maxID = 0;
  std::string line;
  while (std::getline(file, line))
  {
    int ID = 0;
    int row = 0;
    int col = 0;
    for (char c : line)
    {
      ID <<= 1;
      ID |= (c == 'B') || (c=='R');
    }
    seats[ID] = true;
    maxID = std::max(maxID, ID);
  }

  // Part 1
  std::cout << "Part 1: " << maxID << '\n';

  // Part 2
  for (int i = 0; i <= 2<<10; ++i)
  {
    if (!seats[i] && seats[i+1] && seats[i-1])
    {
      std::cout << "Part 2: " << i << '\n';
      break;
    }
  }
}