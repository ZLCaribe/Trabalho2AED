#ifndef TRABALHO2AED_MANAGER_H
#define TRABALHO2AED_MANAGER_H

#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
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

    //Metódos para ler informação dos ficheiros
    void readAirlines();
    void readAirports();
    void readFlights();
    void readFiles();

    //Metódos para fazer input de algo pela consola
    list<Airport> inputLocal(const string& s);
    City inputCidade();
    Airport inputAirport();
    static int inputInt(const string& message);

    //Metódos que mostram menus
    void mainMenu();
    void menuPlanejamentoViagem();
    void menuEstatisticas(Airport airport);

    //Metódos para percorrer grafo(aeroportos)
    void bfsDist(const Airport& airport);

    list<list<Airport>> find_paths(Airport a,Airport end, list<Airport> path, int max);
    list<list<Airport>> getRoutes(Airport start, Airport end, int max);
    list<Airport> getAirportsFromCity(const string& name, const string& country);
    list<Airport> getAirportsFromCoordinates(double latitude, double longitude, double distance);
    void dfs(list<list<Airport>>& result, list<Airport>& path, const Airport& airport1, int max);
    list<list<Airport>> getBetterRoute(Airport& airport1, const list<Airport>& airportsDest);

    //Metódos estatísticos
    list<Airport> getAirportsFromCoordinates(double latitude, double longitude, double distance);
    AirportTable getDestFromAirportFlights(Airport& airport,int maxFlights);
    size_t numberOfAirportsWithMaxNFlights(Airport& airport, int maxflights);
    size_t numberOfCitiesWithMaxNFlights(Airport& airport,int maxflights);
    size_t numberOfCountriesWithMaxNFlights(Airport& airport,int maxflights);
};

#endif //TRABALHO2AED_MANAGER_H