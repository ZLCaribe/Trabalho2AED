#include "Flight.h"

#include <utility>

Flight::Flight(string target, string  airline) :
    target(std::move(target)),airline(std::move(airline)) {}

const string &Flight::getTarget() const {
    return target;
}

const string &Flight::getAirline() const {
    return this->airline;
}
