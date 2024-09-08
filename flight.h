#pragma once

#include <string>
#include <vector>
#include "ticket.h"
#include "airplane.h"

using namespace  std;

class Flight {
public:
    Flight(const string& flightNumber, const Airplane& airplane);
    void addTicket(const Ticket& ticket);
    void removeTicket(const string& seat);
    void displayTickets() const;
    void displayFlightDetails() const;

private:
    string flightNumber;
    Airplane airplane;
    vector<Ticket> tickets;
};