#pragma once
#include <vector>
#include <unordered_map>
#include "Airplane.h"

using namespace std;

class BookingManager {
private:
    vector<Airplane>& flights;
    unordered_map<int, Ticket*> bookingIDMap;
    unordered_map<string, vector<Ticket*>> userBookingMap;

public:
    explicit BookingManager(vector<Airplane>& flights) : flights(flights) {}
    void view(int bookingID) const;
    void view(const string& username) const;
    void view(const string& date, const string& flightNumber) const;
};