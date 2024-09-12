#include "Airplane.h"
#include <iostream>

int Airplane::bookingCounter = 1;

bool Airplane::isSeatAvailable(const string& seat) const {
    return bookings.find(seat) == bookings.end();
}

int Airplane::getPriceForSeat(const string& seat) const {
    int row = stoi(seat.substr(0, seat.size() - 1));
    for (const auto& priceRange : price_ranges) {
        if (row >= priceRange.start_row && row <= priceRange.end_row) {
            return priceRange.price;
        }
    }
    return 0;
}

bool Airplane::bookSeat(const string& seat, const string& username) {
    if (isSeatAvailable(seat)) {
        int bookingID = generateBookingID();
        int seatPrice = getPriceForSeat(seat);
        bookings[seat] = Ticket(username, seat, bookingID, seatPrice);
        cout << "> Confirmed with ID: " << bookingID << endl;
        return true;
    }
    cout << "> Seat " << seat << " is already booked!" << endl;
    return false;
}

bool Airplane::returnTicket(int bookingID) {
    for (auto it = bookings.begin(); it != bookings.end(); ++it) {
        if (it->second.bookingID == bookingID) {
            cout << "> Confirmed $" << it->second.price << " refund for " << it->second.username << endl;
            bookings.erase(it);
            return true;
        }
    }
    cout << "> Booking ID " << bookingID << " not found!" << endl;
    return false;
}

int Airplane::generateBookingID() {
    return bookingCounter++;
}

void Airplane::displayFlightInfo() const {
    cout << "Date: " << date << endl;
    cout << "Flight Number: " << flight_number << endl;
    cout << "Seats per row: " << seats_per_row << endl;

    cout << "Price per row range:" << endl;
    for (const auto &priceRange : price_ranges) {
        cout << "  Rows " << priceRange.start_row << "-" << priceRange.end_row
             << ": $" << priceRange.price << endl;
    }

    int totalRows = price_ranges.back().end_row;
    cout << "Total number of rows: " << totalRows << endl;

    int totalSeats = totalRows * seats_per_row;
    cout << "Total number of seats: " << totalSeats << endl;
    cout << "--------------------------" << endl;
}

void Airplane::displaySeats() const {
    string seatLabels = "A B C D E F G H";

    cout << seatLabels << endl;

    for (int row = 1; row <= price_ranges.back().end_row; ++row) {
        cout << row << " ";
        for (int col = 0; col < seats_per_row; ++col) {
            string seat = to_string(row) + seatLabels[col * 2];
            if (isSeatAvailable(seat)) {
                cout << "AV ";
            } else {
                cout << "X ";
            }
        }
        cout << endl;
    }
}