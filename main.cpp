#include <iostream>
#include <vector>
#include "Parsing.h"
#include "FileReader.h"
#include "CLI.h"

using namespace std;

int main() {
    vector<Flight> flights;
    string filename = R"(C:\KSE\OOP_design\Assignment_1\configFile.txt)";

    flights = parseFlights(filename);

    if (flights.empty()) {
        cerr << "No flight data loaded. Exiting." << endl;
        return 1;
    }

    printFlights(flights);

    vector<Airplane> airplanes;

    if (!FileReader::readFlightData(filename, airplanes)) {
        cerr << "Failed to read flight data from file." << endl;
        return 1;
    }

    if (airplanes.empty()) {
        cerr << "No airplanes loaded. Exiting." << endl;
        return 1;
    }

    Airplane& airplane = airplanes[0];

    CLI cli(airplane);

    cli.run();

    return 0;
}