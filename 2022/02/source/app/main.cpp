// C++ include files
#include <iostream>
#include <fstream>
#include <vector>

// Project specific files
#include "include.h"
#include "config.h"

namespace RPS
{
  enum class Throw { None, Rock, Paper, Scissors };
  enum class WinState { None, Win, Draw, Loss };

  struct Game { Throw player1{Throw::None}; Throw player2{Throw::None}; };

  Throw LetterToThrow(char c)
  {
    switch (c)
    {
      case 'A':
      case 'X':
        return Throw::Rock;
      case 'B':
      case 'Y':
        return Throw::Paper;
      case 'C':
      case 'Z':
        return Throw::Scissors;
      default:
        return Throw::None;
    }
  }

  WinState LetterToWinState(char c)
  {
    switch (c)
    {
      case 'X':
        return WinState::Loss;
      case 'Y':
        return WinState::Draw;
      case 'Z':
        return WinState::Win;
      default:
        return WinState::None;
    }
  }
  
  // Return the Throw needed to obtain outcome against player2
  Throw SolveForThrow(WinState outcome, Throw player2)
  {
    switch (outcome)
    {
      case WinState::Win:
      {
        switch (player2)
        {
          case Throw::Rock:
            return Throw::Paper;
          case Throw::Paper:
            return Throw::Scissors;
          case Throw::Scissors:
            return Throw::Rock;
          default:
            return Throw::None;

        }
      }
      case WinState::Draw:
        return player2;
      case WinState::Loss:
      {
        switch (player2)
        {
          case Throw::Rock:
            return Throw::Scissors;
          case Throw::Paper:
            return Throw::Rock;
          case Throw::Scissors:
            return Throw::Paper;
          default:
            return Throw::None;

        }
      }
      default:
        return Throw::None;
    }
  }

  // Return the win state from the perspective of player 1
  WinState GetWinState(Game const& game)
  {
    WinState state{WinState::Loss};
    if (game.player1 == Throw::Rock && game.player2 == Throw::Scissors
      || game.player1 == Throw::Paper && game.player2 == Throw::Rock
      || game.player1 == Throw::Scissors && game.player2 == Throw::Paper) // Win
    {
      state = WinState::Win;
    }
    else if (game.player1 == game.player2) // Draw
    {
      state = WinState::Draw;
    }
    return state;
  }

  int CalculatePlayer1Score(Game const& game)
  {
    int score = 0;
    // Calculate the score for the hand thrown (we could cast each to an int, but I'm not a fan of that approach)
    switch (game.player1)
    {
      case Throw::Rock:
        score += 1;
        break;
      case Throw::Paper:
        score += 2;
        break;
      case Throw::Scissors:
        score += 3;
        break;
    }

    // Check if it was a win, draw or loss
    switch (GetWinState(game))
    {
      case WinState::Win:
        score += 6;
        break;
      case WinState::Draw:
        score += 3;
        break;
      case WinState::Loss:
      default:
        break;
    }
    return score;
  }

  int CalculatePlayer2Score(Game const& game)
  {
    return CalculatePlayer1Score(Game{game.player2, game.player1});
  }
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

  // Parse the input data
  int totalScorePart1{};
  int totalScorePart2{};
  while (input)
  {
    char player1{}, col2{};
    input >> player1 >> col2;
    if (player1 && col2)
    {
      // Part 1
      auto player1Throw = RPS::LetterToThrow(player1);
      auto player2Throw = RPS::LetterToThrow(col2);
      RPS::Game thisGame{player1Throw, player2Throw};
      totalScorePart1 += RPS::CalculatePlayer2Score(thisGame);

      // Part 2
      auto outcome = RPS::LetterToWinState(col2);
      thisGame.player2 = RPS::SolveForThrow(outcome, player1Throw);
      totalScorePart2 += RPS::CalculatePlayer2Score(thisGame);
    }
  } 
  std::cout << "Day 02 Part 1: " << totalScorePart1 << '\n';
  std::cout << "Day 02 Part 2: " << totalScorePart2 << '\n';
}