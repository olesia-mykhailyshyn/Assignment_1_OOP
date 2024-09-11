#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "parsing.h"

using namespace std;

void displayBookingInfo(const Flight& flight, int bookingID) {
    for (const auto& [seat, booking] : flight.bookings) {
        if (booking.bookingID == bookingID) {
            cout << "> Flight " << flight.flight_number
                 << ", " << flight.date
                 << ", seat " << booking.seat
                 << ", price " << booking.price << "$"
                 << ", " << booking.username << endl;
            return;
        }
    }
    cout << "> Booking ID " << bookingID << " not found!" << endl;
}

int main() {
    vector<Flight> flights;
    string filename = "C:\\KSE\\OOP_design\\Assignment_1\\configFile.txt";

    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return 1;
    }

    stringstream buffer;
    buffer << file.rdbuf();
    string data = buffer.str();
    file.close();

    flights = parseData(data);

    if (flights.empty()) {
        cerr << "No flight data loaded. Exiting." << endl;
        return 1;
    }

    while (true) {
        string command;
        cout << "\nEnter command (check/book/return/view/exit): ";
        cin >> command;

        if (command == "check") {
            string date, flightNumber;
            cout << "Enter flight date (DD.MM.YYYY): ";
            cin >> date;
            cout << "Enter flight number: ";
            cin >> flightNumber;

            bool flightFound = false;
            for (const auto& flight : flights) {
                if (flight.date == date && flight.flight_number == flightNumber) {
                    flightFound = true;
                    displayFlightInfo(flight);
                    displaySeats(flight);
                    break;
                }
            }

            if (!flightFound) {
                cout << "Flight not found for the given date and flight number." << endl;
            }
        }
        else if (command == "book") {
            string date, flightNumber, seat, username;
            cout << "Enter flight date (DD.MM.YYYY): ";
            cin >> date;
            cout << "Enter flight number: ";
            cin >> flightNumber;
            cout << "Enter seat (e.g., 1A): ";
            cin >> seat;
            cout << "Enter your username: ";
            cin >> username;

            bool flightFound = false;
            for (auto& flight : flights) {
                if (flight.date == date && flight.flight_number == flightNumber) {
                    flightFound = true;
                    flight.bookSeat(seat, username);
                    break;
                }
            }

            if (!flightFound) {
                cout << "Flight not found for the given date and flight number." << endl;
            }
        }
        else if (command == "return") {
            int bookingID;
            cout << "Enter booking ID: ";
            cin >> bookingID;

            bool bookingFound = false;
            for (auto& flight : flights) {
                if (flight.returnTicket(bookingID)) {
                    bookingFound = true;
                    break;
                }
            }

            if (!bookingFound) {
                cout << "> Booking ID " << bookingID << " not found!" << endl;
            }
        }
        else if (command == "view") {
            int bookingID;
            cout << "Enter booking ID: ";
            cin >> bookingID;

            bool bookingFound = false;
            for (const auto& flight : flights) {
                for (const auto& [seat, booking] : flight.bookings) {
                    if (booking.bookingID == bookingID) {
                        displayBookingInfo(flight, bookingID);
                        bookingFound = true;
                        break;
                    }
                }
                if (bookingFound) break;
            }

            if (!bookingFound) {
                cout << "> Booking ID " << bookingID << " not found!" << endl;
            }
        }
        else if (command == "exit") {
            cout << "Exiting the program." << endl;
            break;
        }
        else {
            cout << "Unknown command. Please enter 'check', 'book', 'return', 'view', or 'exit'." << endl;
        }
    }

    return 0;
}
