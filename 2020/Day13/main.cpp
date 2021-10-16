#include <iostream>
#include <fstream>
#include <numeric>
#include <vector>
#include <execution>

int64_t mulInv(int64_t a, int64_t m)
{
  int64_t m0 = m;
  int64_t s1 = 1;
  int64_t s2 = 0;
  int64_t t1 = 0;
  int64_t t2 = 1;

  while (m != 0)
  {
    int64_t q = a / m;
    int64_t tmp = a;
    a = m;
    m = tmp - q * m;
    tmp = s1;
    s1 = s2;
    s2 = tmp - q * s2;
    tmp = t1;
    t1 = t2;
    t2 = tmp - q * t2;
  }
  while (s1 < 0)
    s1 += m0;
  return s1 % m0;
}

int64_t chineseRemainder(const std::vector<int64_t>& n, const std::vector<int64_t>& a)
{
  int64_t prod = std::accumulate(n.begin(), n.end(), (int64_t)1, std::multiplies<int64_t>());

  int64_t sm = 0;
  for (size_t i = 0; i < n.size(); ++i)
  {
    int64_t p = prod / n[i];
    sm += a[i] * mulInv(p, n[i]) * p;
  }

  return sm % prod;
}

int main()
{
  std::ifstream file("Input.txt");

  int64_t now;
  file >> now;
  std::vector<int64_t> IDs;

  while (file)
  {
    if ('x' == file.peek())
    {
      file.ignore(2);
      IDs.push_back(0);
    }
    else
    {
      int64_t busID = 0;
      file >> busID;
      if (busID != 0)
        IDs.push_back(busID);
      file.ignore(1);
    }
  }

  // Part 1
  int64_t earliestID = 0;
  int64_t earliest = std::numeric_limits<int64_t>::max();
  for (auto i : IDs)
  {
    if (i != 0)
    {
      int64_t delay = i - now % i;
      delay = delay==i ? i : delay; // If the time until the next bus 
                                    // is exactly one round trip
                                    // then the delay is actually 0
      if (now + delay < earliest)
      {
        earliest = now + delay;
        earliestID = i;
      }
    }
  }
  std::cout << "Part 1: " << (earliestID * (earliest-now)) << '\n';

  // Part 2
  std::vector<int64_t> n;
  std::vector<int64_t> a;
  const int64_t busCount = IDs.size(); 
  for (int64_t i = 0; i < busCount; ++i)
  {
    if (IDs[i] != 0)
    {
      n.push_back(IDs[i]);
      a.push_back((IDs[i] - i) % IDs[i]);
    }
  }
  std::cout << "Part 2: " << chineseRemainder(n, a) << '\n';
}