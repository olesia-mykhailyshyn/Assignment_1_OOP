#include <iostream>
#include <vector>
#include <regex>
#include <unordered_map>
#include "FileReader.h"
#include "Airplane.h"
#include "BookingManager.h"

using namespace std;

bool isValidDate(const string& date) {
    regex datePattern(R"(\d{2}\.\d{2}\.\d{4})");
    return regex_match(date, datePattern);
}

bool isValidSeat(const string& seat) {
    regex seatPattern(R"(\d+[A-Z])");
    return regex_match(seat, seatPattern);
}

int main() {
    vector<Airplane> flights = FileReader::parseData(R"(C:\KSE\OOP_design\Assignment_1\configFile.txt)");

    if (flights.empty()) {
        cerr << "No flight data loaded. Exiting." << endl;
        return 1;
    }

    unordered_map<string, Airplane*> flightIndex;
    for (auto& flight : flights) {
        string key = flight.getDate() + "_" + flight.getFlightNumber();
        flightIndex[key] = &flight;
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

            if (!isValidDate(date)) {
                cout << "Invalid date format. Please use DD.MM.YYYY." << endl;
                continue;
            }

            bool flightFound = false;
            for (const auto& flight : flights) {
                if (flight.getDate() == date && flight.getFlightNumber() == flightNumber) {
                    flightFound = true;
                    flight.displayFlightInfo();
                    flight.displaySeats();
                    break;
                }
            }

            if (!flightFound) {
                cout << "Flight not found for the given date and flight number; or there is a problem related to parsing line." << endl;
            }
        } else if (command == "book") {
            string date, flightNumber, seat, username;

            cout << "Enter flight date (DD.MM.YYYY): " << endl;
            cin >> date;
            if (!isValidDate(date)) {
                cout << "Invalid date format. Please use DD.MM.YYYY." << endl;
                continue;
            }

            cout << "Enter flight number: " << endl;
            cin >> flightNumber;

            cout << "Enter seat (e.g., 1A): " << endl;
            cin >> seat;
            if (!isValidSeat(seat)) {
                cout << "Invalid seat format. Please use a valid seat (e.g., 1A)." << endl;
                continue;
            }

            cout << "Enter your username: " << endl;
            cin >> username;

            bool flightFound = false;
            for (auto& flight : flights) {
                if (flight.getDate() == date && flight.getFlightNumber() == flightNumber) {
                    flightFound = true;

                    if (!flight.bookSeat(seat, username)) {
                        cout << "Failed to book seat " << seat << "." << endl;
                    }
                    break;
                }
            }

            if (!flightFound) {
                cout << "Flight not found for the given date and flight number; or there is a problem related to parsing line." << endl;
            }
        } else if (command == "return") {
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
        } else if (command == "view") {
            string option;
            cout << "Enter 'ID', 'username', or 'flight': " << endl;
            cin >> option;

            if (option == "ID") {
                int bookingID;
                cout << "Enter booking ID: " << endl;
                cin >> bookingID;
                bookingManager.view(bookingID);
            } else if (option == "username") {
                string username;
                cout << "Enter username: " << endl;
                cin >> username;
                bookingManager.view(username);
            } else if (option == "flight") {
                string date, flightNumber;
                cout << "Enter flight date (DD.MM.YYYY): " << endl;
                cin >> date;
                cout << "Enter flight number: " << endl;
                cin >> flightNumber;

                if (!isValidDate(date)) {
                    cout << "Invalid date format. Please use DD.MM.YYYY." << endl;
                    continue;
                }

                bookingManager.view(date, flightNumber);
            } else {
                cout << "Unknown option. Please enter 'ID', 'username', or 'flight'." << endl;
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