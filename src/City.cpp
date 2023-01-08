#include "City.h"

City::City(string name, string country) : name(std::move(name)), country(std::move(country)){}

const string &City::getName() const {
    return name;
}

const string &City::getCountry() const {
    return country;
}

list<Airport> City::getAirports() const {
    return airports;
}

void City::addAirport(const Airport& airport) {
    this->airports.push_back(airport);
}

