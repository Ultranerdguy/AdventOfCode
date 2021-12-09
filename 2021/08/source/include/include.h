#ifndef _AOC_INCLUDE_H_
#define _AOC_INCLUDE_H_

#include <string>
#include <vector>
#include <iostream>

class NumberCode
{
public:
  void AddSegment(char s);

  std::string const& GetSegments() const;
  std::string& GetSegments();
protected:
  std::string m_segments;
};

std::istream& operator>>(std::istream& lhs, NumberCode& rhs);

class Display
{
public:
  void Reset();

  void AddInput(NumberCode const& code);
  void AddOutput(NumberCode const& code);

  void MapValues();
  unsigned int GetOutputValue() const;

  std::vector<NumberCode> const& GetInputs() const;
  std::vector<NumberCode> const& GetOutput() const;

protected:
  static std::string Union(std::string const& lhs, std::string const& rhs);

  std::vector<NumberCode> m_inputs;
  std::vector<NumberCode> m_output;
  int m_mapping[10] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
};

std::istream& operator>>(std::istream& lhs, Display& rhs);

#endif