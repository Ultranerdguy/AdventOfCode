#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

#include "TicketManager.h"

int main()
{
  std::ifstream file("Input.txt");

  CTicketValidator validator;
  CTicket ourTicket;
  std::vector<CTicket> tickets;

  // Read fields
  while (file)
  {
    std::string line;
    std::getline(file, line);
    if (line.empty()) break; // End of fields

    size_t sepPos = line.find(':');
    std::string fieldName = line.substr(0, sepPos);
    std::stringstream strm(line.substr(sepPos+1));

    while (strm)
    {
      int first;
      int second;
      strm >> first;
      strm.ignore(1);
      strm >> second;
      strm.ignore(4);
      validator.GetField(fieldName).push_back(std::make_pair(first, second));
    }
  }

  // Read our ticket
  // Read 3 lines, first the line saying it's our ticket, then our ticket, then empty
  std::string line;
  std::getline(file, line);
  std::getline(file, line);
  std::stringstream strm(line);
  int ticketValue;
  while (strm >> ticketValue)
  {
    ourTicket.AddValue(ticketValue);
    strm.ignore(1);
  }
  std::getline(file, line);

  // Read "nearby tickets:"
  std::getline(file, line);
  // Read all other tickets
  while (file)
  {
    std::string line;
    std::getline(file, line);
    if (line.empty()) break;

    std::stringstream strm(line);
    CTicket nextTicket;
    int ticketValue;
    while (strm >> ticketValue)
    {
      nextTicket.AddValue(ticketValue);
      strm.ignore(1);
    }
    tickets.push_back(nextTicket);
  }

  // Part 1
  size_t invalidSum = 0;
  for (auto ti = tickets.begin(); ti != tickets.end();)
  {
    const size_t s = validator.GetInvalidValues(*ti);
    if (s != -1)
    {
      invalidSum += s;
      ti = tickets.erase(ti);
    }
    else
    {
      ++ti;
    }
  }
  std::cout << "Part 1: " << invalidSum << '\n';

  // Part 2
  // Tickets have already been filtered from part 1
  // Can assume that there is a solution
  validator.InitialiseFieldIndexMap(ourTicket.GetValues().size());
  for (auto itr = tickets.begin(); itr != tickets.end(); ++itr)
  {
    validator.UpdateFieldIndexMap(*itr);
  }
  validator.ValidateFieldIndexMap();

  std::cout << "Part 2: " << validator.DepartureFieldsProduct(ourTicket) << '\n';
}