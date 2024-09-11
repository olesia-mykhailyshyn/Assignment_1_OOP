#include "BookingManager.h"
#include <iostream>

using namespace std;

void BookingManager::viewBookingByID(int bookingID) const {
    for (const auto& flight : flights) {
        for (const auto& [seat, booking] : flight.bookings) {
            if (booking.bookingID == bookingID) {
                cout << "> Flight " << flight.flight_number << ", " << flight.date
                          << ", seat " << booking.seat
                          << ", price $" << booking.price
                          << ", " << booking.username << endl;
                return;
            }
        }
    }
    cout << "> Booking ID " << bookingID << " not found!" << endl;
}

void BookingManager::viewBookingsByUsername(const string& username) const {
    bool bookingFound = false;
    for (const auto& flight : flights) {
        for (const auto& [seat, booking] : flight.bookings) {
            if (booking.username == username) {
                cout << "> Flight " << flight.flight_number
                          << ", " << flight.date
                          << ", seat " << booking.seat
                          << ", price $" << booking.price << endl;
                bookingFound = true;
            }
        }
    }
    if (!bookingFound) {
        cout << "> No bookings found for username: " << username << endl;
    }
}

void BookingManager::viewBookingsByFlight(const string& date, const string& flightNumber) const {
    bool flightFound = false;
    for (const auto& flight : flights) {
        if (flight.date == date && flight.flight_number == flightNumber) {
            flightFound = true;
            cout << "> Bookings for Flight " << flight.flight_number << " on " << flight.date << ":" << endl;
            for (const auto& [seat, booking] : flight.bookings) {
                cout << "Seat: " << seat
                          << ", Username: " << booking.username
                          << ", Price: $" << booking.price << endl;
            }
            break;
        }
    }
    if (!flightFound) {
        cout << "> Flight not found for the given date and flight number." << endl;
    }
}
