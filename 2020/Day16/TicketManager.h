#ifndef _TICKETMANAGER_H_
#define _TICKETMANAGER_H_

#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>


class CTicket
{
protected:
  std::vector<int> m_values;
public:
  void AddValue(int value);
  const std::vector<int>& GetValues() const;
};

class CTicketValidator
{
public:
  typedef std::vector<std::pair<int, int>> TRanges;
  typedef std::unordered_map<std::string, TRanges> TFields;

  TRanges& GetField(const std::string& name);

  int GetInvalidValues(const CTicket& ticket) const;

  bool CheckValueInRanges(int i, const TRanges& ranges) const;

  void InitialiseFieldIndexMap(int fieldCount);
  void UpdateFieldIndexMap(const CTicket& ticket);
  void ValidateFieldIndexMap();

  size_t DepartureFieldsProduct(const CTicket& ticket) const;

  TFields m_fields;
  std::unordered_map<std::string, std::unordered_set<int>> m_fieldIndexMap;
};

#endif