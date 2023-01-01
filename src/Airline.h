#ifndef TRABALHO2AED_AIRLINE_H
#define TRABALHO2AED_AIRLINE_H

#include <string>
#include <unordered_set>

using namespace std;

class Airline {
private:
    string code;
    string name;
    string callsign;
    string country;
public:
    Airline(string code, string name, string callsign, string country);

    const string &getCode() const;

    const string &getName() const;

    const string &getCallsign() const;

    const string &getCountry() const;
};

struct eqAirline {
    bool operator() (const Airline& airline1, const Airline& airline2) const{
        return airline1.getCode() == airline2.getCode();
    }
};

struct hAirline {
    size_t operator() (const Airline & airline) const{
        int v = 0;
        for(auto i : airline.getCode())
            v = 37*v + i;
        return v;
    }
};

typedef unordered_set<Airline,hAirline,eqAirline> AirlineTable;

#endif //TRABALHO2AED_AIRLINE_H
