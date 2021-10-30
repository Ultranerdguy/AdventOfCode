#ifndef _AOC_INCLUDE_H_
#define _AOC_INCLUDE_H_

#include <cstdlib>

using OPCODE = int;
enum Op {ADD = 1, MUL = 2, END = 99};

OPCODE ParseOpcode(OPCODE* pOpcode, size_t len);
bool ParseInstruction(OPCODE* pOpcode, size_t pos);

#endif