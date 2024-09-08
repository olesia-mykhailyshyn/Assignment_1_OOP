#include "FileReader.h"
#include <fstream>
#include <sstream>
#include <iostream>

bool FileReader::readFlightData(const std::string& filename, std::vector<Airplane>& airplanes) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string date, flightNumber;
        int seats;
        if (!(iss >> date >> flightNumber >> seats)) {
            std::cerr << "Error parsing line: " << line << std::endl;
            continue; // Skip to the next line
        }

        std::map<int, int> pricing;
        int row;
        std::string priceStr;
        while (iss >> row >> priceStr) {
            try {
                // Remove dollar sign if present
                if (priceStr.front() == '$') {
                    priceStr = priceStr.substr(1);
                }
                int price = std::stoi(priceStr);
                pricing[row] = price;
            } catch (const std::invalid_argument& e) {
                std::cerr << "Invalid price format in line: " << line << std::endl;
                continue;
            }
        }

        airplanes.emplace_back(seats, pricing);
    }

    file.close();
    return true;
}
