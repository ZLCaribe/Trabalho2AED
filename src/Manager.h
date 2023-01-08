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

    list<Airport> inputLocal(const string& s);
    City inputCidade();
    Airport inputAirport();

    void mainMenu();
    void menuMelhorCaso();

    void bfsDist(const Airport& airport);
    void dfs(list<list<Airport>>& result, list<Airport>& path, const Airport& airport1, int max);
    list<Airport> getAirportsFromCity(const string& name, const string& country);
    list<Airport> getAirportsFromCoordinates(double latitude, double longitude, double distance);

    AirportTable getDestFromAirportFlights(Airport& airport,int maxFlights);
    size_t numberOfAirportsWithMaxNFlights(Airport& airport, int maxflights);
    size_t numberOfCitiesWithMaxNFlights(Airport& airport,int maxflights);
    size_t numberOfCountriesWithMaxNFlights(Airport& airport,int maxflights);

    list<list<Airport>> getBetterRoute(Airport& airport1, const list<Airport>& airportsDest);

    void setAirportVisited(const string& cod);
    void setAirportDistance(const string& cod,int distance);
    void resetAirport(const string& cod);
};

#endif //TRABALHO2AED_MANAGER_H