#include "include.h"

void BinaryFilter::AddLine(std::string const& line)
{
  m_data.push_back(line);
}

char BinaryFilter::GetCommon(std::size_t const n) const
{
  std::size_t oneCount = 0;
  for (auto& line : m_data)
  {
    if (line[n] == '1')
    {
      ++oneCount;
    }
  }
  char c = '0';
  if (oneCount*2 >= GetCount())
  {
    c = '1';
  }
  return c;
}

void BinaryFilter::FilterChar(std::size_t const n, char const c)
{
  for (auto itr = m_data.begin(); itr != m_data.end();)
  {
    if ((*itr)[n] != c)
    {
      itr = m_data.erase(itr);
    }
    else
    {
      ++itr;
    }
  }
}

std::size_t BinaryFilter::GetCount() const
{
  return m_data.size();
}

std::size_t BinaryFilter::GetStringLength() const
{
  std::size_t ret = 0;
  if (!m_data.empty())
  {
    ret = m_data[0].size();
  }
  return ret;
}

unsigned long long BinaryFilter::GetValue() const
{
  unsigned long long ret = 0;
  if (!m_data.empty())
  {
    std::size_t const len = m_data[0].size();
    for (std::size_t i=0; i<len; ++i)
    {
      ret <<= 1;
      ret |= (m_data[0][i] == '1' ? 1 : 0);
    }
  }
  return ret;
}

std::string const& BinaryFilter::Get(std::size_t const i) const
{
  return m_data[i];
}