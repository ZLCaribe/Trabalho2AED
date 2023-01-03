#include "Airport.h"

Airport::Airport(string cod, string name, string  city, string country, double longitude, double latitude) :
    cod(std::move(cod)),name(std::move(name)),city(std::move(city)),country(std::move(country)),longitude(longitude),
    latitude(latitude){}

Airport::Airport(string cod) :cod(std::move(cod)){}

const string &Airport::getCod() const {
    return cod;
}

const string &Airport::getName() const {
    return name;
}

const string &Airport::getCity() const {
    return city;
}

const string &Airport::getCountry() const {
    return country;
}

double Airport::getLongitude() const {
    return longitude;
}

double Airport::getLatitude() const {
    return latitude;
}

list<Flight> Airport::getFlights() const {
    return this->flights;
}

void Airport::addFlight(const Flight &flight) {
    this->flights.push_back(flight);
}

list<Flight> Airport::getFlightsTo(const string& airpoirt) {
    list<Flight> res;
    for(const auto& flight : this->flights)
        if(flight.getTarget() == airpoirt)
            res.push_back(flight);
    return res;
}
