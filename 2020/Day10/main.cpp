#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

int main()
{
  std::ifstream file("Input.txt");

  std::vector<int64_t> values;
  int64_t value;
  while (file >> value)
  {
    values.push_back(value);
  }
  std::sort(values.begin(), values.end());

  // Part 1
  int64_t distribution[3]{ 0,0,1 };
  value = 0;
  for (auto v : values)
  {
    ++distribution[v - value - 1];
    value = v;
  }
  std::cout << "Part 1: " << (distribution[0] * distribution[2]) << '\n';

  // Part 2
  values.insert(values.begin(), 0);
  const size_t valueCount = values.size();
  std::vector<int64_t> routes(valueCount,0);
  routes[0] = 1;
  for (size_t i = 0; i < valueCount; ++i)
  {
    for (size_t j = 1; j <= 3; ++j)
    {
      if (i >= j && values[i] - 3 <= values[i - j])
      {
        routes[i] += routes[i - j];
      }
    }
  }

  std::cout << "Part 2: " << routes[valueCount-1] << '\n';
}