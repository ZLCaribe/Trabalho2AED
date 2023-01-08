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
    AirportMap airports;
    AirlineMap airlines;
    CityMap cities;
public:
    Manager();

    void readAirlines();
    void readAirports();
    void readFlights();
    void readFiles();

    list<Airport> inputLocal(const string& s);
    City inputCidade();
    Airport inputAirport();
    static int inputInt(const string& message);

    void mainMenu();
    void menuPlanejamentoViagem();
    void menuEstatisticas(Airport airport);

    void bfsDist(const Airport& airport);
    list<list<Airport>> find_paths(Airport a,Airport end, list<Airport> path, int max);
    list<list<Airport>> getRoutes(Airport start, Airport end, int max);
    list<Airport> getAirportsFromCity(const string& name, const string& country);
    list<Airport> getAirportsFromCoordinates(double latitude, double longitude, double distance);

    AirportTable getDestFromAirportFlights(Airport& airport,int maxFlights);
    size_t numberOfAirportsWithMaxNFlights(Airport& airport, int maxflights);
    size_t numberOfCitiesWithMaxNFlights(Airport& airport,int maxflights);
    size_t numberOfCountriesWithMaxNFlights(Airport& airport,int maxflights);

    list<list<Airport>> getBetterRoute(Airport& airport1, const list<Airport>& airportsDest);
};

#endif //TRABALHO2AED_MANAGER_H