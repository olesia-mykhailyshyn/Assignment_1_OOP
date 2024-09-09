#pragma once

#include <string>
#include <map>
#include <vector>
#include "Ticket.h"

using namespace std;

class Airplane {
private:
    int seats;
    map<int, int> pricing;
    map<string, Ticket> bookedTickets;

public:
    Airplane(int seats, const map<int, int>& pricing);
    bool bookSeat(const string& seat, const Ticket& ticket);
    bool returnTicket(const string& seat);
    void displayAvailableSeats() const;
    void viewBookedTickets() const;
};
