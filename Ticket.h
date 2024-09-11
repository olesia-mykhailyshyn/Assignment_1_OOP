#pragma once
#include <string>

using namespace std;

class Ticket {
public:
    string username;
    string seat;
    int bookingID;
    int price;

    Ticket() : username(""), seat(""), bookingID(0), price(0) {}
    Ticket(const string& user, const string& seatNo, int id, int seatPrice)
            : username(user), seat(seatNo), bookingID(id), price(seatPrice) {}
};
