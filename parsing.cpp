#include "parsing.h"
#include <iostream>
#include <sstream>
#include <regex>

using namespace std;

Flight parseLine(const string &line) {
    Flight flight;
    smatch match;
    regex pattern(R"((\d{2}\.\d{2}\.\d{4})\s+([A-Z0-9]+)\s+(\d+)\s+((?:\d+-\d+\s+\d+\$\s*)+))");

    if (regex_search(line, match, pattern)) {
        flight.date = match[1];
        flight.flight_number = match[2];
        flight.seats_per_row = stoi(match[3]);

        string prices = match[4];
        regex price_pattern(R"((\d+)-(\d+)\s+(\d+)\$)");
        smatch price_match;
        string::const_iterator search_start(prices.cbegin());

        while (regex_search(search_start, prices.cend(), price_match, price_pattern)) {
            PriceRange pr;
            pr.start_row = stoi(price_match[1]);
            pr.end_row = stoi(price_match[2]);
            pr.price = stoi(price_match[3]);
            flight.price_ranges.push_back(pr);

            search_start = price_match.suffix().first;
        }
    }

    return flight;
}

vector<Flight> parseData(const string &data) {
    vector<Flight> flights;
    stringstream ss(data);
    string line;

    while (getline(ss, line)) {
        Flight flight = parseLine(line);
        if (!flight.flight_number.empty()) {
            flights.push_back(flight);
        }
    }

    return flights;
}

void displayFlightInfo(const Flight &flight) {
    cout << "Date: " << flight.date << endl;
    cout << "Flight Number: " << flight.flight_number << endl;
    cout << "Seats per row: " << flight.seats_per_row << endl;

    cout << "Price per row range:" << endl;
    for (const auto &priceRange : flight.price_ranges) {
        cout << "  Rows " << priceRange.start_row << "-" << priceRange.end_row
             << ": $" << priceRange.price << endl;
    }

    int totalRows = flight.price_ranges.back().end_row;
    cout << "Total number of rows: " << totalRows << endl;

    int totalSeats = totalRows * flight.seats_per_row;
    cout << "Total number of seats: " << totalSeats << endl;
    cout << "--------------------------" << endl;
}

void displaySeats(const Flight &flight) {
    int totalRows = flight.price_ranges.back().end_row;
    string seats = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"; // Seat letters

    for (int i = 0; i < flight.seats_per_row; ++i) {
        cout << seats[i] << " ";
    }
    cout << endl;

    for (int row = 1; row <= totalRows; ++row) {
        cout << row << " ";
        for (int col = 0; col < flight.seats_per_row; ++col) {
            cout << "AV ";
        }
        cout << endl;
    }
}