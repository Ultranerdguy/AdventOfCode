// C++ include files
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

// Project specific files
#include "include.h"
#include "config.h"

struct Hand
{
  static int CardScore1(char c)
  {
    switch (c)
    {
      case 'A': return 12;
      case 'K': return 11;
      case 'Q': return 10;
      case 'J': return 9;
      case 'T': return 8;
      default: return c-'2';
    }
  }
  static int CardScore2(char c)
  {
    switch (c)
    {
      case 'A': return 12;
      case 'K': return 11;
      case 'Q': return 10;
      case 'T': return 9;
      default: return c-'1';
      case 'J': return 0; // now the worst card
    }
  }

  std::string cards;
  int handScore = 0;
  int bid = 0;

  void CalculateScore1()
  {
    int counts[13]{};
    for (auto c : cards) ++counts[CardScore1(c)];
    int reduced[2]{};
    int ri = 0;
    for (int i : counts) 
    {
      if (i > 1)
      {
        reduced[ri] = i;
        ++ri;
      }
    }
    // Scoring
    // 6 - 5 of a kind
    // 5 - 4 of a kind
    // 4 - Full house
    // 3 - 3 of a kind
    // 2 - Two pair
    // 1 - One pair
    // 0 - High card
    if (ri == 0) handScore = 0;
    else if (ri == 1)
    {
      switch (reduced[0])
      {
        case 5: handScore = 6; break;
        case 4: handScore = 5; break;
        case 3: handScore = 3; break;
        case 2: handScore = 1; break;
        default: break;
      }
    }
    else if (reduced[0] == reduced[1]) handScore = 2;
    else handScore = 4;
  }
  
  void CalculateScore2()
  {
    int counts[13]{};
    for (auto c : cards) ++counts[CardScore2(c)];
    int reduced[2]{};
    int ri = 0;
    for (int j = 1; j < 13; ++j) 
    {
      auto i = counts[j];
      if (i > 1)
      {
        reduced[ri] = i;
        ++ri;
      }
    }
    // Scoring
    // 6 - 5 of a kind
    // 5 - 4 of a kind
    // 4 - Full house
    // 3 - 3 of a kind
    // 2 - Two pair
    // 1 - One pair
    // 0 - High card
    switch (counts[0])
    {
      case 5: [[fallthrough]];
      case 4: handScore = 6; break;
      case 3: handScore = (ri>0) ? 6 : 5; break;
      case 2: handScore = (ri>0) ? (reduced[0] == 3) ? 6 : 5 : 3; break;
      case 1: handScore = (ri>0) ? (reduced[0] == 4) ? 6 : (reduced[0] == 3) ? 5 : (ri>1) ? 4 : 3 : 1; break;
      default:
        if (ri == 0) handScore = 0;
        else if (ri == 1)
        {
          switch (reduced[0])
          {
            case 5: handScore = 6; break;
            case 4: handScore = 5; break;
            case 3: handScore = 3; break;
            case 2: handScore = 1; break;
            default: break;
          }
        }
        else if (reduced[0] == reduced[1]) handScore = 2;
        else handScore = 4;

    }
  }
};

template <int CardFunction(char)>
bool Compare(Hand const& lhs, Hand const& rhs)
{
  if (lhs.handScore != rhs.handScore) return lhs.handScore < rhs.handScore;
  for (int i=0; i<5; ++i)
  {
    auto const lScore = CardFunction(lhs.cards[i]);
    auto const rScore = CardFunction(rhs.cards[i]);
    if (lScore != rScore) return lScore < rScore;
  }
  return false;
}

std::istream& operator>>(std::istream& input, Hand& hand)
{
  input >> hand.cards;
  input >> hand.bid;
  return input;
}

int main(int argc, char* argv[])
{
  if (argc < 2)
  {
    std::cout << "Usage: \n";
    std::cout << "  " << EXECUTABLE << " <input file>\n";
    return 1;
  }
  std::ifstream input(argv[1]);

  std::vector<Hand> hands;
  Hand hand;
  while (input >> hand)
  {
    hands.emplace_back(std::move(hand));
  }

  for (auto& hand : hands) hand.CalculateScore1();
  std::sort(hands.begin(), hands.end(), Compare<Hand::CardScore1>);

  unsigned long long score1 = 0;
  for (unsigned long long i = 0; i < hands.size(); ++i)
  {
    score1 += (i+1) * hands[i].bid;
  }
  std::cout << "Day 7 Part 1: " << score1 << '\n';

  for (auto& hand : hands) hand.CalculateScore2();
  std::sort(hands.begin(), hands.end(), Compare<Hand::CardScore2>);

  unsigned long long score2 = 0;
  for (unsigned long long i = 0; i < hands.size(); ++i)
  {
    score2 += (i+1) * hands[i].bid;
  }
  std::cout << "Day 7 Part 2: " << score2 << '\n';
  return 0;
}