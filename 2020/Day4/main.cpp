#include <iostream>
#include <fstream>
#include <vector>

#include "Passport.h"

int main()
{
  std::ifstream file("Input.txt");
  
  std::vector<Passport> passports;
  do
  {
    Passport pass;
    file >> pass;
    passports.push_back(pass);
  } while (file);

  // Part 1
  size_t validCounter = 0;
  for (auto& passport : passports)
  {
    passport.Print();
    if (passport.HasRequiredFields())
    {
      ++validCounter;
    }
  }
  std::cout << "Part 1: " << validCounter << '\n';

  // Part 2
  validCounter = 0;
  for (auto& passport : passports)
  {
    if (passport.IsValid())
    {
      ++validCounter;
    }
  }
  std::cout << "Part 2: " << validCounter << '\n';
}