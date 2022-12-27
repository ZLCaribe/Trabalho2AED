#ifndef TRABALHO2AED_AIRLINE_H
#define TRABALHO2AED_AIRLINE_H

#include <string>

using namespace std;

class Airline {
private:
    string code;
    string name;
    string callsign;
    string country;
public:
    Airline(string code, string name, string callsign, string country);
};

#endif //TRABALHO2AED_AIRLINE_H
