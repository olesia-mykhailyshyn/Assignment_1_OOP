#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include "Ticket.h"

using namespace std;

struct PriceRange {
    int startRow;
    int endRow;
    int price;
};

class Airplane {
private:
    string date;
    string flightNumber;
    int seatsPerRow{};
    vector<PriceRange> priceRanges;
    unordered_map<string, Ticket> bookings;

    static int bookingCounter;

public:
    Airplane() = default;

    string getDate() const { return date; }
    string getFlightNumber() const { return flightNumber; }
    const unordered_map<string, Ticket>& getBookings() const { return bookings; }

    void setDate(const string& d) { date = d; }
    void setFlightNumber(const string& fn) { flightNumber = fn; }
    void setSeatsPerRow(int spr) { seatsPerRow = spr; }
    void setPriceRanges(const vector<PriceRange>& ranges) { priceRanges = ranges; }

    bool bookSeat(const string& seat, const string& username);
    bool isSeatAvailable(const string& seat) const;
    bool returnTicket(int bookingID);
    static int generateBookingID();
    int getPriceForSeat(const string& seat) const;
    void displaySeats() const;
    void displayFlightInfo() const;
};