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
    int price;  // Price of the ticket

    Booking() : username(""), seat(""), bookingID(0), price(0) {}

    Booking(const string& user, const string& seatNo, int id, int seatPrice)
            : username(user), seat(seatNo), bookingID(id), price(seatPrice) {}
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
    bool returnTicket(int bookingID);
    int generateBookingID();
    int getPriceForSeat(const string& seat) const;
};

Flight parseLine(const string &line);
vector<Flight> parseData(const string &data);
void displaySeats(const Flight &flight);
void displayFlightInfo(const Flight &flight);
