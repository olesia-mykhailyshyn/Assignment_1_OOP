#pragma once

#include <string>
#include <vector>
#include "Airplane.h"

using namespace std;

struct PriceRange {
    int startSeat;
    int endSeat;
    int price;
};

struct Flight {
    string date;
    string flightNumber;
    int totalSeats;
    vector<PriceRange> priceRanges;
};

vector<PriceRange> parsePriceRanges(const string& rangeStr);
vector<Flight> parseFlights(const string& filename);
void printFlights(const vector<Flight>& flights);