#include "include.h"

OPCODE ParseOpcode(OPCODE* pOpcode, size_t len)
{
  for (size_t i=0; i<len && ParseInstruction(pOpcode, i); i += 4){}
  return pOpcode[0];
}

bool ParseInstruction(OPCODE* pOpcode, size_t pos)
{
  switch (pOpcode[pos])
  {
    case ADD:
      pOpcode[pOpcode[pos+3]] = pOpcode[pOpcode[pos+1]] + pOpcode[pOpcode[pos+2]];
      break;
    case MUL:
      pOpcode[pOpcode[pos+3]] = pOpcode[pOpcode[pos+1]] * pOpcode[pOpcode[pos+2]];
      break;
    default:
    case END:
    return false;
  }
  return true;
}