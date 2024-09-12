#pragma once
#include <vector>
#include "Airplane.h"

using namespace std;

class BookingManager {
private:
    vector<Airplane>& flights;

public:
    explicit BookingManager(vector<Airplane>& flights) : flights(flights) {}
    void view(int bookingID) const;
    void view(const string& username) const;
    void view(const string& date, const string& flightNumber) const;
};