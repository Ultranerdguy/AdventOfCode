#include <iostream>
#include <fstream>
#include <vector>
#include <string>

class CTrees
{
  static constexpr char Tree = '#';
  std::vector<std::string> treeRows;
public:
  CTrees(std::string filename)
  {
    std::ifstream file(filename);

    std::string treeLine;
    while (std::getline(file, treeLine))
    {
      if (!treeLine.empty())
      {
        treeRows.push_back(treeLine);
      }
    }
  }

  size_t GetCollisions(int rowStep, int colStep)
  {
    size_t treeCount = 0;
    int row = 0;
    int col = 0;

    for (int row = 0, col = 0; row < treeRows.size(); row += rowStep, col += colStep)
    {
      if (treeRows[row][col % treeRows[row].size()] == Tree)
      {
        ++treeCount;
      }
    }
    return treeCount;
  }
};

int main()
{
  CTrees trees("Input.txt");

  // Part 1
  std::cout << "Part 1: " << trees.GetCollisions(1,3) << '\n';

  // Part 2
  const std::initializer_list<std::pair<int, int>> slopes{ {1,1},{3,1},{5,1},{7,1},{1,2} };
  size_t product = 1;
  for (auto& [colStep, rowStep] : slopes)
  {
    product *= trees.GetCollisions(rowStep, colStep);
  }
  std::cout << "Part 2: " << product << '\n';
}