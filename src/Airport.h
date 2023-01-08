#ifndef TRABALHO2AED_AIRPORT_H
#define TRABALHO2AED_AIRPORT_H

#include <list>
#include <unordered_set>
#include <unordered_map>
#include "Flight.h"

using namespace std;

class Airport {
private:
    string cod;
    string name;
    string city;
    string country;
    double longitude{};
    double latitude{};
    list<Flight> flights;

    bool visited = false;
    int distance = 0;
public:
    Airport(string cod, string name, string  city, string country, double longitude, double latitude);

    Airport();

    explicit Airport(string cod);

    const string &getCod() const;

    const string &getName() const;

    const string &getCity() const;

    const string &getCountry() const;

    double getLongitude() const;

    double getLatitude() const;

    list<Flight> getFlights() const;

    bool isVisited() const;

    void setVisited();

    int getDistance() const;

    void setDistance(int newDistance);

    void addFlight(const Flight& flight);

    list<Flight> getFlightsTo(const string& airpoirt);

    size_t getNFlights();

    size_t getNAirlines();

    size_t getNDestinations();

    void resetVisited();

    void setVisitedF();

    bool operator<(const Airport& airport) const;
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
typedef unordered_map<string,Airport> AirportMap;

#endif //TRABALHO2AED_AIRPORT_H
