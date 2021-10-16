#ifndef _PASSPORT_H_
#define _PASSPORT_H_

#include <unordered_map>

class Passport
{
  static const std::string BirthYearField;
  static const std::string IssueYearField;
  static const std::string ExpirationYearField;
  static const std::string HeightField;
  static const std::string HairColourField;
  static const std::string EyeColourField;
  static const std::string PassportIDField;
public:
  void AddField(const std::string& key, const std::string& value);
  bool HasRequiredFields();
  bool IsValid();
  void Print();

protected:
  bool ValidBYR();
  bool ValidIYR();
  bool ValidEYR();
  bool ValidHGT();
  bool ValidHCL();
  bool ValidECL();
  bool ValidPID();

  std::unordered_map<std::string, std::string> m_fields;
};

std::istream& operator>>(std::istream& stream, Passport& passport);

#endif