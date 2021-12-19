#include "include.h"
#include <iostream>

Node::Base::Base(Node::WeakPtr& pParent)
  : m_pParent(pParent)
{
}

std::pair<bool, bool> Node::Base::DoExplosion(int depth)
{
  return { false, false };
}

void Node::Base::ExplodeLeft(Node::Ptr& value, Node::Ptr const& source) {}
void Node::Base::ExplodeRight(Node::Ptr& value, Node::Ptr const& source) {}
bool Node::Base::AddLeft(Node::Ptr& value) { return false; }
bool Node::Base::AddRight(Node::Ptr& value) { return false; }
bool Node::Base::SplitChild() { return false; }

Node::Pair::Pair(Node::WeakPtr& pParent, Node::Ptr& pLeft, Node::Ptr& pRight)
  : Base(pParent)
  , m_pLeft(pLeft)
  , m_pRight(pRight)
{
}

Node::value_t Node::Pair::Evaluate() const
{
  return 3 * m_pLeft->Evaluate() + 2 * m_pRight->Evaluate();
}

std::pair<bool, bool> Node::Pair::DoExplosion(int depth)
{
  if (depth >= 4 
    && m_pLeft->GetNodeType() == Node::NodeType::Value
    && m_pRight->GetNodeType() == Node::NodeType::Value)
  {
    ExplodeLeft(m_pLeft, m_pLeft);
    ExplodeRight(m_pRight, m_pRight);
    return { true, true };
  }
  else
  {
    std::pair<bool, bool> lRes{ false, false };
    std::pair<bool, bool> rRes{ false, false };
    if ((lRes = m_pLeft->DoExplosion(depth + 1)).first)
    {
      if (lRes.second)
      {
        m_pLeft.swap(Node::Ptr(new Node::Value(weak_from_this(), 0)));
      }
    }
    else if ((rRes = m_pRight->DoExplosion(depth + 1)).first)
    {
      if (rRes.second)
      {
        m_pRight.swap(Node::Ptr(new Node::Value(weak_from_this(), 0)));
      }
    }
    return { lRes.first || rRes.first, false };
  }
}

void Node::Pair::ExplodeLeft(Node::Ptr& value, Node::Ptr const& source)
{
  if (source == m_pLeft)
  {
    auto pParent = m_pParent.lock();
    if (pParent)
    {
      pParent->ExplodeLeft(value, shared_from_this());
    }
  }
  else if (source == m_pRight)
  {
    m_pLeft->AddRight(value);
  }
  else
  {
    AddRight(value);
  }
}

void Node::Pair::ExplodeRight(Node::Ptr& value, Node::Ptr const& source)
{
  if (source == m_pRight)
  {
    auto pParent = m_pParent.lock();
    if (pParent)
    {
      pParent->ExplodeRight(value, shared_from_this());
    }
  }
  else if (source == m_pLeft)
  {
    m_pRight->AddLeft(value);
  }
  else
  {
    AddLeft(value);
  }
}

bool Node::Pair::AddRight(Node::Ptr& value)
{
  return m_pRight->AddRight(value);
}

bool Node::Pair::AddLeft(Node::Ptr& value)
{
  return m_pLeft->AddLeft(value);
}

bool Node::Pair::SplitChild()
{
  Node::value_t val = 0;
  if (m_pLeft->SplitChild() || m_pRight->SplitChild())
  {
    return true;
  }
  if (m_pLeft->GetNodeType() == Node::NodeType::Value && (val = m_pLeft->Evaluate()) >= 10)
  {
    Node::Ptr cL(new Node::Value(weak_from_this(), val / 2));
    Node::Ptr cR(new Node::Value(weak_from_this(), (val+1) / 2));
    m_pLeft.swap(Node::Ptr(new Pair(weak_from_this(), cL, cR)));
    return true;
  }
  if (m_pRight->GetNodeType() == Node::NodeType::Value && (val = m_pRight->Evaluate()) >= 10)
  {
    Node::Ptr cL(new Node::Value(weak_from_this(), val / 2));
    Node::Ptr cR(new Node::Value(weak_from_this(), (val + 1) / 2));
    m_pRight.swap(Node::Ptr(new Pair(weak_from_this(), cL, cR)));
    return true;
  }
  return false;
}

Node::NodeType Node::Pair::GetNodeType() const
{
  return Node::NodeType::Pair;
}

Node::Ptr Node::Pair::Clone() const
{
  auto pl = m_pLeft->Clone();
  auto pr = m_pRight->Clone();
  Ptr p(new Pair(WeakPtr(), pl, pr));
  pl->m_pParent = p;
  pr->m_pParent = p;
  return p;
}

void Node::Pair::Print() const
{
  std::cout << '[';
  m_pLeft->Print();
  std::cout << ',';
  m_pRight->Print();
  std::cout << ']';
}

Node::Value::Value(Node::WeakPtr& pParent, Node::value_t value)
  : Base(pParent)
  , m_value(value)
{
}

Node::value_t Node::Value::Evaluate() const
{
  return m_value;
}

bool Node::Value::AddLeft(Node::Ptr& value)
{
  m_value += value->Evaluate();
  return true;
}

bool Node::Value::AddRight(Node::Ptr& value)
{
  m_value += value->Evaluate();
  return true;
}

Node::NodeType Node::Value::GetNodeType() const
{
  return Node::NodeType::Value;
}

Node::Ptr Node::Value::Clone() const
{
  return Ptr(new Value(WeakPtr(), m_value));
}

void Node::Value::Print() const
{
  std::cout << m_value;
}

Number::Number(Node::Ptr const& pRoot)
  : m_pRootNode(pRoot)
{
}

Number::Number(Number const& cpy)
  : m_pRootNode(cpy.m_pRootNode->Clone())
{

}

Node::Ptr Number::GetNode()
{
  return m_pRootNode;
}

Node::value_t Number::Evaluate() const
{
  return m_pRootNode->Evaluate();
}

void Number::Reduce()
{
  bool doPrint = false;
  do
  {
    if (doPrint) Print();
  } while (m_pRootNode->DoExplosion(0).first || m_pRootNode->SplitChild());
}

void Number::Print() const
{
  m_pRootNode->Print();
  std::cout << '\n';
}

Number operator+(Number& lhs, Number& rhs)
{
  if (!lhs.GetNode()) return rhs;
  if (!rhs.GetNode()) return lhs;
  Node::Ptr root(new Node::Pair(Node::WeakPtr(), lhs.GetNode(), rhs.GetNode()));
  Number out(root);
  lhs.GetNode()->m_pParent = root;
  rhs.GetNode()->m_pParent = root;
  out.Reduce();
  return out;
}

bool operator==(Number& lhs, Number& rhs)
{
  return lhs.GetNode() == rhs.GetNode();
}

Number NumberReader::ReadFromString(std::string str)
{
  m_stream.swap(std::stringstream(str));
  auto p = ReadNode(Node::WeakPtr());
  return Number(p);
}

Node::Ptr NumberReader::ReadNode(Node::WeakPtr pParent)
{
  Node::Ptr out;
  if (m_stream.peek() == '[')
  {
    Node::Pair* p = nullptr;
    out.reset(p = new Node::Pair(pParent, Node::Ptr(nullptr), Node::Ptr(nullptr)));
    m_stream.ignore(1);
    p->m_pLeft.swap(ReadNode(out));
    m_stream.ignore(1);
    p->m_pRight.swap(ReadNode(out));
    m_stream.ignore(1);
  }
  else
  {
    Node::value_t val;
    m_stream >> val;
    out.reset(new Node::Value(pParent, val));
  }
  return out;
}