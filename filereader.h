#pragma once

#include <string>
#include <vector>
#include "Airplane.h"

using namespace std;

class FileReader {
public:
    static bool readFlightData(const string& filename, vector<Airplane>& airplanes);
};
