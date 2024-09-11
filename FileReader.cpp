#include "FileReader.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <regex>

vector<Airplane> FileReader::parseData(const string& filename) {
    vector<Airplane> flights;
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return flights;
    }

    stringstream buffer;
    buffer << file.rdbuf();
    string data = buffer.str();
    file.close();

    stringstream ss(data);
    string line;
    regex pattern(R"((\d{2}\.\d{2}\.\d{4})\s+([A-Z0-9]+)\s+(\d+)\s+((?:\d+-\d+\s+\d+\$\s*)+))");

    while (getline(ss, line)) {
        Airplane flight;
        smatch match;

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
            flights.push_back(flight);
        }
    }
    return flights;
}
