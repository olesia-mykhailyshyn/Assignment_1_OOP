#include "Parsing.h"
#include <fstream>
#include <sstream>
#include <iostream>

vector<PriceRange> parsePriceRanges(const string& rangeStr) {
    vector<PriceRange> priceRanges;
    stringstream ss(rangeStr);
    string range;

    while (ss >> range) {
        if (range.empty()) continue;

        PriceRange priceRange;
        size_t dollarPos = range.find('$');
        if (dollarPos == string::npos) {
            cerr << "Invalid format for price range: " << range << endl;
            continue;
        }

        string seats = range.substr(0, dollarPos);
        string priceStr = range.substr(dollarPos + 1);

        size_t dashPos = seats.find('-');
        if (dashPos == string::npos) {
            cerr << "Invalid seat range format: " << seats << endl;
            continue;
        }

        string startSeatStr = seats.substr(0, dashPos);
        string endSeatStr = seats.substr(dashPos + 1);

        try {
            priceRange.startSeat = stoi(startSeatStr);
            priceRange.endSeat = stoi(endSeatStr);
        } catch (const invalid_argument& e) {
            cerr << "Invalid seat range format: " << seats << endl;
            continue;
        }

        try {
            priceRange.price = stoi(priceStr);
        } catch (const invalid_argument& e) {
            cerr << "Invalid price format: " << priceStr << endl;
            continue;
        }

        priceRanges.push_back(priceRange);
    }

    return priceRanges;
}

vector<Flight> parseFlights(const string& filename) {
    vector<Flight> flights;
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Could not open the file: " << filename << endl;
        return flights;
    }

    string line;
    while (getline(file, line)) {
        if (line.empty() || line[0] == '/') continue;

        Flight flight;
        stringstream ss(line);
        string priceRangesStr;

        ss >> flight.date >> flight.flightNumber >> flight.totalSeats;

        getline(ss, priceRangesStr);
        priceRangesStr = priceRangesStr.substr(1);

        flight.priceRanges = parsePriceRanges(priceRangesStr);
        flights.push_back(flight);
    }

    file.close();
    return flights;
}

void printFlights(const vector<Flight>& flights) {
    for (const auto& flight : flights) {
        cout << "Date: " << flight.date << ", Flight Number: " << flight.flightNumber
             << ", Total Seats: " << flight.totalSeats << endl;
        for (const auto& range : flight.priceRanges) {
            cout << "  Seats " << range.startSeat << "-" << range.endSeat
                 << ": $" << range.price << endl;
        }
    }
}
