#ifndef TRABALHO2AED_MANAGER_H
#define TRABALHO2AED_MANAGER_H


#include <unordered_set>
#include "Airline.h"
#include "Airport.h"

using namespace std;

class Manager {
private://Fazer hash Functions
    unordered_set<Airport> airports;
    unordered_set<Airline> airlines;
public:
    Manager();
    void readFiles();
    void mainMenu();
};


#endif //TRABALHO2AED_MANAGER_H