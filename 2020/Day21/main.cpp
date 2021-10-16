#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <set>
#include <map>
#include <sstream>

struct Food
{
  std::set<std::string> m_ingredients;
  std::set<std::string> m_allergens;
};

int main()
{
  std::ifstream file("Input.txt");

  std::map<std::string, std::set<std::string>> allergenMap;
  
  std::vector<Food> foods;
  while (file)
  {
    std::string line;
    std::getline(file, line);
    if (line.empty()) break;

    Food food;
    std::stringstream strm(line);
    while (strm)
    {
      std::string ingredient;
      strm >> ingredient;
      if (ingredient.empty() || ingredient[0] == '(') break;

      food.m_ingredients.insert(ingredient);
    }

    while (strm)
    {
      std::string allergen;
      strm >> allergen;
      if (allergen.empty()) break;

      // Trim trailing , or )
      allergen = allergen.substr(0, allergen.size() - 1);
      food.m_allergens.insert(allergen);

      // Early processing

      // Figure out what ingredients contain this allergen
      auto itr = allergenMap.find(allergen);
      if (itr == allergenMap.end())
      {
        // Haven't found this before, add all ingredients
        itr = allergenMap.insert(std::make_pair(allergen, std::set<std::string>())).first;
        for (auto& i : food.m_ingredients)
        {
          itr->second.insert(i);
        }
      }
      else
      {
        // Found this before, remove ingredients that aren't duped
        for (auto i = itr->second.begin(); i != itr->second.end();)
        {
          if (food.m_ingredients.find(*i) == food.m_ingredients.end())
          {
            i = itr->second.erase(i);
          }
          else
            ++i;
        }
      }
    }
    foods.emplace_back(food);
  }

  // Reduce
  std::set<std::string> unsafeIngredientSet;
  bool canReduce = true;
  while (canReduce)
  {
    canReduce = false;
    for (auto& [a, si] : allergenMap)
    {
      if (si.size() == 1)
      {
        auto& i = *si.begin();
        unsafeIngredientSet.insert(i);

        for (auto& [oa, osi] : allergenMap)
        {
          if (a == oa) continue;
          if (osi.erase(i))
            canReduce = true;
        }
      }
    }
  }

  size_t countSafeFood = 0;
  for (auto& f : foods)
  {
    for (auto& i : f.m_ingredients)
    {
      if (unsafeIngredientSet.find(i) == unsafeIngredientSet.end()) ++countSafeFood;
    }
  }

  std::cout << "Part 1: " << countSafeFood << '\n';

  std::cout << "Part 2: ";
  std::vector<std::string> unsafe;
  for (auto& [a, i] : allergenMap)
  {
    unsafe.push_back(*i.begin());
  }
  const size_t ingredientCount = unsafe.size();
  if (ingredientCount != 0)
  {
    std::cout << unsafe[0];
    for (size_t i = 1; i < ingredientCount; ++i)
    {
      std::cout << ',' << unsafe[i];
    }
  }
}