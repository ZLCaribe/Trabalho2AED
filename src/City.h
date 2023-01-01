#ifndef TRABALHO2AED_CITY_H
#define TRABALHO2AED_CITY_H


#include <unordered_set>
#include "Airport.h"

class City {
private:
    string name;
    string country;
    vector<Airport *> airports;
public:
    City(string name, string country);

    const string &getName() const;

    const string &getCountry() const;

    const vector<Airport *> &getAirports() const;

    void addAirport(Airport * airport);
};

struct eqCity {
    bool operator() (const City& city1, const City& city2) const{
        return city1.getName() == city2.getName() && city1.getCountry() == city2.getCountry();
    }
};

struct hCity {
    size_t operator() (const City& city) const{
        int v = 0;
        string combined = city.getName() + city.getCountry();
        for(char i : combined)
            v = 37*v + i;
        return v;
    }
};

typedef unordered_set<City,hCity,eqCity> CityTable;

#endif //TRABALHO2AED_CITY_H
