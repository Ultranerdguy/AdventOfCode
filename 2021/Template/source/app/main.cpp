// C++ include files
#include <iostream>

// Project specific files
#include "include.h"

extern int g_test;
int main()
{
  std::cout << "Hello world!\n";
  std::cout << g_test << '\n';
  foo();
}