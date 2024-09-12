#include "BookingManager.h"
#include <iostream>

using namespace std;

void BookingManager::view(int bookingID) const {
    for (const auto& flight : flights) {
        for (const auto& [seat, booking] : flight.getBookings()) {
            if (booking.getBookingID() == bookingID) {
                cout << "Flight " << flight.getFlightNumber()
                     << ", " << flight.getDate()
                     << ", seat " << booking.getSeat()
                     << ", price $" << booking.getPrice()
                     << ", " << booking.getUsername() << endl;
                return;
            }
        }
    }
    cout << "Booking ID " << bookingID << " not found!" << endl;
}

void BookingManager::view(const string& username) const {
    bool bookingFound = false;
    int counter = 1;
    for (const auto& flight : flights) {
        for (const auto& [seat, booking] : flight.getBookings()) {
            if (booking.getUsername() == username) {
                cout << counter << ". Flight " << flight.getFlightNumber()
                     << ", " << flight.getDate()
                     << ", seat " << booking.getSeat()
                     << ", price $" << booking.getPrice() << endl;
                bookingFound = true;
                ++counter;
            }
        }
    }
    if (!bookingFound) {
        cout << "No bookings found for username: " << username << endl;
    }
}

void BookingManager::view(const string& date, const string& flightNumber) const {
    bool flightFound = false;
    for (const auto& flight : flights) {
        if (flight.getDate() == date && flight.getFlightNumber() == flightNumber) {
            flightFound = true;
            const auto& bookings = flight.getBookings();
            if (bookings.empty()) {
                cout << "No bookings found for flight " << flightNumber << " on " << date << endl;
                return;
            }

            cout << "Bookings for Flight " << flight.getFlightNumber() << " on " << flight.getDate() << ":" << endl;
            for (const auto& [seat, booking] : bookings) {
                cout << seat << " " << booking.getUsername() << " $" << booking.getPrice() << endl;
            }
            return;
        }
    }
    if (!flightFound) {
        cout << "Flight not found for the given date and flight number." << endl;
    }
}