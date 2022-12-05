#ifndef _AOC_INCLUDE_H_
#define _AOC_INCLUDE_H_

#include <iostream>

struct Instruction
{
  int source;
  int destination;
  int quantity;
};

std::istream& operator>>(std::istream&, Instruction&);

#endif