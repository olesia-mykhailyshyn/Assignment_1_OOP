#include <iostream>
#include <vector>
#include "FileReader.h"
#include "Airplane.h"
#include "BookingManager.h"

using namespace std;

int main() {
    vector<Airplane> flights = FileReader::parseData(R"(C:\KSE\OOP_design\Assignment_1\configFile.txt)");

    if (flights.empty()) {
        cerr << "No flight data loaded. Exiting." << endl;
        return 1;
    }

    BookingManager bookingManager(flights);

    while (true) {
        string command;
        cout << "\nEnter command (check/book/return/view/exit): " << endl;
        cin >> command;

        if (command == "check") {
            string date, flightNumber;
            cout << "Enter flight date (DD.MM.YYYY): "  << endl;
            cin >> date;
            cout << "Enter flight number: " << endl;
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

            cout << "Enter flight date (DD.MM.YYYY): " << endl;
            cin >> date;

            cout << "Enter flight number: " << endl;
            cin >> flightNumber;

            cout << "Enter seat (e.g., 1A): " << endl;
            cin >> seat;

            cout << "Enter your username: " << endl;
            cin >> username;

            bool flightFound = false;
            for (auto& flight : flights) {
                if (flight.date == date && flight.flight_number == flightNumber) {
                    flightFound = true;
                    if (!flight.bookSeat(seat, username)) {
                        cout << "Failed to book seat " << seat << "." << endl;
                    }
                    break;
                }
            }

            if (!flightFound) {
                cout << "Flight not found for the given date and flight number." << endl;
            }
        }


        else if (command == "return") {
            int bookingID;
            cout << "Enter booking ID: " << endl;
            cin >> bookingID;

            bool bookingFound = false;
            for (auto& flight : flights) {
                if (flight.returnTicket(bookingID)) {
                    bookingFound = true;
                    break;
                }
            }

            if (!bookingFound) {
                cout << "Booking ID " << bookingID << " not found!" << endl;
            }
        }
        else if (command == "view") {
            string option;
            cout << "Enter 'ID', 'username', or 'flight': ";
            cin >> option;

            if (option == "ID") {
                int bookingID;
                cout << "Enter booking ID: ";
                cin >> bookingID;
                bookingManager.viewBookingByID(bookingID);
            } else if (option == "username") {
                string username;
                cout << "Enter username: ";
                cin >> username;
                bookingManager.viewBookingsByUsername(username);
            } else if (option == "flight") {
                string date, flightNumber;
                cout << "Enter flight date (DD.MM.YYYY): ";
                cin >> date;
                cout << "Enter flight number: ";
                cin >> flightNumber;
                bookingManager.viewBookingsByFlight(date, flightNumber);
            } else {
                cout << "Unknown option. Please enter 'ID', 'username', or 'flight'." << endl;
            }
        }

        else if (command == "exit") {
            cout << "Exiting the program." << endl;
            break;
        } else {
            cout << "Unknown command. Please enter 'check', 'book', 'return', 'view', or 'exit'." << endl;
        }
    }

    return 0;
}