#include "Airport.h"

Airport::Airport(string cod, string name, string  city, string country, double longitude, double latitude) :
    cod(std::move(cod)),name(std::move(name)),city(std::move(city)),country(std::move(country)),longitude(longitude),
    latitude(latitude){}

Airport::Airport(string cod) :cod(std::move(cod)){}

Airport::Airport() = default;

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

bool Airport::isVisited() const {
    return this->visited;
}

void Airport::setVisited() {
    this->visited = true;
}

int Airport::getDistance() const{
    return this->distance;
}

void Airport::setDistance(int newDistance) {
    this->distance = newDistance;
}

void Airport::addFlight(const Flight &flight) {
    this->flights.push_back(flight);
}

/**
 * procura voos partindo do aeroporto que chamou o método que vão para o aeroporto passado como parametro
 * COMPLEXIDADE: O(f)
 * @param airpoirt aeroporto de destino
 * @return lista com os voos que partem do aeroporto que chamou o método e vão para o aeroporto passado como parametro
 */
list<Flight> Airport::getFlightsTo(const string& airpoirt) {
    list<Flight> res;
    for(const auto& flight : this->flights)
        if(flight.getTarget() == airpoirt)
            res.push_back(flight);
    return res;
}

size_t Airport::getNFlights() {
    return flights.size();
}

/**
 * COMPLEXIDADE: O(f)
 * @return número de companhias aereas com voos partindo deste aeroporto
 */
size_t Airport::getNAirlines() {
    unordered_set<string> res;
    for(const auto& f : this->flights)
        res.insert(f.getAirline());
    return res.size();
}

/**
 * COMPLEXIDADE: O(f)
 * @return número de aeroportos atingiveis diretamente a partir deste aeroporto
 */
size_t Airport::getNDestinations() {
    unordered_set<string> res;
    for(const auto& f : this->flights)
        res.insert(f.getTarget());
    return res.size();
}

/**
 * faz reset ao aeroporto para poder utiliza-lo num dfs ou bfs
 */
void Airport::resetVisited() {
    this->visited = false;
    this->distance = 0;
}

void Airport::setVisitedF(){
    this->visited = false;
}

bool Airport::operator<(const Airport& airport) const{
    return this->cod < airport.cod;
}
