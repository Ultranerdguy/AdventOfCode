#ifndef _AOC_INCLUDE_H_
#define _AOC_INCLUDE_H_

#include <istream>
#include <vector>

class BingoBoard
{
public:
  bool Read(std::istream& src);

  void AddNumber(int n);
  void SetWidth(int n);
  void Reset();

  bool MarkNumber(int n);
  bool CheckVictory() const;
  int GetScore() const;
protected:
  int m_width = -1;
  std::vector<int> m_board;
  std::vector<bool> m_marked;
};

#endif