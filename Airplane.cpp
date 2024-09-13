#include "Airplane.h"
#include <iostream>

int Airplane::bookingCounter = 1;

bool Airplane::isSeatAvailable(const string& seat) const {
    return bookings.find(seat) == bookings.end();
}

int Airplane::getPriceForSeat(const string& seat) const {
    int row = stoi(seat.substr(0, seat.size() - 1));
    for (const auto& priceRange : priceRanges) {
        if (row >= priceRange.startRow && row <= priceRange.endRow) {
            return priceRange.price;
        }
    }
    return 0;
}

bool Airplane::bookSeat(const string& seat, const string& username) {
    if (seat.size() < 2 || !isdigit(seat[0])) {
        cout << "Error: Invalid seat format! Seat should be in the format '1A'." << endl;
        return false;
    }

    int row = stoi(seat.substr(0, seat.size() - 1));
    char seatLetter = seat.back();

    if (row < priceRanges.front().startRow || row > priceRanges.back().endRow) {
        cout << "Error: Row " << row << " is out of bounds!" << endl;
        return false;
    }

    if ((seatLetter - 'A') >= seatsPerRow) {
        cout << "Error: Seat letter " << seatLetter << " is invalid!" << endl;
        return false;
    }

    if (!isSeatAvailable(seat)) {
        cout << "Error: Seat " << seat << " is already booked!" << endl;
        return false;
    }

    int bookingID = generateBookingID();
    int seatPrice = getPriceForSeat(seat);
    if (seatPrice <= 0) {
        cout << "Error: Invalid price for seat " << seat << "!" << endl;
        return false;
    }

    bookings[seat] = Ticket(username, seat, bookingID, seatPrice);
    cout << "Booking confirmed with ID: " << bookingID << endl;
    return true;
}

bool Airplane::returnTicket(int bookingID) {
    for (auto it = bookings.begin(); it != bookings.end(); ++it) {
        if (it->second.getBookingID() == bookingID) {
            cout << "Confirmed $" << it->second.getPrice()
                 << " refund for " << it->second.getUsername() << endl;
            bookings.erase(it);
            return true;
        }
    }
    return false;
}

int Airplane::generateBookingID() {
    return bookingCounter++;
}

void Airplane::displayFlightInfo() const {
    cout << "Date: " << date << endl;
    cout << "Flight Number: " << flightNumber << endl;
    cout << "Seats per row: " << seatsPerRow << endl;

    cout << "Price per row range:" << endl;
    for (const auto &priceRange : priceRanges) {
        cout << "  Rows " << priceRange.startRow << "-" << priceRange.endRow
             << ": $" << priceRange.price << endl;
    }

    int totalRows = priceRanges.back().endRow;
    cout << "Total number of rows: " << totalRows << endl;

    int totalSeats = totalRows * seatsPerRow;
    cout << "Total number of seats: " << totalSeats << endl;
    cout << "--------------------------" << endl;
}

void Airplane::displaySeats() const {
    string seatLabels = "   ";
    for (int i = 0; i < seatsPerRow; ++i) {
        seatLabels += static_cast<char>('A' + i);
        if (i < seatsPerRow - 1) seatLabels += " ";
    }

    cout << seatLabels << endl;

    for (int row = 1; row <= priceRanges.back().endRow; ++row) {
        if (row < 10) {
            cout << " ";
        }
        cout << row << " ";

        for (int col = 0; col < seatsPerRow; ++col) {
            string seat = to_string(row) + static_cast<char>('A' + col);
            if (isSeatAvailable(seat)) {
                cout << "1 ";
            } else {
                cout << "X ";
            }
        }
        cout << endl;
    }
}