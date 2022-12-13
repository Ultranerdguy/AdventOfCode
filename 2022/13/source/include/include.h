#ifndef _AOC_INCLUDE_H_
#define _AOC_INCLUDE_H_

#include <vector>
#include <sstream>

class List
{
public:
  List() = default;
  List(std::string const& l);
  void Parse(std::stringstream& line);

  friend int Compare(List const&, List const&);
private:
  std::vector<List> children;
  int value = -1;
};

int Compare(List const& lhs, List const& rhs);

#endif