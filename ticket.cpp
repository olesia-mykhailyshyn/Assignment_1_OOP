#include "Ticket.h"

Ticket::Ticket()
        : passengerName(""), seat(""), flightNumber(""), price(0) {}

Ticket::Ticket(const string& passengerName, const string& seat, const string& flightNumber, int price)
        : passengerName(passengerName), seat(seat), flightNumber(flightNumber), price(price) {}

Ticket::Ticket(const Ticket& other)
        : passengerName(other.passengerName), seat(other.seat), flightNumber(other.flightNumber), price(other.price) {}

Ticket::Ticket(Ticket&& other) noexcept
        : passengerName(std::move(other.passengerName)), seat(std::move(other.seat)), flightNumber(std::move(other.flightNumber)), price(other.price) {
    other.price = 0;
}

Ticket::~Ticket() {}

Ticket& Ticket::operator=(const Ticket& other) {
    if (this != &other) {
        passengerName = other.passengerName;
        seat = other.seat;
        flightNumber = other.flightNumber;
        price = other.price;
    }
    return *this;
}

Ticket& Ticket::operator=(Ticket&& other) noexcept {
    if (this != &other) {
        passengerName = std::move(other.passengerName);
        seat = std::move(other.seat);
        flightNumber = std::move(other.flightNumber);
        price = other.price;
        other.price = 0;
    }
    return *this;
}

string Ticket::getPassengerName() const {
    return passengerName;
}

string Ticket::getSeat() const {
    return seat;
}

string Ticket::getFlightNumber() const {
    return flightNumber;
}

int Ticket::getPrice() const {
    return price;
}
