#pragma once

#include <string>
#include <vector>
#include <map>

using namespace std;

struct PriceRange {
    int start_row;
    int end_row;
    int price;
};

struct Booking {
    string username;
    string seat;
    int bookingID;

    Booking() : username(""), seat(""), bookingID(0) {}

    Booking(const string& user, const string& seatNo, int id)
            : username(user), seat(seatNo), bookingID(id) {}
};

class Flight {
public:
    string date;
    string flight_number;
    int seats_per_row;
    vector<PriceRange> price_ranges;
    map<string, Booking> bookings;

    static int bookingCounter;

    Flight() = default;

    bool bookSeat(const string& seat, const string& username);
    bool isSeatAvailable(const string& seat) const;
    int generateBookingID();
};

Flight parseLine(const string &line);
vector<Flight> parseData(const string &data);
void displaySeats(const Flight &flight);
void displayFlightInfo(const Flight &flight);
