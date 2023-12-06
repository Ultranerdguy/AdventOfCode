// C++ include files
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>

// Project specific files
#include "include.h"
#include "config.h"

using value_t = long long;

struct TimeDistancePair
{
  value_t time = 0;
  value_t dist = 0;
};

value_t GetTotalWinningPlays(TimeDistancePair const& race)
{
  value_t const b = race.time;
  value_t const c = -race.dist;
  value_t const tLowest = static_cast<value_t>(std::floor(b - std::sqrt(b*b + 4*c))/2)+1;
  return race.time - 2*tLowest + 1;
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

  std::string word;
  std::vector<TimeDistancePair> races;

  value_t value = 0;
  input >> word;
  while (input >> value) races.push_back({value, 0});
  input.clear();
  input >> word;
  for (std::size_t i=0; i<races.size(); ++i)
  {
    input >> value;
    races[i].dist = value;
  }

  // Part 1
  value_t prod = 1;
  for (auto& race : races)
  {
    prod *= GetTotalWinningPlays(race);
  }

  std::cout << "Day 6 Part 1: " << prod << '\n';

  // Part 2
  TimeDistancePair theBigRace;
  std::stringstream timeStream;
  std::stringstream distStream;
  for (auto& race : races)
  {
    timeStream << race.time;
    distStream << race.dist;
  }
  timeStream >> theBigRace.time;
  distStream >> theBigRace.dist;

  std::cout << "Day 6 Part 2: " << GetTotalWinningPlays(theBigRace) << '\n';

  return 0;
}