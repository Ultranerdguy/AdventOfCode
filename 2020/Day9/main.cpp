#include <iostream>
#include <fstream>
#include <unordered_set>
#include <queue>
#include <string>

int main()
{
  std::ifstream file("Input.txt");

  constexpr uint64_t preamble = 25;

  uint64_t invalidValue = -1;

  std::queue<uint64_t> queue;
  std::unordered_multiset<uint64_t> set;
  std::vector<uint64_t> allValues;
  uint64_t value = 0;
  while (file >> value)
  {
    allValues.push_back(value);
    if (queue.size() == preamble)
    {
      bool valid = false;
      for (auto itr = set.begin(); itr != set.end(); ++itr)
      {
        for (auto range = set.equal_range(value - *itr); range.first != range.second; ++range.first)
        {
          if (range.first != itr)
          {
            valid = true;
            break;
          }
        }
      }
      if (!valid)
      {
        invalidValue = value;
      }
      set.erase(queue.front());
      queue.pop();
    }
    queue.push(value);
    set.insert(value);
  }

  // Part 1
  std::cout << "Part 1: " << invalidValue << '\n';

  // Part 2
  auto itrStart = allValues.begin();
  auto itrEnd = ++allValues.begin();
  uint64_t sum = *itrStart;
  while (sum != invalidValue
    && itrStart != allValues.end()
    && itrEnd != allValues.end())
  {
    if (sum < invalidValue)
    {
      sum += *itrEnd;
      ++itrEnd;
    }
    else
    {
      sum -= *itrStart;
      ++itrStart;
    }
  }
  uint64_t min = std::numeric_limits<uint64_t>::max();
  uint64_t max = std::numeric_limits<uint64_t>::min();
  while (itrStart != itrEnd
    && itrStart != allValues.end()
    && itrEnd != allValues.end())
  {
    if (*itrStart < min)
    {
      min = *itrStart;
    }
    if (*itrStart > max)
    {
      max = *itrStart;
    }
    ++itrStart;
  }
  std::cout << "Part 2: " << (min + max) << '\n';
  
}