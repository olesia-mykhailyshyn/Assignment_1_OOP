#pragma once
#include <string>

using namespace std;

class Ticket {
private:
    string username;
    string seat;
    int bookingID;
    int price;

public:
    Ticket() : bookingID(0), price(0) {}
    Ticket(const string& user, const string& seatNo, int id, int seatPrice)
            : username(user), seat(seatNo), bookingID(id), price(seatPrice) {}

    string getUsername() const { return username; }
    string getSeat() const { return seat; }
    int getBookingID() const { return bookingID; }
    int getPrice() const { return price; }
};