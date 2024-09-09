cmake_minimum_required(VERSION 3.10)
project(Assignment_1)

set(CMAKE_CXX_STANDARD 17)

include_directories(${CMAKE_SOURCE_DIR})

add_executable(Assignment_1
        main.cpp
        CLI.cpp
        Flight.cpp
        airplane.cpp
        Ticket.cpp
        parsing.cpp
        parsing.h
)