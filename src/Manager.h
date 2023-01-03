#ifndef TRABALHO2AED_MANAGER_H
#define TRABALHO2AED_MANAGER_H

#include <iostream>
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
};

#endif //TRABALHO2AED_MANAGER_H