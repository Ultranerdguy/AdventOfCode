#include "include.h"
#include <string>

std::istream& operator>>(std::istream& in, Instruction& instruction)
{
  std::string word;
  return (in >> word >> instruction.quantity >> word >> instruction.source >> word >> instruction.destination);
}
