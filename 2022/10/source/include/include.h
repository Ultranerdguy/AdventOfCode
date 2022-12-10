#ifndef _AOC_INCLUDE_H_
#define _AOC_INCLUDE_H_

#include <string_view>

class Processor
{
public:
  using cycle_count_t = int;
  struct Registers
  {
    int X{1};
  };

  void RunLine(std::string_view line);

  virtual void EndCycleCallback(cycle_count_t cycle, Registers const& reg) {};
  virtual void MidCycleCallback(cycle_count_t cycle, Registers const& reg) {};

protected:
  void AddX(int dx);
  void Noop();

  Registers registers;
  cycle_count_t currentCycle{1};
};

#endif