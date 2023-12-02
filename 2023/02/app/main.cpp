// C++ include files
#include <iostream>
#include <string>
#include <fstream>
#include <string_view>
#include <sstream>

// Project specific files
#include "include.h"
#include "config.h"

struct Colours
{
  unsigned int red = 0;
  unsigned int green = 0;
  unsigned int blue = 0;
};

std::istream& operator>>(std::istream& input, Colours& colours)
{
  colours = {0,0,0};
  constexpr std::string_view red = "red";
  constexpr std::string_view green = "green";
  constexpr std::string_view blue = "blue";
  unsigned int count = 0;
  std::string word;
  bool readHand = false;
  while (input >> count >> word)
  {
    input.clear(); // successful read, make sure bits are set properly
    std::string_view wordview = word;
    
    readHand = true;
    if (wordview.substr(0,red.size()) == red) colours.red = count;
    else if (wordview.substr(0,green.size()) == green) colours.green = count;
    else if (wordview.substr(0,blue.size()) == blue) colours.blue = count;
    else readHand = false;

    if (wordview[wordview.size()-1] == ';') break;
  }

  if (readHand)
    input.clear();

  return input;
}

int main(int argc, char* argv[])
{
  if (argc < 2)
  {
    std::cout << "Usage: \n";
    std::cout << "  " << EXECUTABLE << " <input file>\n";
    return 1;
  }
  std::ifstream input(argv[1]);

  Colours maxAllowedColours{12,13,14};

  unsigned int IDCounter = 0;
  unsigned int powerSum = 0;
  std::string line;
  while (std::getline(input, line) && !line.empty())
  {
    std::stringstream lineStream(line);
    std::string word;
    unsigned int ID = 0;
    char c;
    lineStream >> word >> ID >> c;
    Colours maxColours;
    Colours handColour;
    while (lineStream >> handColour)
    {
      maxColours.red = std::max(maxColours.red, handColour.red);
      maxColours.green = std::max(maxColours.green, handColour.green);
      maxColours.blue = std::max(maxColours.blue, handColour.blue);
    }

    if (maxColours.red <= maxAllowedColours.red
      && maxColours.green <= maxAllowedColours.green 
      && maxColours.blue <= maxAllowedColours.blue)
    {
      IDCounter += ID;
    }

    powerSum += maxColours.red * maxColours.green * maxColours.blue;
  }

  std::cout << "Day 2 Part 1: " << IDCounter << '\n';
  std::cout << "Day 2 Part 2: " << powerSum << '\n';
}