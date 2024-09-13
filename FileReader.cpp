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

        stringstream buffer;
        const DWORD bufferSize = 1024;
        char tempBuffer[bufferSize];
        DWORD bytesRead;

        while ((bytesRead = file.Read(tempBuffer, bufferSize)) > 0) {
            buffer.write(tempBuffer, bytesRead);
        }

        string fileContent = buffer.str();
        stringstream ss(fileContent);
        string line;

        regex pattern(R"((\d{2}\.\d{2}\.\d{4})\s+([A-Z0-9]+)\s+(\d+)\s+((?:\d+-\d+\s+\d+\$\s*)+))");

        while (getline(ss, line)) {
            Airplane flight;
            smatch match;

            cout << "Processing line: " << line << endl;

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
            } else {
                cerr << "Failed to parse line: " << line << endl;
                if (line.find("  ") != string::npos) {
                    cerr << "Error: Extra spaces detected in the line." << endl;
                } else if (line.find("$") == string::npos) {
                    cerr << "Error: Missing price format ($) in the line." << endl;
                } else if (line.size() < 20) {
                    cerr << "Error: Line is too short and may be incomplete." << endl;
                }
            }
        }
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }

    return flights;
}