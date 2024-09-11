#pragma once

#include <string>
#include <vector>

using namespace std;

struct PriceRange {
    int start_row;
    int end_row;
    int price;
};

struct Flight {
    string date;
    string flight_number;
    int seats_per_row;
    vector<PriceRange> price_ranges;
};

Flight parseLine(const string &line);
vector<Flight> parseData(const string &data);
void displaySeats(const Flight &flight);
void displayFlightInfo(const Flight &flight);