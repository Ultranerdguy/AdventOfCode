#include <string>
#include <sstream>

#include "include.h"

void BingoBoard::AddNumber(int n)
{
  m_board.push_back(n);
  m_marked.push_back(false);
}

void BingoBoard::SetWidth(int n)
{
  m_width = n;
}

void BingoBoard::Reset()
{
  m_width = -1;
  m_board.clear();
  m_marked.clear();
}

bool BingoBoard::MarkNumber(int n)
{
  bool ret = false;
  std::size_t const size = m_board.size();
  for (std::size_t i=0; i<size; ++i)
  {
    if (m_board[i] == n && !m_marked[i])
    {
      m_marked[i] = true;
      ret = true;
    }
  }
  return ret;
}

bool BingoBoard::CheckVictory() const
{
  bool ret = false;
  std::size_t const size = m_board.size();
  std::size_t const rows = size / m_width;

  for (std::size_t i=0; i<rows; ++i)
  {
    bool rowWin = true;
    for (std::size_t j=0; j<m_width; ++j)
    {
      if (!m_marked[j + i*m_width])
      {
        rowWin = false;
        break;
      }
    }
    if (rowWin)
    {
      ret = true;
      break;
    }
  }

  for (std::size_t i=0; i<m_width; ++i)
  {
    bool colWin = true;
    for (std::size_t j=0; j<rows; ++j)
    {
      if (!m_marked[i + j*m_width])
      {
        colWin = false;
        break;
      }
    }
    if (colWin)
    {
      ret = true;
      break;
    }
  }
  return ret;
}

int BingoBoard::GetScore() const
{
  int ret = 0;
  std::size_t const size = m_board.size();
  for (std::size_t i=0; i<size; ++i)
  {
    if (!m_marked[i])
    {
      ret += m_board[i];
    }
  }
  return ret;
}

bool BingoBoard::Read(std::istream& src)
{
  bool good = false;
  std::string line;
  Reset();
  while (std::getline(src, line) && !line.empty())
  {
    good = true;
    std::stringstream lineStream(line);
    int val = 0;
    int width = 0;
    while (!(lineStream >> val).fail())
    {
      ++width;
      AddNumber(val);
    }
    SetWidth(width);
  }
  return good;
}