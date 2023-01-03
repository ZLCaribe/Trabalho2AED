#include "Airline.h"

Airline::Airline(string code, string name, string callsign, string country) :
        code(std::move(code)),name(std::move(name)),callsign(std::move(callsign)),country(std::move(country)){}

const string &Airline::getCode() const {
    return code;
}

const string &Airline::getName() const {
    return name;
}

const string &Airline::getCallsign() const {
    return callsign;
}

const string &Airline::getCountry() const {
    return country;
}

