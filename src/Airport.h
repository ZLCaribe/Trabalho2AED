#ifndef TRABALHO2AED_AIRPORT_H
#define TRABALHO2AED_AIRPORT_H

#include <hash_map>
#include <hash_set>
#include <unordered_set>
#include "Flight.h"

using namespace std;

class Airport {
private:
    string cod;
    string name;
    string city;
    string country;
    double longitude;
    double latitude;
    unordered_set<Flight> flights;//Fazer Hash function
public:
    Airport(string cod, string name, string city, string country, double longitude,double latitude);
};

#endif //TRABALHO2AED_AIRPORT_H
