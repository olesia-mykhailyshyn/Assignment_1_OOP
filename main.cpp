#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "parsing.h"
#include "CLI.h"

using namespace std;

int main() {
    vector<Flight> flights;
    string filename = R"(C:\KSE\OOP_design\Assignment_1\configFile.txt)";

    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return 1;
    }

    stringstream buffer;
    buffer << file.rdbuf();
    string data = buffer.str();
    file.close();

    flights = parseData(data);

    if (flights.empty()) {
        cerr << "No flight data loaded. Exiting." << endl;
        return 1;
    }

    displayFlights(flights);

    vector<Airplane> airplanes;

    if (!readFlightData(filename, airplanes)) {
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
