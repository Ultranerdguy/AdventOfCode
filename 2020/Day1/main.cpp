#include <iostream>
#include <fstream>
#include <unordered_set>

int main()
{
  constexpr int sumTarget = 2020;

  std::unordered_multiset<int> values;
  
  std::ifstream expenseReport("ExpenseReport");

  {
    // Read all the values in
    int value = 0;
    while (expenseReport >> value)
    {
      values.insert(value);
    }
  }

  // Solve part 1
  for (int value : values)
  {
    // Check if the other value needed to sum to 2020 was found yet
    const int sumPair = sumTarget - value;
    if (values.find(sumPair) != values.end())
    {
      // The other value was found, report back
      std::cout << "Part 1: " << value << " * " << sumPair << " = " << (sumPair * value) << '\n';
      break; // Found, don't need to find more
    }
  }

  // Solve part 2
  for (auto itrFirst = values.begin(); itrFirst != values.end(); ++itrFirst)
  {
    bool found = false;
    auto itrSecond = itrFirst;
    ++itrSecond;
    for (; itrSecond != values.end(); ++itrSecond)
    {
      // Check if the other value needed to sum to 2020 was found yet
      const int sumPair = sumTarget - *itrFirst - *itrSecond;
      if (values.find(sumPair) != values.end())
      {
        // The other value was found, report back
        std::cout << "Part 2: " << *itrFirst << " * " << *itrSecond << " * " << sumPair << " = " << (sumPair * *itrFirst * *itrSecond) << '\n';
        found = true;
        break; // Found, don't need to find more
      }
    }
    if (found)
    {
      break;
    }
  }

  return 0;
}