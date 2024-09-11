#pragma once
#include <vector>
#include "Airplane.h"

class BookingManager {
public:
    BookingManager(const std::vector<Airplane>& flights) : flights(flights) {}

    void viewBookingByID(int bookingID) const;
    void viewBookingsByUsername(const std::string& username) const;
    void viewBookingsByFlight(const std::string& date, const std::string& flightNumber) const;

private:
    std::vector<Airplane> flights;
};
