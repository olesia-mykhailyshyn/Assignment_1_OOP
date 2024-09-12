#pragma once
#include <vector>
#include "Airplane.h"

using namespace std;

class BookingManager {
public:
    explicit BookingManager(vector<Airplane>& flights) : flights(flights) {}

    // View methods based on different criteria
    void view(int bookingID) const;
    void view(const string& username) const;
    void view(const string& date, const string& flightNumber) const;

    static int nextBookingID;

private:
    vector<Airplane>& flights;
};
