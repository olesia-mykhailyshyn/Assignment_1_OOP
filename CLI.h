
#ifndef CLI_H
#define CLI_H

#include <string>
#include <vector>
#include "Airplane.h"
#include "Flight.h"
#include "parsing.h"

class CLI {
public:
    CLI(Airplane& airplane);
    void checkSeatAvailability();
    void bookTicket(const std::string& date, const std::string& flightNumber, const std::string& seat, const std::string& username);
    void returnTicket(const std::string& bookingID);
    void viewBookingByID(const std::string& bookingID);
    void viewBookingsByUsername(const std::string& username);
    void viewBookingsByFlight(const std::string& date, const std::string& flightNumber);
    void run();

private:
    Airplane& airplane;
    std::vector<Flight> flights;
};

#endif // CLI_H
