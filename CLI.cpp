
#include "CLI.h"
#include <iostream>

using namespace std;

CLI::CLI(Airplane& airplane) : airplane(airplane) {}

void CLI::run() {
    string command;
    while (true) {
        cout << "\n------- Welcome to the Airplane Reservation System -------" << endl;
        cout << "1. Display Flights" << endl;
        cout << "2. Check Seat Availability" << endl;
        cout << "3. Book Ticket" << endl;
        cout << "4. Return Ticket" << endl;
        cout << "5. Exit" << endl;
        cout << "--------------------------------------------------------" << endl;
        cout << "> ";
        cin >> command;

        if (command == "1") {
        } else if (command == "2") {
            checkSeatAvailability();
        } else if (command == "3") {
            string date, flightNumber, seat, username;
            cout << "Enter Date, Flight Number, Seat, Username: ";
            cin >> date >> flightNumber >> seat >> username;
            bookTicket(date, flightNumber, seat, username);
        } else if (command == "4") {
            string bookingID;
            cout << "Enter Booking ID: ";
            cin >> bookingID;
            returnTicket(bookingID);
        } else if (command == "5") {
            cout << "Logging out..." << endl;
            break;
        } else {
            cout << "Invalid command, please try again." << endl;
        }
    }
}


void CLI::checkSeatAvailability() {
    airplane.displayAvailableSeats();
}

void CLI::bookTicket(const std::string& date, const std::string& flightNumber, const std::string& seat, const std::string& username) {
    int price = 100;  // Replace with logic to fetch dynamic pricing
    Ticket ticket(username, seat, flightNumber, price);
    bool success = airplane.bookSeat(seat, ticket);
    if (success) {
        cout << "Ticket booked successfully for " << username << ".";
    } else {
        cout << "Error: Seat is already booked.";
    }
}

void CLI::returnTicket(const std::string& bookingID) {
}

void CLI::viewBookingByID(const std::string& bookingID) {
    // Assuming bookingID is the seat number for simplicity
    auto it = airplane.bookedTickets.find(bookingID);
    if (it != airplane.bookedTickets.end()) {
        cout << "Booking found for seat " << bookingID << ":" << endl;
        cout << "Passenger Name: " << it->second.getPassengerName() << endl;
        cout << "Flight Number: " << it->second.getFlightNumber() << endl;
        cout << "Price: $" << it->second.getPrice() << endl;
    } else {
        cout << "Error: No booking found for seat " << bookingID << "." << endl;
    }
}

void CLI::viewBookingsByUsername(const std::string& username) {
}

void CLI::viewBookingsByFlight(const std::string& date, const std::string& flightNumber) {
    bool found = false;
    for (const auto& [seat, ticket] : airplane.bookedTickets) {
        if (ticket.getFlightNumber() == flightNumber) {
            cout << "Seat: " << seat << ", Passenger: " << ticket.getPassengerName() << ", Price: $" << ticket.getPrice() << endl;
            found = true;
        }
    }
    if (!found) {
        cout << "No bookings found for flight " << flightNumber << " on date " << date << "." << endl;
    }
}
