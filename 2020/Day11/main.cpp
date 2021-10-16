#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class SeatSim
{
protected:
  static constexpr char FLOOR = '.';
  static constexpr char CHAIR = 'L';
  static constexpr char PERSON = '#';
  typedef std::vector<std::vector<char>> TLayout;
  TLayout seatLayout;

public:
  template <typename Iterator>
  void SetSeatLayout(Iterator begin, Iterator end)
  {
    seatLayout.clear();
    size_t row = 0;
    while (begin != end)
    {
      seatLayout.push_back(std::vector<char>());
      for (char c : *begin)
      {
        seatLayout[row].push_back(c);
      }
      ++row;
      ++begin;
    }
  }

  bool StepSimPart1()
  {
    TLayout oldLayout = seatLayout;

    const size_t rows = seatLayout.size();
    for (size_t y = 0; y < rows; ++y)
    {
      const size_t cols = seatLayout[y].size();
      for (size_t x = 0; x < cols; ++x)
      {
        char& cell = oldLayout[y][x];
        if (cell == FLOOR)
        {
          continue;
        }
        if (cell == CHAIR)
        {
          if (CountAdjacentPeople(oldLayout, y, x, rows, cols) == 0)
          {
            seatLayout[y][x] = PERSON;
          }
        }
        else if (cell == PERSON)
        {
          if (CountAdjacentPeople(oldLayout, y, x, rows, cols) >= 4)
          {
            seatLayout[y][x] = CHAIR;
          }
        }
      }
    }
    return (oldLayout == seatLayout);
  }

  bool StepSimPart2()
  {
    TLayout oldLayout = seatLayout;

    const size_t rows = seatLayout.size();
    for (size_t y = 0; y < rows; ++y)
    {
      const size_t cols = seatLayout[y].size();
      for (size_t x = 0; x < cols; ++x)
      {
        char& cell = oldLayout[y][x];
        if (cell == FLOOR)
        {
          continue;
        }
        if (cell == CHAIR)
        {
          if (CountVisiblePeople(oldLayout, y, x, rows, cols) == 0)
          {
            seatLayout[y][x] = PERSON;
          }
        }
        else if (cell == PERSON)
        {
          if (CountVisiblePeople(oldLayout, y, x, rows, cols) >= 5)
          {
            seatLayout[y][x] = CHAIR;
          }
        }
      }
    }
    return (oldLayout == seatLayout);
  }

  size_t CountAdjacentPeople(TLayout& layout, int row, int col, int rows, int cols) const
  {
    size_t count = 0;
    for (auto [dx, dy]
      : std::initializer_list<std::pair<int, int>>(
        { {-1,-1},{-1,0},{-1,+1},
      {0,-1},{0,1},
      {1,-1},{1,0},{1,1} }))
    {
      if (row + dy >= 0 && row + dy < rows 
        && col + dx >= 0 && col + dx < cols 
        && layout[row+dy][col+dx] == PERSON) ++count;
    }
    return count;
  }

  size_t CountVisiblePeople(TLayout& layout, size_t row, size_t col, size_t rows, size_t cols) const
  {
    size_t count = 0;
    for (auto [ddx, ddy]
      : std::initializer_list<std::pair<int, int>>(
        { {-1,-1},{-1,0},{-1,+1},
      {0,-1},{0,1},
      {1,-1},{1,0},{1,1} }))
    {
      int dx = ddx;
      int dy = ddy;
      while (row + dy >= 0 && row + dy < rows
        && col + dx >= 0 && col + dx < cols)
      {
        char& cell = layout[row + dy][col + dx];
        if (cell == FLOOR)
        {
          dx += ddx;
          dy += ddy;
        }
        else
        {
          if (cell == PERSON) ++count;
          break;
        }
      }
    }
    return count;
  }

  size_t CountPeople() const
  {
    size_t count = 0;
    for (auto& row : seatLayout)
    {
      for (char c : row)
      {
        if (c == PERSON) ++count;
      }
    }
    return count;
  }
};

int main()
{
  std::ifstream file("Input.txt");

  std::vector<std::string> layout;
  while (file)
  {
    std::string line;
    std::getline(file, line);
    if (!line.empty()) layout.push_back(line);
  }
  SeatSim sim;

  // Part 1
  sim.SetSeatLayout(layout.begin(), layout.end());
  while (!sim.StepSimPart1()) {}
  std::cout << "Part 1: " << sim.CountPeople() << '\n';

  // Part 2
  sim.SetSeatLayout(layout.begin(), layout.end()); // Reset
  while (!sim.StepSimPart2()) {}
  std::cout << "Part 2: " << sim.CountPeople() << '\n';
}