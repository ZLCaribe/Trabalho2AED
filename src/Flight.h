#ifndef TRABALHO2AED_FLIGHT_H
#define TRABALHO2AED_FLIGHT_H

#include <string>

using namespace std;

class Flight {
    string source;
    string target;
    string airline;
public:
    Flight(string source, string target, string airline);
};


#endif //TRABALHO2AED_FLIGHT_H
