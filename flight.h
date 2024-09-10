
#ifndef FLIGHT_H
#define FLIGHT_H

#include <string>
#include <vector>
#include "Airplane.h"
#include "Ticket.h"

class FlightDetails {
public:
    FlightDetails(const std::string& flightNumber, const Airplane& airplane);
    bool checkSeatAvailability(const std::string& seat) const;
    bool bookSeat(const std::string& seat, const Ticket& ticket);
    bool cancelBooking(const std::string& seat);
    void displayBookedSeats() const;

private:
    std::string flightNumber;
    Airplane airplane;
    std::vector<Ticket> tickets;
    std::string date;
};

#endif // FLIGHT_H
