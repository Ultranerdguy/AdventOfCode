#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <string>
#include <sstream>
#include <set>

struct ruleNode
{
  typedef int RuleIndex;
  std::vector<std::vector<ruleNode*>> subrules;
  char charmatch = 0;

  std::set<size_t> Evaluate(const std::string& line)
  {
    std::set<size_t> validLengths;
    size_t matchingCharacters = 0;
    if (line.empty())
    {
    }
    else if (line[0] == charmatch)
    {
      validLengths.insert(1);
    }
    else
    {
      const size_t subruleCount = subrules.size();
      for (size_t i = 0; i < subruleCount; ++i)
      {
        std::set<size_t> subsubMatchedLengths{ 0 };
        const size_t subsubruleCount = subrules[i].size();
        for (size_t j = 0; j < subsubruleCount; ++j)
        {
          auto cpy = subsubMatchedLengths;
          for (auto s : cpy)
          {
            std::string subLine = line.substr(s);
            auto nextLevel = subrules[i][j]->Evaluate(subLine);
            for (auto n : nextLevel)
            {
              subsubMatchedLengths.insert(n + s);
            }
            subsubMatchedLengths.erase(s);
          }
        }
        validLengths.insert(subsubMatchedLengths.begin(), subsubMatchedLengths.end());
      }
    }
    return validLengths;
  }
};

int main()
{
  std::ifstream file("Input.txt");

  std::map<ruleNode::RuleIndex, ruleNode> rules;
  std::vector<std::string> messages;

  while (file)
  {
    std::string line;
    std::getline(file, line);
    if (line.empty()) break; // Now to read messages

    std::stringstream strm(line);
    ruleNode::RuleIndex index;
    strm >> index;
    strm.ignore(2);

    ruleNode& node = rules[index];

    size_t subRuleIndex = 0; 
    while (strm)
    {
      while (strm && strm.peek() != '|')
      {
        if (strm.peek() == '\"')
        {
          strm.ignore(1);
          strm >> node.charmatch;
          strm.ignore(1);
        }
        else
        {
          node.subrules.resize(subRuleIndex + 1);
          ruleNode::RuleIndex subRule;
          if (strm >> subRule)
          {
            node.subrules[subRuleIndex].push_back(&rules[subRule]);
            strm.ignore(1);
          }
        }
      }
      ++subRuleIndex;
      strm.ignore(1);
    }
  }
  
  while (file)
  {
    std::string line;
    std::getline(file, line);
    if (line.empty()) continue;

    messages.push_back(line);
  }

  // Part 1
  size_t validMessages = 0;
  const size_t messageCount = messages.size();
  for (size_t i = 0; i < messageCount; ++i)
  {
    auto lengths = rules[0].Evaluate(messages[i]);
    if (lengths.find(messages[i].size()) != lengths.end()) ++validMessages;
  }
  std::cout << "Part 1: " << validMessages << '\n';

  // Part 2
  rules[8].subrules = { {&rules[42]},{&rules[42], &rules[8]} };
  rules[11].subrules = { {&rules[42], &rules[31]},{&rules[42], &rules[11], &rules[31]} };
  validMessages = 0;
  for (size_t i = 0; i < messageCount; ++i)
  {
    auto lengths = rules[0].Evaluate(messages[i]);
    if (lengths.find(messages[i].size()) != lengths.end()) ++validMessages;
  }
  std::cout << "Part 2: " << validMessages << '\n';
}