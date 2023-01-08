#include "Manager.h"

using namespace std;

Manager::Manager() = default;

/**
 * Pede ao utilizador o local de partida e local de chegada da viagem que ele pretende fazer e imprime na consola os voos
 * necessarios para ir de um local a outro da forma mais eficiente
 * <br>COMPLEXIDADE: TODO complexidade de getBetterRoute() + O(R*r)
 */
void Manager::menuPlanejamentoViagem(){
    auto paritda = this->inputLocal("Partida");
    auto chegada = this->inputLocal("Chegada");
    list<list<Airport>> routes;
    routes = getBetterRoute(*paritda.begin(), chegada);
    cout << "As possíveis para fazer a viagem sao: " << endl;
    for(auto route : routes){
        cout << "------------------------------------------" << endl;
        for(auto a = route.begin();a != route.end();){
            cout << a->getCod() + " -> ";
            a++;
            cout << a->getCod() << endl;
        }
    }
    cout << "------------------------------------------" <<endl;
}

/**
 * Menu principal onde o utilizador pode escolher se quer ver um caminho de um local a outro ou ver estatísticas de um
 * aeroporto
 */
void Manager::mainMenu() {
    int i = 0;
    while(i != 3){
        cout << "------------MENU PRINCIPAL----------" << endl;
        cout << "1: Ver melhor caminho\n";
        cout << "2: Ver estatisticas de um aeroporto\n";
        cout << "3: Sair\n";
        cout << "Selecione a opcao: ";
        cin >> i;
        switch (i) {
            case 1:
                menuPlanejamentoViagem();
                break;
            case 2:
                menuEstatisticas(inputAirport());
                break;
            case 3:
                cout << "A sair..." << endl;
                break;
            default:
                cout << "Selecione uma opcao valida!" << endl;
                break;
        }
    }
}

/**
 * organiza uma string que tenha delimitadores em um vetor de strings sem os delimitadores
 * <br>COMPLEXIDADE: O(d)
 * @param s string original com os delimitadores
 * @param c delimitador
 * @return vetor de strings organizado
 */
vector<string> explode(const string& s, const char& c){
    vector<string> v;
    string buff;
    stringstream ss(s);
    while (std::getline(ss, buff, ',')) {
        v.push_back(buff);
    }
    return v;
}

/**
 * lê o ficheiro airlines.csv e guarda a informação dentro da variável airlines
 * <br>COMPLEXIDADE: O(l*d)
 */
void Manager::readAirlines() {
    ifstream in("../resources/airlines.csv");
    string line;
    getline(in,line);
    while(getline(in,line)){
        vector<string> v = explode(line, ',');
        Airline airline(v[0],v[1],v[2],v[3]);
        this->airlines.insert({v[0], airline});
    }
}

/**
 * lê o ficheiro airports.csv e guarda a informação dentro das variáveis airports e cities
 * <br>COMPLEXIDADE: O(l*d)
 */
void Manager::readAirports() {
    ifstream in("../resources/airports.csv");
    string line;
    getline(in,line);
    while(getline(in,line)){
        vector<string> v = explode(line,',');
        Airport airport(v[0],v[1],v[2],v[3],stod(v[4]), stod(v[5]));
        City city(v[2],v[3]);
        this->airports.insert({v[0], airport});
        auto city2 = this->cities.find(v[0] + v[1]);
        if(city2 != this->cities.end()) {
            city2->second.addAirport(airport);
        }else{
            city.addAirport(airport);
            this->cities.insert({v[0] + v[1], city});
        }
    }
}

/**
 * lê o ficheiro flights.csv e guarda a informação dentro dos respetivos aeroportos dos quais os voos partem
 * <br>COMPLEXIDADE: O(l*d)
 */
void Manager::readFlights() {
    ifstream in("../resources/flights.csv");
    string line;
    getline(in,line);
    while(getline(in,line)){
        vector<string> v = explode(line, ',');
        Flight flight(v[1],v[2]);
        auto i = this->airports.find(v[0]);
        if(i != this->airports.end()){
            i->second.addFlight(flight);
        }
    }
}

/**
 * lê os ficheiros com a informação das companhias aereas, aeroportos e voos
 */
void Manager::readFiles() {
    this->readAirlines();
    this->readAirports();
    this->readFlights();
}

/**
 * computa a distância em número de voos partindo do aeroporto passado como argumento
 * <br>COMPLEXIDADE: O(a + f)
 * @param airport aeroporto inicial
 */
void Manager::bfsDist(const Airport& airport) {
    for(auto &a : this->airports) a.second.resetVisited();
    this->airports[airport.getCod()].setDistance(0);
    this->airports[airport.getCod()].setVisited();
    queue<Airport> q;
    q.push(airport);
    while(!q.empty()){
        Airport u = q.front(); q.pop();
        list<Flight> flights = u.getFlights();
        for(const auto& f : flights){
            auto w = this->airports.find(f.getTarget());
            if(w != this->airports.end()) {
                if (!w->second.isVisited()) {
                    q.push(w->second);
                    w->second.setDistance(u.getDistance() + 1);
                    w->second.setVisited();
                }
            }
        }
    }
}

/**
 * TODO
 * @param result
 * @param path
 * @param airport1
 * @param max
 */
void Manager::dfs(list<list<Airport>>& result, list<Airport>& path, const Airport& airport1, int max){
    path.push_back(airport1);
    if(path.size() == max +1) result.push_back(path);
    else{
        for(const auto& a: airport1.getFlights()){
            auto w = this->airports.find(a.getTarget());
            dfs(result,path,w->second,max);
        }
    }
    path.pop_back();
}

/**
 * Calcula a distância em quilometros entre duas coordenadas
 * @param lat1 latitude da primeira coordenada
 * @param lon1 longitude da primeira coordenada
 * @param lat2 latitude da segunda coordenada
 * @param lon2 longitude da segunda coordenada
 * @return distância em quilometros entre as duas coordenadas
 */
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

/**
 * Procura todos os aeroportos que estão até uma distância máxima de uma dada coordenada
 * <br>COMPLEXIDADE: O(a)
 * @param latitude latitude da coordenada
 * @param longitude longitude da coordenada
 * @param distance distância máxima
 * @return lista com os aeroportos a uma distância máxima de uma dada coordanada
 */
list<Airport> Manager::getAirportsFromCoordinates(double latitude, double longitude, double distance) {
    list<Airport> res;
    for(const auto& a : this->airports)
        if(haversine(a.second.getLatitude(), a.second.getLongitude(), latitude, longitude) <= distance)
            res.push_back(a.second);
    return res;
}

/**
 * Procura todos os aeroportos atingiveis partindo de um dado aeroporto e utilizando um dado número de máximo de voos
 * <br>COMPLEXIDADE: O(a + f)
 * @param airport aeroporto inicial
 * @param maxFlights número máximo de voos
 * @return aeroportos atingiveis
 */
AirportTable Manager::getDestFromAirportFlights(Airport& airport, int maxFlights){
    AirportTable possibleDestinations;
    for(auto &a : this->airports) a.second.resetVisited();
    queue<Airport> q;
    q.push(airport);
    this->airports[airport.getCod()].setVisited();
    this->airports[airport.getCod()].setDistance(0);
    while(!q.empty()){
        Airport u = q.front(); q.pop();
        for(const auto& f : u.getFlights()){
            Airport *w = &this->airports[f.getTarget()];
            if(!w->isVisited()){
                w->setDistance(u.getDistance() + 1);
                w->setVisited();
                if(w->getDistance() <= maxFlights) {
                    q.push(*w);
                    possibleDestinations.insert(*w);
                }
            }
        }
    }
    return possibleDestinations;
}

/**
 * Calcula o número aeroportos atingiveis partindo de um dado aeroporto e utilizando um dado número de máximo de voos
 * <br>COMPLEXIDADE: O(a + f)
 * @param airport aeroporto inicial
 * @param maxFlights número máximo de voos
 * @return número de aeroportos atingiveis
 */
size_t Manager::numberOfAirportsWithMaxNFlights(Airport &airport, int maxflights) {
    return this->getDestFromAirportFlights(airport,maxflights).size();
}

/**
 * Calcula o número cidades atingiveis partindo de um dado aeroporto e utilizando um dado número de máximo de voos
 * <br>COMPLEXIDADE: O(a + f)
 * @param airport aeroporto inicial
 * @param maxFlights número máximo de voos
 * @return número de cidades atingiveis
 */
size_t Manager::numberOfCitiesWithMaxNFlights(Airport &airport, int maxflights) {
    auto s = this->getDestFromAirportFlights(airport,maxflights);
    unordered_set<string> res;
    for(const auto& a : s)
        res.insert(a.getCity());
    return res.size();
}

/**
 * Calcula o número países atingiveis partindo de um dado aeroporto e utilizando um dado número de máximo de voos
 * <br>COMPLEXIDADE: O(a + f)
 * @param airport aeroporto inicial
 * @param maxFlights número máximo de voos
 * @return número de aeroportos atingiveis
 */
size_t Manager::numberOfCountriesWithMaxNFlights(Airport &airport, int maxflights) {
    auto s = this->getDestFromAirportFlights(airport,maxflights);
    unordered_set<string> res;
    for(const auto& a : s)
        res.insert(a.getCountry());
    return res.size();
}

/**
 * TODO
 * @param airport1
 * @param airportsDest
 * @return
 */
list<list<Airport>> Manager::getBetterRoute(Airport& airport1, const list<Airport>& airportsDest){
    bfsDist(airport1);
    int min = airportsDest.begin()->getDistance();
    Airport dest;
    list<list<Airport>> result;
    list<Airport> path;
    for(const auto& b: airportsDest) {
        Airport a = this->airports.find(b.getCod())->second;
        if(a.isVisited() && a.getDistance() < min) min = a.getDistance();
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
    return result;
}

/**
 * @return retorna o aeroporto com o código que o utilizador inserir
 */
Airport Manager::inputAirport() {
    string cod;
    while(true) {
        cout << "Insira o codigo do aeroporto que deseja: ";
        cin >> cod;
        if (this->airports.find(cod) == this->airports.end())
            cout << "Codigo nao existe, tente novamente" << endl;
        else break;
    }
    return this->airports[cod];
}

/**
 * @return retorna a cidade com o nome que e que faz parte do país que utilizador inserir
 */
City Manager::inputCidade() {
    string name,country;
    while(true) {
        cout << "Insira o nome da cidade que deseja: ";
        cin >> name;
        cout << "Insira o pais da cidade que deseja: ";
        cin >> country;
        if (this->cities.find(name + country) == this->cities.end())
            cout << "Cidade nao existe, tente novamente" << endl;
        else break;
    }
    return this->cities.at(name + country);
}

/**
 * @param s determina se o local é de partida ou chegada
 * @return lista de aeroportos no local selecionado pelo utilizador
 */
list<Airport> Manager::inputLocal(const string& s) {
    int i = 4;
    list<Airport> a;
    while(i > 3){
        cout << "Qual seu local de " + s << endl;
        cout << "1: Uma cidade\n";
        cout << "2: Uma coordenada\n";
        cout << "3: Um aeroporto\n";
        cout << "Selecione a opcao: ";
        cin >> i;
        switch (i) {
            case 1:
                return this->inputCidade().getAirports();
            case 2:
                double lat,longi,distance;
                cout << "Insira uma latidude: ";
                cin >> lat;
                cout << "Insira uma longitude: ";
                cin >> longi;
                cout << "Insira uma distancia maxima: ";
                cin >> distance;
                return this->getAirportsFromCoordinates(lat,longi,distance);
            case 3:
                a.push_back(inputAirport());
                break;
            default:
                cout << "Selecione uma opcao valida!" << endl;
                break;
        }
    }
    return a;
}

/**
 * Menu onde o utilizador pode escolher que estatística ele quer ver de sobre os voos de um aeroporto
 * @param airport aeroporto de onde serão tiradas as estatísticas
 */
void Manager::menuEstatisticas(Airport airport) {
    int i = 0,x;
    while(i != 7){
        cout << "------------MENU ESTATISTICAS----------" << endl;
        cout << "O que deseja saber sobre os voos que partem de " + airport.getCod() +"?" << endl;
        cout << "1: Numero de voos\n";
        cout << "2: Numero de companhias aereas\n";
        cout << "3: Aeroportos que recebem voos deste aeroporto\n";
        cout << "4: Quantos aeroportos diferentes sao atingiveis usando um maximo de x voos\n";
        cout << "5: Quantas cidades diferentes sao atingiveis usando um maximo de x voos\n";
        cout << "6: Quantos paises diferentes sao atingiveis usando um maximo de x voos\n";
        cout << "7: voltar\n";
        cout << "Selecione a opcao: ";
        cin >> i;
        switch (i) {
            case 1:
                cout << "O numero de voos que partem de " + airport.getCod() + " sao: ";
                cout << airport.getNFlights() << endl;
                break;
            case 2:
                cout << "O numero de companhias aereas que partem de " + airport.getCod() + " sao: ";
                cout << airport.getNAirlines() << endl;
                break;
            case 3:
                cout << "O numero de aeroportos diferentes atingiveis partindo de " + airport.getCod() + " sao: ";
                cout << airport.getNDestinations() << endl;
                break;
            case 4:
                x = inputInt("Insira o numero maximo de voos: ");
                cout << "O numero de aeroportos atingiveis usando um maximo de " + to_string(x) +" voos\npartindo de " + airport.getCod() + " sao: ";
                cout << this->numberOfAirportsWithMaxNFlights(airport,x) << endl;
                break;
            case 5:
                x = inputInt("Insira o numero maximo de voos: ");
                cout << "O numero de cidades atingiveis usando um maximo de " + to_string(x) +" voos\npartindode " + airport.getCod() + " sao: ";
                cout << this->numberOfCitiesWithMaxNFlights(airport,x) << endl;
                break;
            case 6:
                x = inputInt("Insira o numero maximo de voos: ");
                cout << "O numero de paises atingiveis usando um maximo de " + to_string(x) +" voos\npartindo de " + airport.getCod() + " sao: ";
                cout << this->numberOfCountriesWithMaxNFlights(airport,x) << endl;
                break;
            case 7:
                cout << "A voltar..." << endl;
                break;
            default:
                cout << "Selecione uma opcao valida!" << endl;
                break;
        }
    }
}

/**
 * imprime uma mensagem na consola e retorna um número inteiro lido da consola
 * @param message mensagem que vai ser mostrada
 * @return número inteiro
 */
int Manager::inputInt(const string& message) {
    cout << message;
    int x;
    cin >> x;
    return x;
}
