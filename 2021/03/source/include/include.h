#ifndef _AOC_INCLUDE_H_
#define _AOC_INCLUDE_H_

#include <vector>
#include <string>

class BinaryFilter
{
public:
  void AddLine(std::string const& line);
  char GetCommon(std::size_t const n) const;
  void FilterChar(std::size_t const n, char const c);
  std::size_t GetCount() const;
  std::size_t GetStringLength() const;
  unsigned long long GetValue() const;
  std::string const& Get(std::size_t const i) const;

protected:
  std::vector<std::string> m_data;
};

#endif