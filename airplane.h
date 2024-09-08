#pragma once

#include <string>
#include <map>
#include <vector>
#include "Ticket.h"

using namespace std;

class Airplane {
private:
    int seats;
    std::map<int, int> pricing;
    std::map<std::string, Ticket> bookedTickets;

public:
    Airplane(int seats, const std::map<int, int>& pricing);
    bool bookSeat(const std::string& seat, const Ticket& ticket);
    bool returnTicket(const std::string& seat);
    void displayAvailableSeats() const;
    void viewBookedTickets() const;
};

