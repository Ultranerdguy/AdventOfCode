#ifndef _AOC_INCLUDE_H_
#define _AOC_INCLUDE_H_

#include <memory>
#include <string>
#include <sstream>

namespace Node
{
  class Base;
  using WeakPtr = std::weak_ptr<Base>;
  using Ptr = std::shared_ptr<Base>;
  using value_t = unsigned long long int;

  enum class NodeType{Base, Pair, Value};

  class Base : public std::enable_shared_from_this<Base>
  {
  public:
    Base(WeakPtr& pParent);

    virtual value_t Evaluate() const = 0;
    virtual NodeType GetNodeType() const = 0;
    virtual Ptr Clone() const = 0;

    virtual std::pair<bool, bool> DoExplosion(int depth); // recursive down
    virtual void ExplodeLeft(Ptr& value, Ptr const& source); // recursive up
    virtual void ExplodeRight(Ptr& value, Ptr const& source); // recursive up
    virtual bool AddRight(Ptr& value); // recursive down
    virtual bool AddLeft(Ptr& value); // recursive down
    virtual bool SplitChild(); // recursive down

    virtual void Print() const = 0;
    std::weak_ptr<Base> m_pParent;
  };

  class Pair : public Base
  {
  public:
    Pair(WeakPtr& pParent, Ptr& pLeft, Ptr& pRight);

    virtual value_t Evaluate() const override;
    virtual std::pair<bool, bool> DoExplosion(int depth) override;
    virtual void ExplodeLeft(Ptr& value, Ptr const& source) override;
    virtual void ExplodeRight(Ptr& value, Ptr const& source) override;
    virtual bool AddRight(Ptr& value) override;
    virtual bool AddLeft(Ptr& value) override;
    virtual bool SplitChild() override;
    virtual NodeType GetNodeType() const override;
    virtual Ptr Clone() const override;

    virtual void Print() const override;
    
    std::shared_ptr<Base> m_pLeft;
    std::shared_ptr<Base> m_pRight;
  };

  class Value : public Base
  {
  public:
    Value(WeakPtr& pParent, value_t value);

    virtual value_t Evaluate() const override;
    virtual bool AddRight(Ptr& value) override;
    virtual bool AddLeft(Ptr& value) override;
    virtual NodeType GetNodeType() const override;
    virtual Ptr Clone() const override;

    virtual void Print() const override;
  protected:
    value_t m_value;
  };
}

class Number
{
public:
  Number(Node::Ptr const& pRoot = nullptr);
  Number(Number const& cpy);
 
  void Reduce();
  Node::Ptr GetNode();
  Node::value_t Evaluate() const;
  void Print() const;
protected:
  Node::Ptr m_pRootNode;
};

Number operator+(Number& lhs, Number& rhs);
bool operator==(Number& lhs, Number& rhs);

class NumberReader
{
public:
  Number ReadFromString(std::string str);
private:
  Node::Ptr ReadNode(Node::WeakPtr pParent);
  std::stringstream m_stream;
};
#endif