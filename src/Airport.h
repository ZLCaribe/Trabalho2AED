#ifndef TRABALHO2AED_AIRPORT_H
#define TRABALHO2AED_AIRPORT_H

#include <list>
#include <unordered_set>
#include "Flight.h"

using namespace std;

class Airport {
private:
    string cod;
    string name;
    string city;
    string country;
    long double longitude{};
    long double latitude{};
    vector<Flight> flights;
public:
    Airport(string cod, string name, string  city, string country, double longitude, double latitude);

    explicit Airport(string cod);

    const string &getCod() const;

    const string &getName() const;

    const string &getCity() const;

    const string &getCountry() const;

    double getLongitude() const;

    double getLatitude() const;

    void addFlight(const Flight& flight);
};

struct eqAirport {
    bool operator() (const Airport& airport1, const Airport& airport2) const{
        return airport1.getCod() == airport2.getCod();
    }
};

struct hAirport {
    size_t operator() (const Airport& airport) const{
        int v = 0;
        for(char i : airport.getCod())
            v = 37*v + i;
        return v;
    }
};

typedef unordered_set<Airport,hAirport,eqAirport> AirportTable;

#endif //TRABALHO2AED_AIRPORT_H
