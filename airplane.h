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

public:
    bool bookSeat(const string& seat, const Ticket& ticket);
    bool returnTicket(const string& seat);
    void displayAvailableSeats() const;
    void viewBookedTickets() const;
    void getAvailableSeatsWithPrices() const;

    map<string, Ticket> bookedTickets;

    Airplane(int seats, const map<int, int>& pricing);
};
