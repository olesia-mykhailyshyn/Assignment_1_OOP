#include "Airplane.h"
#include "Ticket.h"
#include <iostream>

using namespace std;

Airplane::Airplane(int seats, const map<int, int>& pricing)
        : seats(seats), pricing(pricing) {}

bool Airplane::bookSeat(const string& seat, const Ticket& ticket) {
    if (bookedTickets.find(seat) != bookedTickets.end()) {
        return false;
    }
    bookedTickets[seat] = ticket;
    return true;
}

bool Airplane::returnTicket(const string& seat) {
    auto it = bookedTickets.find(seat);
    if (it != bookedTickets.end()) {
        bookedTickets.erase(it);
        return true;
    }
    return false;
}

void Airplane::displayAvailableSeats() const {
    cout << "Available seats:\n";
    for (int i = 1; i <= seats; ++i) {
        string seat = to_string(i);
        if (bookedTickets.find(seat) == bookedTickets.end()) {
            cout << seat << " ";
        }
    }
    cout << endl;
}

void Airplane::viewBookedTickets() const {
    if (bookedTickets.empty()) {
        std::cout << "No tickets booked yet.\n";
    } else {
        for (const auto& pair : bookedTickets) {
            cout << "Seat: " << pair.first << ", Passenger: " << pair.second.getPassengerName() << endl;
        }
    }
}