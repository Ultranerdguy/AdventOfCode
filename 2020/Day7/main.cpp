#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <queue>

struct Bag
{
  std::string name;
  std::vector<Bag*> parents;
  std::vector<std::pair<size_t, Bag*>> contents;
};

size_t CountBags(Bag* pBag)
{
  size_t total = 0;
  if (pBag)
  {
    for (auto [count, pChild] : pBag->contents)
    {
      if (count != 0)
      {
        total += count * (CountBags(pChild)+1);
      }
    }
  }
  return total;
}

int main()
{
  const std::string myBag = "shiny gold";
  std::ifstream file("Input.txt");

  std::unordered_map<std::string, Bag> bagGraph;

  while (file)
  {
    std::string line;
    std::getline(file, line);

    if (!line.empty())
    {
      std::string bagName = line.substr(0,line.find("bag")-1);
      std::string contents = line.substr(line.find("contain") + 8);

      bagGraph[bagName].name = bagName;
      Bag bag;
      std::stringstream contentStream(contents);
      while (contentStream)
      {
        size_t count=0;
        std::string name1;
        std::string name2;
        contentStream >> count >> name1 >> name2;
        std::string bagChildName = name1 + " " + name2;

        if (count != 0)
        {
          bagGraph[bagName].contents.push_back(std::make_pair(count, &bagGraph[bagChildName]));
          bagGraph[bagChildName].parents.push_back(&bagGraph[bagName]);
        }
        contentStream.ignore(std::numeric_limits<std::streamsize>::max(), ',');
        contentStream.get();
      }
    }
  }

  // Part 1
  std::unordered_set<std::string> viableParents;
  std::queue<Bag*> toCheck;
  toCheck.push(&bagGraph[myBag]);
  while (!toCheck.empty())
  {
    Bag* pCurrentBag = toCheck.front();
    if (pCurrentBag)
    {
      toCheck.pop();
      for (Bag* p : pCurrentBag->parents)
      {
        if (p)
        {
          toCheck.push(p);
          viableParents.insert(p->name);
        }
      }
    }
  }
  std::cout << "Part 1: " << viableParents.size() << '\n';

  // Part 2
  size_t bagCount = 0;
  Bag* pMyBag = &bagGraph[myBag];
  if (pMyBag)
  {
    bagCount = CountBags(pMyBag);
  }
  std::cout << "Part 2: " << bagCount << '\n';
}