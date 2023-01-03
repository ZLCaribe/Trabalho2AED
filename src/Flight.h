#ifndef TRABALHO2AED_FLIGHT_H
#define TRABALHO2AED_FLIGHT_H

#include <string>

using namespace std;

class Flight {
    string target;
    string airline;
public:
    Flight(string target, string  airline);

    const string &getTarget() const;

    const string &getAirline() const;
};

#endif //TRABALHO2AED_FLIGHT_H
