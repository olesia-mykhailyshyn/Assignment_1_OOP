#include <iostream>
#include <vector>
#include "FileReader.h"
#include "Airplane.h"

using namespace std;

void viewBookingByID(const vector<Airplane>& flights, int bookingID) {
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

void viewBookingsByUsername(const vector<Airplane>& flights, const string& username) {
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

void viewBookingsByFlight(const vector<Airplane>& flights, const string& date, const string& flightNumber) {
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

int main() {
    vector<Airplane> flights = FileReader::parseData("C:\\KSE\\OOP_design\\Assignment_1\\configFile.txt");

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
                    flight.displayFlightInfo();
                    flight.displaySeats();
                    break;
                }
            }

            if (!flightFound) {
                cout << "Flight not found for the given date and flight number." << endl;
            }
        } else if (command == "book") {
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
        } else if (command == "return") {
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
        } else if (command == "view") {
            string option;
            cout << "Enter 'ID', 'username', or 'flight': ";
            cin >> option;

            if (option == "ID") {
                int bookingID;
                cout << "Enter booking ID: ";
                cin >> bookingID;
                viewBookingByID(flights, bookingID);
            } else if (option == "username") {
                string username;
                cout << "Enter username: ";
                cin >> username;
                viewBookingsByUsername(flights, username);
            } else if (option == "flight") {
                string date, flightNumber;
                cout << "Enter flight date (DD.MM.YYYY): ";
                cin >> date;
                cout << "Enter flight number: ";
                cin >> flightNumber;
                viewBookingsByFlight(flights, date, flightNumber);
            }
        } else if (command == "exit") {
            cout << "Exiting the program." << endl;
            break;
        } else {
            cout << "Unknown command. Please enter 'check', 'book', 'return', 'view', or 'exit'." << endl;
        }
    }

    return 0;
}
