#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_set>
#include <stack>

int main()
{
  constexpr char nop[] = "nop";
  constexpr char acc[] = "acc";
  constexpr char jmp[] = "jmp";
  std::ifstream file("Input.txt");
  
  std::vector<std::pair<char, int>> prog;

  while (file)
  {
    std::string operation;
    int argument;
    file >> operation >> argument;
    prog.push_back(std::make_pair(operation[0], argument));
  }

  // Part 1
  std::unordered_set<int> visited;
  const size_t progSize = prog.size();
  int accumulator = 0;
  size_t i = 0;
  while (i < progSize)
  {
    if (!visited.insert(i).second)
    {
      break;
    }
    switch (prog[i].first)
    {
      case 'n':
      default:
        break;
      case 'a':
        accumulator += prog[i].second;
        break;
      case 'j':
        i += prog[i].second;
        continue;
    }
    ++i;
  }
  std::cout << "Part 1: " << accumulator << '\n';

  // Part 2
  std::stack<std::pair<int, int>> brokenStack;
  std::stack<std::pair<int, int>> modStack;
  std::unordered_set<int> brokenVisited;
  std::unordered_set<int> modVisited;
  accumulator = 0;
  i = 0;
  while (i < progSize)
  {
    char op = prog[i].first;

    if (modStack.empty())
    {
      brokenStack.push(std::make_pair(i, accumulator));
      if (!brokenVisited.insert(i).second)
      {
        brokenStack.pop();
        while (prog[brokenStack.top().first].first == 'a')
        {
          brokenVisited.erase(brokenStack.top().first);
          brokenStack.pop();
        }
        i = brokenStack.top().first;
        accumulator = brokenStack.top().second;
        switch (prog[i].first)
        {
          case 'n':
            op = 'j';
            break;
          case 'j':
            op = 'n';
            break;
        }
        modStack.push(std::make_pair(i,accumulator));
        modVisited.insert(i);
      }
    }
    else
    {
      modStack.push(std::make_pair(i, accumulator));
      if (!modVisited.insert(i).second)
      {
        while (!modStack.empty()) modStack.pop();
        modVisited.clear();
        brokenStack.pop();
        while (prog[brokenStack.top().first].first == 'a')
        {
          brokenVisited.erase(brokenStack.top().first);
          brokenStack.pop();
        }
        i = brokenStack.top().first;
        accumulator = brokenStack.top().second;
        switch (prog[i].first)
        {
        case 'n':
          op = 'j';
          break;
        case 'j':
          op = 'n';
          break;
        }
        modStack.push(std::make_pair(i, accumulator));
        modVisited.insert(i);
      }
    }

    switch (op)
    {
    case 'n':
    default:
      break;
    case 'a':
      accumulator += prog[i].second;
      break;
    case 'j':
      i += prog[i].second;
      continue;
    }
    ++i;
  }
  std::cout << "Part 2: " << accumulator << '\n';
}