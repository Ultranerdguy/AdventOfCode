// C++ include files
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

// Project specific files
#include "include.h"
#include "config.h"

class SignalProcessor : public Processor
{
public:
  virtual void EndCycleCallback(cycle_count_t cycle, Registers const& reg) override;

  int strength{};
};

class ScreenProcessor : public Processor
{
public:
  virtual void MidCycleCallback(cycle_count_t cycle, Registers const& reg) override;

  std::stringstream screenOut;
};

void SignalProcessor::EndCycleCallback(cycle_count_t cycle, Registers const& reg)
{
  // Could subtract 20, but unsigned types might roll under and act weird
  if (((cycle + 20)%40) == 0 && cycle <= 220)
  {
    strength += (cycle * reg.X);
  }
}

void ScreenProcessor::MidCycleCallback(cycle_count_t cycle, Registers const& reg)
{
  auto pos = (cycle-1) % 40;
  bool lit = std::abs(pos - reg.X) < 2;
  screenOut << (lit ? '#' : ' ');
  if ((cycle%40) == 0) screenOut << '\n';
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
  
  SignalProcessor proc;
  ScreenProcessor screen;
  std::string line;
  while (std::getline(input, line))
  {
    proc.RunLine(line);
    screen.RunLine(line);
  }
  std::cout << "Day 10 Part 1: " << proc.strength << '\n';

  std::cout << "Day 10 Part 2: " << '\n' << screen.screenOut.str() << '\n';
}