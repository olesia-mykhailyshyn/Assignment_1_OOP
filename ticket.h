#pragma once

#include <string>

using namespace std;

class Ticket {
public:
    Ticket();
    Ticket(const string& passengerName, const string& seat, const string& flightNumber, int price);
    Ticket(const Ticket& other);
    Ticket(Ticket&& other) noexcept;
    ~Ticket();

    Ticket& operator=(const Ticket& other);
    Ticket& operator=(Ticket&& other) noexcept;

    string getPassengerName() const;
    string getSeat() const;
    string getFlightNumber() const;
    int getPrice() const;

private:
    string passengerName;
    string seat;
    string flightNumber;
    int price;
};