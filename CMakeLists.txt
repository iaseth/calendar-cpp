cmake_minimum_required(VERSION 3.10)

# Project name and executable
project(CalendarApp)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the executable target
add_executable(cal src/calendar.cpp)
