
#include "Flight.h"


using namespace std;

FlightDetails::FlightDetails(const std::string& flightNumber, const Airplane& airplane)
        : flightNumber(flightNumber), airplane(airplane) {}

bool FlightDetails::checkSeatAvailability(const std::string& seat) const {
    return airplane.bookedTickets.find(seat) == airplane.bookedTickets.end();
}

bool FlightDetails::bookSeat(const std::string& seat, const Ticket& ticket) {
    return airplane.bookSeat(seat, ticket);
}

bool FlightDetails::cancelBooking(const std::string& seat) {
    return airplane.returnTicket(seat);
}

void FlightDetails::displayBookedSeats() const {
    airplane.viewBookedTickets();
}
