#include <iostream>

#include "TicketManager.h"

void CTicket::AddValue(int value)
{
  m_values.push_back(value);
}

const std::vector<int>& CTicket::GetValues() const
{
  return m_values;
}

CTicketValidator::TRanges& CTicketValidator::GetField(const std::string& name)
{
  return m_fields[name];
}

int CTicketValidator::GetInvalidValues(const CTicket& ticket) const
{
  int invalidSum = -1;
  for (auto i : ticket.GetValues())
  {
    bool valueValid = false;
    for (auto& [key, value] : m_fields)
    {
      valueValid = CheckValueInRanges(i, value);
      if (valueValid)
      {
        break;
      }
    }
    if (!valueValid)
    {
      if (invalidSum == -1)
      {
        ++invalidSum;
      }
      invalidSum += i;
    }
  }
  return invalidSum;
}

bool CTicketValidator::CheckValueInRanges(int i, const TRanges& ranges) const
{
  bool valid = false;
  for (auto& p : ranges)
  {
    if (p.first <= i && i <= p.second)
    {
      valid = true;
      break;
    }
  }
  return valid;
}

void CTicketValidator::InitialiseFieldIndexMap(int fieldCount)
{
  for (auto& [key, v] : m_fields)
  {
    for (int i = 0; i < fieldCount; ++i)
    {
      m_fieldIndexMap[key].insert(i);
    }
  }
}

void CTicketValidator::UpdateFieldIndexMap(const CTicket& ticket)
{
  const size_t valueCount = ticket.GetValues().size();
  for (size_t index = 0; index < valueCount; ++index)
  {
    const int value = ticket.GetValues()[index];
    for (auto itr = m_fields.begin(); itr != m_fields.end(); ++itr)
    {
      auto fimItr = m_fieldIndexMap.find(itr->first);
      if (fimItr != m_fieldIndexMap.end())
      {
        if (fimItr->second.find(index) != fimItr->second.end())
        {
          if (!CheckValueInRanges(value, itr->second))
          {
            m_fieldIndexMap[itr->first].erase(index);
          }
        }
      }
    }
  }
}

void CTicketValidator::ValidateFieldIndexMap()
{
  bool bCanUpdate = true;
  while (bCanUpdate)
  {
    bCanUpdate = false;
    for (auto itr = m_fieldIndexMap.begin(); itr != m_fieldIndexMap.end(); ++itr)
    {
      if (itr->second.size() == 1)
      {
        const int value = *itr->second.begin();
        for (auto nitr = m_fieldIndexMap.begin(); nitr != m_fieldIndexMap.end(); ++nitr)
        {
          if (itr != nitr && (nitr->second.find(value) != nitr->second.end()))
          {
            if (nitr->second.erase(value) != 0)
            {
              bCanUpdate = true;
            }
          }
        }
      }
    }
  }
}

size_t CTicketValidator::DepartureFieldsProduct(const CTicket& ticket) const
{
  size_t prod = 1;
  for (auto& [key, v] : m_fieldIndexMap)
  {
    if (key.substr(0, 9) == "departure" && !v.empty())
    {
      const int index = *v.begin();
      prod *= ticket.GetValues()[index];
    }
  }
  return prod;
}
