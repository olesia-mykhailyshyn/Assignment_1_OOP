#include "CLI.h"
#include <iostream>

using namespace std;

CLI::CLI(Airplane& airplane) : airplane(airplane) {}

void CLI::run() {
    int choice;
    do {
        cout << "1. Check seat availability\n";
        cout << "2. Book a ticket\n";
        cout << "3. Return a ticket\n";
        cout << "4. View booked tickets\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1: checkSeatAvailability(); break;
            case 2: bookTicket(); break;
            case 3: returnTicket(); break;
            case 4: viewBookedTickets(); break;
            case 5: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice.\n";
        }
    } while (choice != 5);
}

void CLI::checkSeatAvailability() {
    airplane.displayAvailableSeats();
}

void CLI::bookTicket() {
    string seat, passengerName;
    cout << "Enter seat number: ";
    cin >> seat;
    cout << "Enter passenger name: ";
    cin >> passengerName;

    // Example flight number and price; in real use, these should be dynamic
    string flightNumber = "FL123";
    int price = 100;

    Ticket ticket(passengerName, seat, flightNumber, price);
    if (airplane.bookSeat(seat, ticket)) {
        cout << "Ticket booked successfully.\n";
    } else {
        cout << "Error: Seat is already booked.\n";
    }
}

void CLI::returnTicket() {
    string seat;
    cout << "Enter seat number to return: ";
    cin >> seat;
    if (airplane.returnTicket(seat)) {
        cout << "Ticket returned successfully.\n";
    } else {
        cout << "Error: Seat not found.\n";
    }
}

void CLI::viewBookedTickets() {
    airplane.viewBookedTickets();
}
