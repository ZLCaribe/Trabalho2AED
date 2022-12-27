#include "Airline.h"

#include <utility>

Airline::Airline(string code, string name, string callsign, string country) :
code(std::move(code)), name(std::move(name)), callsign(std::move(callsign)), country(std::move(country)) {}
