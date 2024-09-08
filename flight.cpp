#include "flight.h"
#include <iostream>

using namespace std;

Flight::Flight(const string& flightNumber, const Airplane& airplane)
        : flightNumber(flightNumber), airplane(airplane) {}

void Flight::addTicket(const Ticket& ticket) {
    tickets.push_back(ticket);
}

void Flight::removeTicket(const std::string& seat) {
    for (auto it = tickets.begin(); it != tickets.end(); ++it) {
        if (it->getSeat() == seat) {
            tickets.erase(it);
            return;
        }
    }
}

void Flight::displayTickets() const {
    cout << "Tickets for flight " << flightNumber << ":\n";
    for (const auto& ticket : tickets) {
        cout << "Seat: " << ticket.getSeat() << ", Passenger: " << ticket.getPassengerName() << endl;
    }
}

void Flight::displayFlightDetails() const {
    cout << "Flight Number: " << flightNumber << endl;
    cout << "Airplane Details:\n";
    airplane.displayAvailableSeats();
}