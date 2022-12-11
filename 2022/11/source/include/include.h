#ifndef _AOC_INCLUDE_H_
#define _AOC_INCLUDE_H_

#include <vector>
#include <iostream>

using worry_t = unsigned long long;

class Environment;

class Operation
{
public:
  enum class Mode { MUL, ADD };

  worry_t Apply(worry_t in) const;

  void Parse(std::istream& in);

protected:
  Mode mode{Mode::ADD};
  worry_t modifier{};
  bool useOld{false};
};

class Test
{
public:
  int GetNextMonkey(worry_t in) const;
  worry_t GetMod() const;

  void Parse(std::istream& in);

private:
  worry_t modTest{1};
  int trueMonkeyIndex{};
  int falseMonkeyIndex{};
};

class Monkey
{
public:
  void SetEnvironment(Environment& env);
  void AddItem(worry_t item);
  void ReduceItems(worry_t mod);

  void InspectAll(bool tooWorried = false);
  std::size_t GetTotalInspections() const;
  Test const& GetTest() const;

  void Parse(std::istream& in);

private:
  Environment* pEnvironment{nullptr};
  std::size_t inspections{};
  std::vector<worry_t> items;
  Operation op;
  Test test;
};

class Environment
{
public:
  Environment() = default;
  Environment(Environment const& cpy);
  std::size_t GetMonkeyCount() const;
  Monkey& GetMonkey(int index);
  void UpdateItemWorry();

  void Parse(std::istream& in);

private:
  std::vector<Monkey> monkeys;
};

#endif