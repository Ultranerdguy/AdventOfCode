#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <string>
#include <set>
#include <map>

template <typename QueueType>
bool RecursiveCombat(QueueType& p1, QueueType& p2)
{
  auto initP1 = p1;
  auto initP2 = p2;
  std::set<std::pair<QueueType, QueueType>> rounds;
  while (!p1.empty() && !p2.empty())
  {
    if (rounds.find({ p1,p2 }) != rounds.end())
    {
      return true;
    }
    rounds.insert({ p1,p2 });

    bool p1Wins = false;

    typename QueueType::value_type p1Card = p1.front();
    typename QueueType::value_type p2Card = p2.front();
    p1.erase(p1.begin());
    p2.erase(p2.begin());
    if (p1Card <= p1.size()
      && p2Card <= p2.size())
    {
      auto p1LastItr = p1.begin();
      for (typename QueueType::value_type i = 0; i < p1Card; ++i) ++p1LastItr;
      QueueType p1Cpy(p1.begin(), p1LastItr);
      auto p2LastItr = p2.begin();
      for (typename QueueType::value_type i = 0; i < p2Card; ++i) ++p2LastItr;
      QueueType p2Cpy(p2.begin(), p2LastItr);
      p1Wins = RecursiveCombat(p1Cpy, p2Cpy);
    }
    else 
      p1Wins = p1Card > p2Card;

    if (p1Wins)
    {
      p1.push_back(p1Card);
      p1.push_back(p2Card);
    }
    else
    {
      p2.push_back(p2Card);
      p2.push_back(p1Card);
    }
  }
  return p2.empty();
}

int main()
{
  std::ifstream file("Input.txt");

  std::list<int> p1;
  std::list<int> p2;

  // Skip "Player 1:"
  std::string line;
  std::getline(file, line);
  while (file)
  {
    std::getline(file, line);
    if (line.empty()) break;
    p1.push_back(std::stoi(line));
  }
  // Skip "Player 2:"
  std::getline(file, line);
  while (file)
  {
    std::getline(file, line);
    if (line.empty()) break;
    p2.push_back(std::stoi(line));
  }

  auto p1g1 = p1;
  auto p2g1 = p2;
  
  // Part 1
  while (!p1g1.empty() && !p2g1.empty())
  {
    int p1Card = p1g1.front();
    p1g1.erase(p1g1.begin());
    int p2Card = p2g1.front();
    p2g1.erase(p2g1.begin());
    if (p1Card > p2Card)
    {
      p1g1.push_back(p1Card);
      p1g1.push_back(p2Card);
    }
    else
    {
      p2g1.push_back(p2Card);
      p2g1.push_back(p1Card);
    }
  }

  {
    auto& winner = p1g1.empty() ? p2g1 : p1g1;
    unsigned long long score = 0;
    size_t count = winner.size();
    while (!winner.empty())
    {
      int card = winner.front();
      score += (count * card);
      --count;
      winner.erase(winner.begin());
    }
    std::cout << "Part 1: " << score << '\n';
  }

  // Part 2
  auto p1g2 = p1;
  auto p2g2 = p2;

  {
    auto& winner = RecursiveCombat(p1g2, p2g2) ? p1g2 : p2g2;
    unsigned long long score = 0;
    size_t count = winner.size();
    while (!winner.empty())
    {
      int card = winner.front();
      score += (count * card);
      --count;
      winner.erase(winner.begin());
    }
    std::cout << "Part 2: " << score << '\n';
  }
}