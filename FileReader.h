#pragma once
#include <vector>
#include "Airplane.h"

using namespace std;

class FileReader {
public:
    static vector<Airplane> parseData(const string &filename);
};
