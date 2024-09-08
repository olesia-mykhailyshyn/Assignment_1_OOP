#pragma once

#include <string>
#include "airplane.h"

class CLI {
public:
    CLI(Airplane& airplane);
    void run();
private:
    Airplane& airplane;
    void checkSeatAvailability();
    void bookTicket();
    void returnTicket();
    void viewBookedTickets();
};