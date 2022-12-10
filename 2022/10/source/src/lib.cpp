#include "include.h"
#include <sstream>

void Processor::RunLine(std::string_view line)
{
  auto p = line.find_first_of(" ",0);
  auto op = line.substr(0,p);
  auto arg = line.substr(p+1);

  if (op == "addx")
  {
    std::stringstream strm{std::string(arg)};
    int dx{};
    strm >> dx;
    AddX(dx);
  }
  else if (op == "noop")
  {
    Noop();
  }
}

void Processor::AddX(int dx)
{
  MidCycleCallback(currentCycle, registers);
  ++currentCycle;
  EndCycleCallback(currentCycle, registers);

  MidCycleCallback(currentCycle, registers);
  ++currentCycle;
  registers.X += dx;
  EndCycleCallback(currentCycle, registers);
}

void Processor::Noop()
{
  MidCycleCallback(currentCycle, registers);
  ++currentCycle;
  EndCycleCallback(currentCycle, registers);
}