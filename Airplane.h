#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include "Ticket.h"

using namespace std;

struct PriceRange {
    int start_row;
    int end_row;
    int price;
};

class Airplane {
private:
    string date;
    string flight_number;
    int seats_per_row{};
    vector<PriceRange> price_ranges;
    unordered_map<string, Ticket> bookings;

    static int bookingCounter;

public:
    Airplane() = default;

    string getDate() const { return date; }
    string getFlightNumber() const { return flight_number; }
    const unordered_map<string, Ticket>& getBookings() const { return bookings; }

    void setDate(const string& d) { date = d; }
    void setFlightNumber(const string& fn) { flight_number = fn; }
    void setSeatsPerRow(int spr) { seats_per_row = spr; }
    void setPriceRanges(const vector<PriceRange>& ranges) { price_ranges = ranges; }

    bool bookSeat(const string& seat, const string& username);
    bool isSeatAvailable(const string& seat) const;
    bool returnTicket(int bookingID);
    static int generateBookingID();
    int getPriceForSeat(const string& seat) const;
    void displaySeats() const;
    void displayFlightInfo() const;
};