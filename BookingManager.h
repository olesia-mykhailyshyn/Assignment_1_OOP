#pragma once
#include <vector>
#include "Airplane.h"

using namespace std;

class BookingManager {
public:
    explicit BookingManager(const vector<Airplane>& flights) : flights(flights) {}
    void viewBookingByID(int bookingID) const;
    void viewBookingsByUsername(const string& username) const;
    void viewBookingsByFlight(const string& date, const string& flightNumber) const;

private:
    vector<Airplane> flights;
};