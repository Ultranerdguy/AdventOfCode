#ifndef _AOC_INCLUDE_H_
#define _AOC_INCLUDE_H_

#include <bitset>
#include <memory>
#include <vector>
#include <sstream>

namespace Packet
{
  using version_t = std::bitset<3>;
  using typeID_t = std::bitset<3>;
  class Base
  {
  public:
    virtual unsigned long long CountVersions() const;
    virtual unsigned long long GetSize() const;
    virtual unsigned long long Evaluate() const = 0;

    version_t m_version;
    typeID_t m_typeID;
  };

  using Ptr = std::unique_ptr<Base>;

  class Constant : public Base
  {
  public:
    virtual unsigned long long GetSize() const override;
    virtual unsigned long long Evaluate() const override;

    std::vector<std::bitset<4>> m_constantGroups;
  };

  class Group : public Base
  {
  public:
    virtual unsigned long long CountVersions() const override;
    virtual unsigned long long GetSize() const override;
    virtual unsigned long long Evaluate() const override;

    std::vector<Ptr> m_subPackets;
  };

  class GroupSize : public Group
  {
  public:
    virtual unsigned long long GetSize() const override;
  };

  class GroupCount : public Group
  {
  public:
    virtual unsigned long long GetSize() const override;
  };
}

class PacketReader
{
public:
  PacketReader(std::string const& packet);

  void EvaluatePacket();

  unsigned long long CountVersions();
  unsigned long long Evaluate();

  Packet::Ptr ReadPacket();
  Packet::Ptr ReadConstant(Packet::version_t version, Packet::typeID_t type);
  Packet::Ptr ReadGroup(Packet::version_t version, Packet::typeID_t type);
  Packet::Ptr ReadGroupSize(Packet::version_t version, Packet::typeID_t type);
  Packet::Ptr ReadGroupCount(Packet::version_t version, Packet::typeID_t type);

protected:
  std::istringstream m_stream;
  Packet::Ptr m_evaluatedPacket;
};

#endif