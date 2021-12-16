#include "include.h"

unsigned long long Packet::Base::CountVersions() const
{
  return m_version.to_ullong();
}

unsigned long long Packet::Base::GetSize() const
{
  return 6;
}

unsigned long long Packet::Constant::GetSize() const
{
  return Base::GetSize() + 5*m_constantGroups.size();
}

unsigned long long Packet::Constant::Evaluate() const
{
  unsigned long long out = 0;
  for (auto& v : m_constantGroups)
  {
    out *= 16;
    out += v.to_ullong();
  }
  return out;
}

unsigned long long Packet::Group::CountVersions() const
{
  unsigned long long count = Base::CountVersions();
  for (Ptr const& p : m_subPackets)
  {
    count += p->CountVersions();
  }
  return count;
}

unsigned long long Packet::Group::GetSize() const
{
  unsigned long long size = Base::GetSize() + 1;
  for (Ptr const& p : m_subPackets)
  {
    size += p->GetSize();
  }
  return size;
}

unsigned long long Packet::Group::Evaluate() const
{
  unsigned long long out = 0;

  switch (m_typeID.to_ullong())
  {
    case 0:
      for (Ptr const& p : m_subPackets)
      {
        out += p->Evaluate();
      }
      break;
    case 1:
      out = 1;
      for (Ptr const& p : m_subPackets)
      {
        out *= p->Evaluate();
      }
      break;
    case 2:
      out = std::numeric_limits<unsigned long long>::max();
      for (Ptr const& p : m_subPackets)
      {
        auto pVal = p->Evaluate();
        out = pVal < out ? pVal : out;
      }
      break;
    case 3:
      for (Ptr const& p : m_subPackets)
      {
        auto pVal = p->Evaluate();
        out = pVal > out ? pVal : out;
      }
      break;
    case 5:
      out = m_subPackets[0]->Evaluate() > m_subPackets[1]->Evaluate() ? 1 : 0;
      break;
    case 6:
      out = m_subPackets[0]->Evaluate() < m_subPackets[1]->Evaluate() ? 1 : 0;
      break;
    case 7:
      out = m_subPackets[0]->Evaluate() == m_subPackets[1]->Evaluate() ? 1 : 0;
      break;
  }

  return out;
}

unsigned long long Packet::GroupSize::GetSize() const
{
  return Group::GetSize() + 15;
}

unsigned long long Packet::GroupCount::GetSize() const
{
  return Group::GetSize() + 11;
}

PacketReader::PacketReader(std::string const& packet)
  : m_stream(packet)
{
}

void PacketReader::EvaluatePacket()
{
  m_evaluatedPacket = ReadPacket();
}

unsigned long long PacketReader::CountVersions()
{
  return m_evaluatedPacket->CountVersions();
}

unsigned long long PacketReader::Evaluate()
{
  return m_evaluatedPacket->Evaluate();
}

Packet::Ptr PacketReader::ReadPacket()
{
  Packet::version_t version;
  Packet::typeID_t type;
  if (m_stream >> version >> type)
  {
    switch (type.to_ullong())
    {
      case 4:
        return ReadConstant(version, type);
      default:
        return ReadGroup(version, type);
    }
  }
  return nullptr;
}

Packet::Ptr PacketReader::ReadConstant(Packet::version_t version, Packet::typeID_t type)
{
  auto p = new Packet::Constant;
  Packet::Ptr packet(p);
  p->m_version = version;
  p->m_typeID = type;
  char c;
  do
  {
    std::bitset<4> value;
    m_stream >> c >> value;
    p->m_constantGroups.push_back(value);
  } while (c == '1');
  return packet;
}

Packet::Ptr PacketReader::ReadGroup(Packet::version_t version, Packet::typeID_t type)
{
  char l;
  if (m_stream >> l)
  {
    switch (l)
    {
      default:
      case '0':
        return ReadGroupSize(version, type);
      case '1':
        return ReadGroupCount(version, type);
    }
  }
  return nullptr;
}

Packet::Ptr PacketReader::ReadGroupSize(Packet::version_t version, Packet::typeID_t type)
{
  auto p = new Packet::GroupSize;
  Packet::Ptr packet(p);
  p->m_version = version;
  p->m_typeID = type;
  auto v = version.to_ullong();
  auto t = type.to_ullong();

  std::bitset<15> size;
  m_stream >> size;
  Packet::Ptr sp;
  while (p->GetSize()-22 < size.to_ullong() && (sp = ReadPacket()))
  {
    p->m_subPackets.emplace_back(std::move(sp));
  }
  return packet;
}

Packet::Ptr PacketReader::ReadGroupCount(Packet::version_t version, Packet::typeID_t type)
{
  auto p = new Packet::GroupCount;
  Packet::Ptr packet(p);
  p->m_version = version;
  p->m_typeID = type;

  std::bitset<11> count;
  m_stream >> count;
  Packet::Ptr sp;
  while (p->m_subPackets.size() < count.to_ullong() && (sp = ReadPacket()))
  {
    p->m_subPackets.emplace_back(std::move(sp));
  }
  return packet;
}