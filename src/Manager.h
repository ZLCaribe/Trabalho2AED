#ifndef TRABALHO2AED_MANAGER_H
#define TRABALHO2AED_MANAGER_H

#include <iostream>
#include <cmath>
#include "Airline.h"
#include "Airport.h"
#include "City.h"

using namespace std;

class Manager {
private:
    AirportTable airports;
    AirlineTable airlines;
    CityTable cities;
public:
    Manager();

    void readAirlines();
    void readAirports();
    void readFlights();
    void readFiles();

    void mainMenu();
    void menuMelhorCaso();

    void bfsDist(Airport airport);
    void dfs(list<list<Airport>>& result, list<Airport>& path, Airport airport1, int max);
    list<Airport> getAirportsFromCity(const string& name, const string& country);
    list<Airport> getAirportsFromCoordinates(double latitude, double longitude, double distance);

    AirportTable getDestFromAirportFlights(Airport& airport,int maxFlights) const;
    size_t numberOfAirportsWithMaxNFlights(Airport& airport, int maxflights) const;
    size_t numberOfCitiesWithMaxNFlights(Airport& airport,int maxflights) const;
    size_t numberOfCountriesWithMaxNFlights(Airport& airport,int maxflights) const;

    list<list<Airport>> getBetterRoute(Airport& airport1, const list<Airport>& airportsDest);
};

#endif //TRABALHO2AED_MANAGER_H