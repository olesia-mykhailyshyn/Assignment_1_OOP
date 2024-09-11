#pragma once
#include <string>
#include <vector>
#include <map>
#include "Ticket.h"

using namespace std;

struct PriceRange {
    int start_row;
    int end_row;
    int price;
};

class Airplane {
public:
    string date;
    string flight_number;
    int seats_per_row;
    vector<PriceRange> price_ranges;
    map<string, Ticket> bookings;

    static int bookingCounter;

    Airplane() = default;

    bool bookSeat(const string& seat, const string& username);
    bool isSeatAvailable(const string& seat) const;
    bool returnTicket(int bookingID);
    int generateBookingID();
    int getPriceForSeat(const string& seat) const;
    void displaySeats() const;
    void displayFlightInfo() const;
};
