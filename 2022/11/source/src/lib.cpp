#include "include.h"
#include <string>

worry_t Operation::Apply(worry_t in) const
{
  auto mod = useOld ? in : modifier;
  switch (mode)
  {
    case Mode::MUL:
      in *= mod;
      break;
    case Mode::ADD:
      in += mod;
      break;
  }
  return in;
}

void Operation::Parse(std::istream& in)
{
  std::string word;
  while (in >> word && word != "old");
  char c;
  in >> c;
  switch (c)
  {
    case '*': mode = Mode::MUL; break;
    case '+': mode = Mode::ADD; break;
  }
  auto p = in.tellg();
  in >> word;
  if (word == "old")
  {
    useOld = true;
  }
  else
  {
    in.seekg(p);
    in >> modifier;
  }
}

int Test::GetNextMonkey(worry_t in) const
{
  if (in % modTest == 0)
  {
    return trueMonkeyIndex;
  }
  return falseMonkeyIndex;
}

worry_t Test::GetMod() const
{
  return modTest;
}

void Test::Parse(std::istream& in)
{
  std::string word;
  while (in >> word && word != "by");
  in >> modTest;
  while (in >> word && word != "monkey");
  in >> trueMonkeyIndex;
  while (in >> word && word != "monkey");
  in >> falseMonkeyIndex;
}

void Monkey::SetEnvironment(Environment& env)
{
  pEnvironment = &env;
}

void Monkey::AddItem(worry_t item)
{
  items.push_back(item);
}

void Monkey::ReduceItems(worry_t mod)
{
  for (auto& i : items)
  {
    i %= mod;
  }
}

void Monkey::InspectAll(bool tooWorried)
{
  for (worry_t i : items)
  {
    i = op.Apply(i);
    if (!tooWorried) { i /= 3; }
    pEnvironment->GetMonkey(test.GetNextMonkey(i)).AddItem(i);
  }
  inspections += items.size();
  items.clear();
}

std::size_t Monkey::GetTotalInspections() const
{
  return inspections;
}

Test const& Monkey::GetTest() const
{
  return test;
}

void Monkey::Parse(std::istream& in)
{
  std::string word;
  while (in >> word && word != "items:");
  worry_t w;
  while (in >> w)
  {
    items.push_back(w);
    in.get(); // Skip next character
  }
  in.clear();
  op.Parse(in);
  test.Parse(in);
}

Environment::Environment(Environment const& cpy)
{
  monkeys = cpy.monkeys;
  for (auto& i : monkeys) i.SetEnvironment(*this);
}

std::size_t Environment::GetMonkeyCount() const
{
  return monkeys.size();
}

Monkey& Environment::GetMonkey(int index)
{
  return monkeys[index];
}

void Environment::UpdateItemWorry()
{
  worry_t prod = 1;
  for (auto& m : monkeys)
  {
    prod *= m.GetTest().GetMod();
  }
  for (auto& m : monkeys)
  {
    m.ReduceItems(prod);
  }
}

void Environment::Parse(std::istream& in)
{
  std::string word;
  while (in >> word)
  {
    if (word == "Monkey")
    {
      monkeys.push_back(Monkey{});
      Monkey& last = monkeys.back();
      last.SetEnvironment(*this);
      last.Parse(in);
    }
  }
}