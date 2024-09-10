#include "Airplane.h"
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
    cout << "Flight Number: " << "FR123" << endl;
    cout << "Total Seats: " << seats << endl;
    cout << "----- Available Seats -----" << endl;

    int columns = 2;
    for (int i = 1; i <= seats; ++i) {
        string seat = to_string(i);
        if (bookedTickets.find(seat) == bookedTickets.end()) {
            cout << seat;
        } else {
            cout << "X";
        }

        if (i % columns == 0) {
            cout << "  ";
        } else {
            cout << "\t";
        }

        if (i % (columns * 5) == 0) {
            cout << endl;
        }
    }
    cout << "\n----------------------------\n";
}


void Airplane::viewBookedTickets() const {
    if (bookedTickets.empty()) {
        cout << "No tickets booked yet.\n";
    } else {
        for (const auto& pair : bookedTickets) {
            cout << "Seat: " << pair.first << ", Passenger: " << pair.second.getPassengerName() << endl;
        }
    }
}

void Airplane::getAvailableSeatsWithPrices() const {
    cout << "Available seats with prices:\n";
    for (const auto& [seat, price] : pricing) {
        if (bookedTickets.find(to_string(seat)) == bookedTickets.end()) {
            cout << seat << " " << price << "$, ";
        }
    }
    cout << endl;
}
