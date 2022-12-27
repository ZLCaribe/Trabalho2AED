#include "Flight.h"

#include <utility>

Flight::Flight(string source, string target, string airline) :
    source(std::move(source)), target(std::move(target)),airline(std::move(airline)) {}
