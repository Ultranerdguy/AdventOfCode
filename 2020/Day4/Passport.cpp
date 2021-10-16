#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <unordered_set>
#include "Passport.h"

const std::string Passport::BirthYearField("byr");
const std::string Passport::IssueYearField("iyr");
const std::string Passport::ExpirationYearField("eyr");
const std::string Passport::HeightField("hgt");
const std::string Passport::HairColourField("hcl");
const std::string Passport::EyeColourField("ecl");
const std::string Passport::PassportIDField("pid");

void Passport::AddField(const std::string& key, const std::string& value)
{
  m_fields[key] = value;
}

bool Passport::HasRequiredFields()
{
  constexpr size_t requiredFieldCount = 7;
  static const std::string requiredFields[] = {
    BirthYearField,
    IssueYearField,
    ExpirationYearField,
    HeightField,
    HairColourField,
    EyeColourField,
    PassportIDField };
  for (size_t i = 0; i < requiredFieldCount; ++i)
  {
    if (m_fields.find(requiredFields[i]) == m_fields.end())
    {
      return false;
    }
  }
  return true;
}

bool Passport::IsValid()
{
  return HasRequiredFields() && ValidBYR() && ValidECL() && ValidEYR() && ValidHCL()
    && ValidHGT() && ValidIYR() && ValidPID();
}

void Passport::Print()
{
  std::cout << m_fields.size() << "\t";
  for (auto& [k, v] : m_fields)
  {
    std::cout << std::setw(3) << k << " " << std::setw(10) << v << '\t';
  }
  std::cout << '\n';
}

bool Passport::ValidBYR()
{
  bool bValid = false;
  auto itr = m_fields.find(BirthYearField);
  if (itr != m_fields.end())
  {
    int year = atoi(itr->second.c_str());
    bValid = (1920 <= year && year <= 2002);
  }
  return bValid;
}

bool Passport::ValidIYR()
{
  bool bValid = false;
  auto itr = m_fields.find(IssueYearField);
  if (itr != m_fields.end())
  {
    int year = atoi(itr->second.c_str());
    bValid = (2010 <= year && year <= 2020);
  }
  return bValid;
}

bool Passport::ValidEYR()
{
  bool bValid = false;
  auto itr = m_fields.find(ExpirationYearField);
  if (itr != m_fields.end())
  {
    int year = atoi(itr->second.c_str());
    bValid = (2020 <= year && year <= 2030);
  }
  return bValid;
}

bool Passport::ValidHGT()
{
  bool bValid = false;
  auto itr = m_fields.find(HeightField);
  if (itr != m_fields.end())
  {
    std::string units = itr->second.substr(itr->second.size() - 2);
    int size = atoi(itr->second.substr(0, itr->second.size() - 2).c_str());
    if (units == "cm")
    {
      bValid = (150 <= size && size <= 193);
    }
    else if (units == "in")
    {
      bValid = (59 <= size && size <= 76);
    }
  }
  return bValid;
}

bool Passport::ValidHCL()
{
  bool bValid = false;
  auto itr = m_fields.find(HairColourField);
  if (itr != m_fields.end())
  {
    if (itr->second[0] == '#' && itr->second.size() == 7)
    {
      bValid = true; // Assume valid, fail if a digit isn't hex
      for (size_t i = 1; i < 7; ++i)
      {
        if (!std::isxdigit(itr->second[i]))
        {
          bValid = false;
          break;
        }
      }
    }
  }
  return bValid;
}

bool Passport::ValidECL()
{
  static const std::unordered_set<std::string> validEyeColours{ "amb", "blu", "brn", "gry", "grn", "hzl", "oth" };
  bool bValid = false;
  auto itr = m_fields.find(EyeColourField);
  if (itr != m_fields.end())
  {
    bValid = validEyeColours.find(itr->second) != validEyeColours.end();
  }
  return bValid;
}

bool Passport::ValidPID()
{
  bool bValid = false;
  auto itr = m_fields.find(PassportIDField);
  if (itr != m_fields.end())
  {
    bValid = itr->second.size() == 9;
    if (bValid)
    {
      for (char& c : itr->second)
      {
        if (!std::isdigit(c))
        {
          bValid = false;
          break;
        }
      }
    }
  }
  return bValid;
}

std::istream& operator>>(std::istream& stream, Passport& passport)
{
  constexpr char delimiter = ':';
  std::string line;
  while (std::getline(stream, line) && !line.empty())
  {
    std::stringstream sstream;
    sstream << line;

    std::string kvPair;
    while (sstream >> kvPair)
    {
      const size_t delimitPos = kvPair.find(delimiter);
      const std::string key = kvPair.substr(0, delimitPos);
      const std::string value = kvPair.substr(delimitPos + 1);

      passport.AddField(key, value);
    }
  }
  return stream;
}