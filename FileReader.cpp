#include "FileReader.h"
#include "RAII.h"
#include <sstream>
#include <iostream>
#include <regex>

using namespace std;

vector<Airplane> FileReader::parseData(const string& filename) {
    vector<Airplane> flights;

    wstring wfilename = wstring(filename.begin(), filename.end());

    try {
        FileRAII file(wfilename, GENERIC_READ, OPEN_EXISTING);

        const DWORD bufferSize = 1024;
        char buffer[bufferSize];
        DWORD bytesRead = file.Read(buffer, bufferSize);
        if (bytesRead == 0) {
            cerr << "File is empty or could not be read." << endl;
            return flights;
        }

        stringstream ss(string(buffer, bytesRead));
        string line;
        regex pattern(R"((\d{2}\.\d{2}\.\d{4})\s+([A-Z0-9]+)\s+(\d+)\s+((?:\d+-\d+\s+\d+\$\s*)+))");

        while (getline(ss, line)) {
            Airplane flight;
            smatch match;

            if (regex_search(line, match, pattern)) {
                flight.setDate(match[1]);
                flight.setFlightNumber(match[2]);
                flight.setSeatsPerRow(stoi(match[3]));

                string prices = match[4];
                regex price_pattern(R"((\d+)-(\d+)\s+(\d+)\$)");
                smatch price_match;
                string::const_iterator search_start(prices.cbegin());

                vector<PriceRange> price_ranges;
                while (regex_search(search_start, prices.cend(), price_match, price_pattern)) {
                    PriceRange pr{};
                    pr.start_row = stoi(price_match[1]);
                    pr.end_row = stoi(price_match[2]);
                    pr.price = stoi(price_match[3]);
                    price_ranges.push_back(pr);

                    search_start = price_match.suffix().first;
                }
                flight.setPriceRanges(price_ranges);

                flights.push_back(flight);
            }
        }
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }

    return flights;
}