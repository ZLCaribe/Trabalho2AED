#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "Manager.h"

using namespace std;

Manager::Manager() = default;

void Manager::mainMenu() {
    int i = 0;
    while(i != 4){
        cout << "------------MENU PRINCIPAL----------" << endl;
        cout << "Selecione a opcao: \n";
        //TODO MENU
        cin >> i;
    }
}

vector<string> explode(const string& s, const char& c){
    vector<string> v;
    string buff;
    stringstream ss(s);
    while (std::getline(ss, buff, ',')) {
        v.push_back(buff);
    }
    return v;
}

void Manager::readAirlines() {
    ifstream in("../resources/airlines.csv");
    string line;
    getline(in,line);
    while(getline(in,line)){
        vector<string> v = explode(line, ',');
        Airline airline(v[0],v[1],v[2],v[3]);
        if(this->airlines.find(airline) == this->airlines.end())
            this->airlines.insert(airline);
    }
}

void Manager::readAirports() {
    ifstream in("../resources/airports.csv");
    string line;
    getline(in,line);
    while(getline(in,line)){
        vector<string> v = explode(line,',');
        Airport airport(v[0],v[1],v[2],v[3],stod(v[4]), stod(v[5]));
        City city(v[2],v[3]);
        if(this->airports.find(airport) == this->airports.end())
            this->airports.insert(airport);
        auto city2 = this->cities.find(city);
        if(city2 != this->cities.end()) {
            auto &city3 = const_cast<City &>(*city2);
            city3.addAirport(&airport);
        }else{
            city.addAirport(&airport);
            this->cities.insert(city);
        }
    }
}

void Manager::readFlights() {
    ifstream in("../resources/flights.csv");
    string line;
    getline(in,line);
    while(getline(in,line)){
        vector<string> v = explode(line, ',');
        Flight flight(v[1],v[2]);
        Airport tempAirport(v[0]);
        auto i = this->airports.find(tempAirport);
        if(i != this->airports.end()){
            auto &airport = const_cast<Airport &>(*i);
            airport.addFlight(flight);
        }
    }
}

void Manager::readFiles() {
    this->readAirlines();
    this->readAirports();
    this->readFlights();
}
