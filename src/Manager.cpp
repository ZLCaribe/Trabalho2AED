#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <queue>
#include "Manager.h"

using namespace std;

Manager::Manager() = default;

void Manager::menuMelhorCaso(){
    int i = 0;
    while(i != 4){
        cout << "------------MENU Melhor caminho----------" << endl;
        cout << "1: Partir de uma cidade\n";
        cout << "2: Partir de uma coordenada\n";
        cout << "3: Partir de um aeroporto\n";
        cout << "Selecione a opcao: \n";
        //TODO MENU
        cin >> i;
        switch (i) {
            case 1:

            case 2:

            case 3:

            case 4:

            case 5:
                cout << "A voltar..." << endl;
                break;
            default:
                cout << "Selecione uma opcao valida!" << endl;
                break;
        }
    }
}

void Manager::mainMenu() {
    int i = 0;
    while(i != 4){
        cout << "------------MENU PRINCIPAL----------" << endl;
        cout << "1: Ver melhor caminho\n";
        cout << "2: Ver informacoes sobre voos de um dado aeroporto\n";
        cout << "3: Ver estatisticas de um aeroporto\n";
        cout << "Selecione a opcao: \n";
        //TODO MENU
        cin >> i;
        switch (i) {
            case 1:
                menuMelhorCaso()
            case 2:
                this->novoPedido(ADICIONAR);
                break;
            case 3:
                this->novoPedido(ALTERAR);
                break;
            case 4:
                this->novoPedidoConj();
                break;
            case 5:
                cout << "A voltar..." << endl;
                break;
            default:
                cout << "Selecione uma opcao valida!" << endl;
                break;
        }
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

void Manager::bfsDist(Airport airport) {
    for(Airport a : this->airports) a.resetVisited();
    airport.setDistance(0);
    queue<Airport> q;
    q.push(airport);
    airport.setVisited();
    while(!q.empty()){
        Airport u = q.front(); q.pop();
        for(const auto& f : u.getFlights()){
            auto w = this->airports.find(Airport(f.getTarget()));
            if(!w->isVisited()){
                Airport l = const_cast<Airport &>(*w);
                q.push(l);
                l.setDistance(u.getDistance() + 1);
                l.setVisited();

            }
        }
    }

}

void Manager::dfs(list<list<Airport>>& result, list<Airport>& path, Airport airport1, int max){
    path.push_back(airport1);
    if(path.size() == max +1) result.push_back(path);
    else{
        for(auto a: airport1.getFlights()){
            auto w = this->airports.find(Airport(a.getTarget()));
            Airport l = const_cast<Airport &>(*w);
            dfs(result,path,l,max);
        }
    }
    path.pop_back();

}

list<Airport> Manager::getAirportsFromCity(const string& name, const string& country) {
    City city(name, country);
    auto i = this->cities.find(city);
    if(i == this->cities.end())
        return {};
    city = *i;
    return (const list<Airport> &) city.getAirports();
}

double haversine(double lat1, double lon1, double lat2, double lon2){
    double dLat = (lat2 - lat1) * M_PI / 180.0;
    double dLon = (lon2 - lon1) * M_PI / 180.0;

    lat1 = (lat1) * M_PI / 180.0;
    lat2 = (lat2) * M_PI / 180.0;

    double a = pow(sin(dLat / 2), 2) + pow(sin(dLon / 2), 2) * cos(lat1) * cos(lat2);
    double rad = 6371;
    double c = 2 * asin(sqrt(a));
    return rad * c;
}

list<Airport> Manager::getAirportsFromCoordinates(double latitude, double longitude, double distance) {
    list<Airport> res;
    for(const auto& a : this->airports)
        if(haversine(a.getLatitude(), a.getLongitude(), latitude, longitude) <= distance)
            res.push_back(a);
    return res;
}

/**
 * calculate the maximum of airports that someone can get leaving from airport and using a maximum number of flights
 * @param airport starting point
 * @param maxFlights maximum number of flights
 * @return the possible destinations
 */
AirportTable Manager::getDestFromAirportFlights(Airport& airport, int maxFlights) const{//TODO N FOI TESTADO
    AirportTable possibleDestinations;
    for(Airport a : this->airports) a.resetVisited();
    queue<Airport> q;
    q.push(airport);
    auto i = this->airports.find(airport);
    auto airport1 = const_cast<Airport &>(*i);
    airport1.setVisited();
    airport1.setDistance(0);
    while(!q.empty()){
        Airport u = q.front(); q.pop();
        for(const auto& f : u.getFlights()){
            i = this->airports.find(Airport(f.getTarget()));
            if(!i->isVisited()){
                Airport w = const_cast<Airport &>(*i);
                w.setDistance(w.getDistance() + 1);
                w.setVisited();
                possibleDestinations.insert(w);
                if(w.getDistance() <= maxFlights)
                    q.push(w);
            }
        }
    }
    return possibleDestinations;
}

size_t Manager::numberOfAirportsWithMaxNFlights(Airport &airport, int maxflights) const {
    return this->getDestFromAirportFlights(airport,maxflights).size();
}

size_t Manager::numberOfCitiesWithMaxNFlights(Airport &airport, int maxflights) const {
    auto s = this->getDestFromAirportFlights(airport,maxflights);
    unordered_set<string> res;
    for(const auto& a : s)
        res.insert(a.getCity());
    return res.size();
}

size_t Manager::numberOfCountriesWithMaxNFlights(Airport &airport, int maxflights) const {
    auto s = this->getDestFromAirportFlights(airport,maxflights);
    unordered_set<string> res;
    for(const auto& a : s)
        res.insert(a.getCountry());
    return res.size();
}

list<list<Airport>> Manager::getBetterRoute(Airport& airport1, const list<Airport>& airportsDest){
    bfsDist(airport1);
    int min = INT_MAX;
    Airport dest;
    list<list<Airport>> result;
    list<Airport> path;
    for(const Airport& a : this->airports){
        for(const auto& b: airportsDest) {
            if(a.getCod() == b.getCod()){
                if(a.getDistance() < min){
                    min = a.getDistance();
                    dest = b;
                }

            }
        }
    }
    dfs(result,path,airport1,min);
    auto it = result.begin();
    while(it != result.end()){
        bool flag = false;
        for(const auto& ad: airportsDest){
            if(it->front().getCod() == ad.getCod()) flag = true;
        }
        if(!flag){
            it = result.erase(it);
        }
        else it++;
    }
    
}
