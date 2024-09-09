#include "parsing.h"
#include <iostream>
#include <sstream>
#include <regex>
#include <fstream>

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

void displayFlights(const vector<Flight> &flights) {
    for (const auto &flight : flights) {
        cout << "Date: " << flight.date << endl;
        cout << "Flight Number: " << flight.flight_number << endl;
        cout << "Seats per row: " << flight.seats_per_row << endl;
        cout << "Price Ranges:" << endl;
        for (const auto &pr : flight.price_ranges) {
            cout << "  Rows " << pr.start_row << "-" << pr.end_row << ": $" << pr.price << endl;
        }
        cout << "--------------------------" << endl;
    }
}

bool readFlightData(const string &filename, vector<Airplane> &airplanes) {

    ifstream file(filename);
    if (!file.is_open()) {
        return false;
    }


    file.close();
    return true;
}
