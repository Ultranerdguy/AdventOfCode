// C++ include files
#include <iostream>
#include <fstream>
#include <algorithm>
#include <numeric>

// Project specific files
#include "include.h"
#include "config.h"

int main(int argc, char* argv[])
{
  if (argc < 2)
  {
    std::cout << "Usage: \n";
    std::cout << "  " << EXECUTABLE << " <input file>\n";
    return 1;
  }
  std::ifstream input(argv[1]);

  int initialP1;
  int initialP2;
  input.ignore(std::numeric_limits<std::streamsize>::max(), ':');
  input >> initialP1;
  input.ignore(std::numeric_limits<std::streamsize>::max(), ':');
  input >> initialP2;
  {
    // hard-coded position sequences
    constexpr int position1Sequence[] = { 6,0,2,2,0 };
    constexpr int position2Sequence[] = { 5,8,9,8,5,0,3,4,3,0 };

    // calculate the score sequences
    int score1Sequence[5];
    int score1Sum = 0;
    for (int i = 0; i < 5; ++i)
    {
      int pos = (initialP1 + position1Sequence[i]) % 10;
      score1Sequence[i] = pos == 0 ? 10 : pos;
      score1Sum += score1Sequence[i];
    }
    int score2Sequence[10];
    int score2Sum = 0;
    for (int i = 0; i < 10; ++i)
    {
      int pos = (initialP2 + position2Sequence[i]) % 10;
      score2Sequence[i] = pos == 0 ? 10 : pos;
      score2Sum += score2Sequence[i];
    }

    // calculate turn count to win
    int turn1Count = 1000 / score1Sum;
    int turn2Count = 1000 / score2Sum;
    int score1 = turn1Count * score1Sum;
    int score2 = turn2Count * score2Sum;
    turn1Count *= 5;
    turn2Count *= 10;
    int i = 0;
    while (score1 < 1000)
    {
      score1 += score1Sequence[i];
      ++turn1Count;
      ++i %= 5;
    }
    i = 0;
    while (score2 < 1000)
    {
      score2 += score2Sequence[i];
      ++turn2Count;
      ++i %= 10;
    }

    // calculate the losers score
    // If they're equal, player 1 wins by going first
    unsigned long long losingScore = 0;
    unsigned long long rollCount = 0;
    if (turn1Count <= turn2Count)
    {
      turn2Count = turn1Count - 1;
      losingScore = turn2Count / 10 * score2Sum;
      turn2Count %= 10;
      while (turn2Count != 0)
      {
        losingScore += score2Sequence[--turn2Count];
      }
      turn2Count = turn1Count - 1;
    }
    else
    {
      turn1Count = turn2Count;
      losingScore = turn1Count * score1Sum / 5;
      turn1Count %= 5;
      while (turn1Count != 0)
      {
        losingScore += score1Sequence[--turn1Count];
      }
      turn1Count = turn2Count;
    }
    rollCount = 3 * (turn1Count + turn2Count);
    std::cout << "Day 21 Part 1: " << (rollCount * losingScore) << '\n';
  }
  // Part 2
  {
    constexpr unsigned long long rollWeights[][2] = { {3,1},{4,3},{5,6},{6,7},{7,6},{8,3},{9,1} };
    unsigned long long player1Table[10][21]{};
    unsigned long long player2Table[10][21]{};
    player1Table[initialP1][0] = 1;
    player2Table[initialP2][0] = 1;
    unsigned long long player1Wins = 0;
    unsigned long long player2Wins = 0;
    auto not_zero = [](auto i) {return i != 0; };
    while (std::any_of((unsigned long long*)player1Table, (unsigned long long*)player1Table + 210, not_zero)
      || std::any_of((unsigned long long*)player2Table, (unsigned long long*)player2Table + 210, not_zero))
    {
      unsigned long long player2UniverseCount = std::accumulate((unsigned long long*)player2Table, (unsigned long long*)player2Table + 210, 0ULL);
      unsigned long long player1SwapTable[10][21]{};
      for (int position = 0; position < 10; ++position)
      {
        for (int score = 0; score < 21; ++score)
        {
          if (player1Table[position][score] != 0)
          {
            for (auto roll : rollWeights)
            {
              auto const& delta = roll[0];
              auto const& weight = roll[1];

              auto newPos = (position + delta) % 10;
              auto newScore = score + (newPos == 0 ? 10 : newPos);
              auto universeCount = weight * player1Table[position][score];
              if (newScore >= 21)
              {
                player1Wins += universeCount * player2UniverseCount;
              }
              else
              {
                player1SwapTable[newPos][newScore] += universeCount;
              }
            }
          }
        }
      }
      std::swap(player1Table, player1SwapTable);

      unsigned long long player1UniverseCount = std::accumulate((unsigned long long*)player1Table, ((unsigned long long*)player1Table) + 210, 0ULL);
      unsigned long long player2SwapTable[10][21]{};
      for (int position = 0; position < 10; ++position)
      {
        for (int score = 0; score < 21; ++score)
        {
          if (player2Table[position][score] != 0)
          {
            for (auto roll : rollWeights)
            {
              auto const& delta = roll[0];
              auto const& weight = roll[1];

              auto newPos = (position + delta) % 10;
              auto newScore = score + (newPos == 0 ? 10 : newPos);
              auto universeCount = weight * player2Table[position][score];
              if (newScore >= 21)
              {
                player2Wins += universeCount * player1UniverseCount;
              }
              else
              {
                player2SwapTable[newPos][newScore] += universeCount;
              }
            }
          }
        }
      }
      std::swap(player2Table, player2SwapTable);
    }
    std::cout << "Day 21 Part 2: " << std::max(player1Wins, player2Wins) << '\n';
  }
  return 0;
}