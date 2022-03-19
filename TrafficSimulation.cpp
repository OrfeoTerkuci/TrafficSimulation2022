// custom libs
#include "TrafficSimulation.h"
#include "Road.h"
#include "TrafficLight.h"
#include "Vehicle.h"
#include "VehicleGenerator.h"
#include "Standard_Values.h"
#include "DesignByContract.h"

// c++ libs
#include <stdexcept>

//==== Parsing FUnctions ====//
bool TrafficSimulation::parseRoad(TiXmlElement* &root){
    REQUIRE(this->properlyInitialized(), "TrafficSimulation was not initialized when calling parseRoad");
    // create road object
    Road *newRoad = new Road();

    // temp values
    string tempn;
    unsigned int tempi;

    // Parsing
    for(TiXmlElement* elem = root->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement()) {
        string elemName = elem->Value();
        if(elemName == NAAM){
            tempn = elem->GetText();
            if(tempn.empty()){
                delete newRoad;
                return false;
            }
            else{
                newRoad->setRoadName(tempn);
            }
        }
        else if(elemName == LENGTE){
            tempi = atoi(elem->GetText());
            if(tempi == 0){
                delete newRoad;
                return false;
            }
            else{
                newRoad->setLength(tempi);
            }
        }
    }

    // Check if road already exists + add road
    if(newRoad->getLength() > 0 and !newRoad->getRoadName().empty()){
        if(!this->addRoad(newRoad)){
            delete newRoad;
            return false;
        }
        else{
            return true;
        }
    }
    return false;
}

bool TrafficSimulation::parseTrafficLight(TiXmlElement* &root){
    REQUIRE(this->properlyInitialized(), "TrafficSimulation was not initialized when calling parseTrafficLight");
    // Create object
    TrafficLight* trafficLight = new TrafficLight();

    // Create temp values
    string tempn;
    unsigned int tempi;

    // Parsing
    for(TiXmlElement* elem = root->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement()) {
        string elemName = elem->Value();
        tempn = elem->GetText();

        // if elem is empty, end parsing and return false
        if(tempn.empty()){
            delete trafficLight;
            return false;
        }

        if(elemName == BAANL){
            for (unsigned int i = 0; i < this->roads.size(); ++i) {
                if (tempn == this->roads[i]->getRoadName()) {
                    trafficLight->setRoad(this->roads[i]);
                    break;
                }
            }
        }
        else if(elemName == POSITIE){
            tempi = atoi(elem->GetText());
            trafficLight->setPosition(tempi);
        }
        else if(elemName == CYCLUS){
            tempi = atoi(elem->GetText());
            trafficLight->setCyclus(tempi);
        }
    }

    // add traffic light to road
    for (unsigned int i = 0; i < this->roads.size(); ++i) {
        if (this->roads[i] == trafficLight->getRoad()){
            this->roads[i]->addLight(trafficLight);
            this->addTrafficLight(trafficLight);
            break;
        }
    }

    return true;
}

bool TrafficSimulation::parseVehicle(TiXmlElement* &root){
    REQUIRE(this->properlyInitialized(), "TrafficSimulation was not initialized when calling parseVehicle");
    Vehicle* vehicle = new Vehicle();

    string tempn;
    unsigned int tempi;

    for(TiXmlElement* elem = root->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement()) {
        string elemName = elem->Value();
        tempn = elem->GetText();

        // if elem is empty, end parsing and return false
        if(tempn.empty()){
            delete vehicle;
            return false;
        }

        if(elemName == BAANL){
            for (unsigned int i = 0; i < this->roads.size(); ++i) {
                if (tempn == this->roads[i]->getRoadName()) {
                    vehicle->setRoad(this->roads[i]);
                    this->roads[i]->addVehicle(vehicle);
                    this->addVehicle(vehicle);
                    break;
                }
            }
        }
        else if(elemName == POSITIE){
            tempi = atoi(elem->GetText());
            vehicle->setPosition(tempi);
        }
    }

    return true;
}

bool TrafficSimulation::parseVehicleGenerator(TiXmlElement *&root) {
    REQUIRE(this->properlyInitialized(), "TrafficSimulation was not initialized when calling parseVehicleGenerator");
    VehicleGenerator* vehicleGenerator = new VehicleGenerator();

    string tempn;
    int tempf;

    for(TiXmlElement* elem = root->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement()) {
        string elemName = elem->Value();
        tempn = elem->GetText();

        if(tempn.empty()){
            delete vehicleGenerator;
            return false;
        }

        if (elemName == BAANL) {
            for (unsigned int i = 0; i < this->roads.size(); ++i) {
                if (tempn == this->roads[i]->getRoadName()) {
                    vehicleGenerator->setRoad(this->roads[i]);
                    if (!this->addVehicleGenerator(vehicleGenerator)){
                        delete vehicleGenerator;
                        return false;
                    }
                    break;
                }
            }
        }
        else if (elemName == FREQUENTIE) {
            tempf = atoi(elem->GetText());
            vehicleGenerator->setFrequentie(tempf);
        }
    }
    return true;
}



//==== Constructors and Destructor ====//
TrafficSimulation::TrafficSimulation(const string &filename) : filename(filename) {
    TiXmlDocument doc;
    _initCheck = this;
    // File readable detection with error message
    try{
        if(!doc.LoadFile(this->filename.c_str())) {
            cerr << doc.ErrorDesc() << endl;
            throw 1;
        }
    }

    catch(int error){
        if(error == 1){
            cout << "File not readable" << endl;
        }
    }

    // Check if file has elements to parse
    TiXmlElement* root = doc.FirstChildElement();

    if(root == NULL) {
        cerr << "Failed to load file: No root element." << endl;
        doc.Clear();
    }

    // Parsing of data
    for(TiXmlElement* elem = root->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement()) {
        string elemName = elem->Value();
        if (elemName == BAANU) {
            if (!this->parseRoad(elem)) {
                cout << "Error: Could not make road" << endl;
            }
        } else if (elemName == VERKEERSLICHT) {
            if (!this->parseTrafficLight(elem)) {
                cout << "Error: Could not make traffic light" << endl;
            }
        } else if (elemName == VOERTUIG) {
            if (!this->parseVehicle(elem)) {
                cout << "Error: Could not make vehicle" << endl;
            }
        } else if (elemName == VOERTUIGGENERATOR) {
            if (!this->parseVehicleGenerator(elem)) {
                cout << "Error: Could not make vehicle generator" << endl;
            }
        }
    }
    ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
}

TrafficSimulation::TrafficSimulation() {_initCheck = this;
    ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");}

bool TrafficSimulation::properlyInitialized() {
    return  _initCheck == this;
}

const vector<VehicleGenerator *> &TrafficSimulation::getVehicleGenerators() {
    REQUIRE(this->properlyInitialized(), "TrafficSimulation was not initialized when calling getVehicleGenerators");
    return vehicleGenerators;
}

const vector<Road *> & TrafficSimulation::getRoads() {
    REQUIRE(this->properlyInitialized(), "TrafficSimulation was not initialized when calling getRoads");
    return roads;
}

void TrafficSimulation::setRoads(const vector<Road *> &newRoads) {
    REQUIRE(this->properlyInitialized(), "TrafficSimulation was not initialized when calling setRoads");
    TrafficSimulation::roads = newRoads;
}

void TrafficSimulation::addTrafficLight(TrafficLight *&newLight) {
    REQUIRE(this->properlyInitialized(), "TrafficSimulation was not initialized when calling addTrafficLight");
    this->lights.push_back(newLight);
}

void TrafficSimulation::addVehicle(Vehicle *&newVehicle) {
    REQUIRE(this->properlyInitialized(), "TrafficSimulation was not initialized when calling addVehicle");
    this->vehicles.push_back(newVehicle);
}

bool TrafficSimulation::addRoad(Road *newRoad) {
    REQUIRE(this->properlyInitialized(), "TrafficSimulation was not initialized when calling addRoad");
    for (unsigned int i = 0; i < this->roads.size(); ++i) {
        if(this->roads[i] == newRoad){
            return false;
        }
    }
    this->roads.push_back(newRoad);
    return true;
}

bool TrafficSimulation::addVehicleGenerator(VehicleGenerator *newVehicleGenerator) {
    REQUIRE(this->properlyInitialized(), "TrafficSimulation was not initialized when calling addVehicleGenerator");
    for (unsigned int i = 0; i < this->vehicleGenerators.size(); ++i) {
        if (this->vehicleGenerators[i]->getRoad() == newVehicleGenerator->getRoad()){
            return false;
        }
    }
    this->vehicleGenerators.push_back(newVehicleGenerator);
    return true;
}

void TrafficSimulation::printAll() {
    REQUIRE(this->properlyInitialized(), "TrafficSimulation was not initialized when calling printAll");
    if (!this->roads.empty()){

        if(this->roads.size() == 1){
            cout <<"Consists of " << this->roads.size() << " road: " << endl;
        }
        else{
            cout <<"Consists of " << this->roads.size() << " roads: " << endl;
        }

        for(unsigned int i = 0; i < this->roads.size(); i++){
            cout << endl << "--------------------";

            cout << endl;

            this->roads[i]->print();

            cout << endl;

            if(this->roads[i]->getTrafficLightsAmount() == 1){
                cout << "Consist of " << this->roads[i]->getTrafficLightsAmount() << " traffic light." << endl;
            }
            else{
                cout << "Consist of " << this->roads[i]->getTrafficLightsAmount() << " traffic lights." << endl;
            }

            cout << endl;

            for (int j = 0; j < this->roads[i]->getTrafficLightsAmount(); ++j) {
                cout << "Traffic light " << j + 1 << ":" << endl;
                this->roads[i]->getTrafficLight(j)->print();
            }

            cout << endl;

            if(this->roads[i]->getVehicleAmount() == 1){
                cout << "Consist of " << this->roads[i]->getVehicleAmount() << " vehicle." << endl;
            }
            else{
                cout << "Consist of " << this->roads[i]->getVehicleAmount() << " vehicles." << endl;
            }

            cout << endl;

            for (int k = 0; k < this->roads[i]->getVehicleAmount(); ++k) {
                cout << "Vehicle " << k + 1 << ":" << endl;
                this->roads[i]->getVehicle(k)->print();
                cout << endl;
            }
        }
    }
    else{
        cout << "There are no roads." << endl;
    }
}

void TrafficSimulation::print( int &count) {
    if (!this->vehicles.empty()){
        cout << "Time: " << count << endl;
        for (long unsigned int i = 0; i < this->vehicles.size(); ++i) {
            cout << "Vehicle " << i << ": " << endl;
            this->vehicles.at(i)->print();
            cout << endl;
        }
    }

}

void TrafficSimulation::startSimulation() {
    REQUIRE(this->properlyInitialized(), "TrafficSimulation was not initialized when calling startSimulation");
    int count = 0;
    double vehiclePosition;
    int roadLength;
    Vehicle* currentVehicle;
    Road* currentRoad;

    cout << "- Starting simulation" << endl;

    while (!this->vehicles.empty()){
        for (unsigned int i = 0; i < this->vehicles.size(); ++i){
            // Get current vehicle
            currentVehicle = this->vehicles.at(i);
            // Get current road
            currentRoad = currentVehicle->getRoad();
            // Simulate vehicle
            currentVehicle->simulate();
            vehiclePosition = currentVehicle->getVehiclePosition();
            roadLength = currentRoad->getLength();
            // Check if vehicle had gone off the road
            if (vehiclePosition > roadLength){
                // Remove the vehicle from the simulation
                currentRoad->removeVehicle(currentVehicle);
                this->vehicles.erase(vehicles.begin() + i);
            }
        }
        for (unsigned int j = 0; j < this->lights.size(); ++j) {
            // Simulate traffic light
            currentRoad = lights.at(j)->getRoad();
            if(currentRoad->getVehicleAmount() > 0){
                this->lights.at(j)->simulate(count);
            }
        }
        print(count);
        count ++;
    }
    cout << "- There are no vehicles on the road network." << endl;
    cout << "- Ending simulation" << endl;

}

void TrafficSimulation::startSimNoPrint() {
    REQUIRE(this->properlyInitialized(), "TrafficSimulation was not initialized when calling startSimNoPrint");
    int count = 0;
    double vehiclePosition;
    int roadLength;
    Vehicle* currentVehicle;
    Road* currentRoad;

    while (!this->vehicles.empty()){
        for (unsigned int i = 0; i < this->vehicles.size(); ++i){
            // Get current vehicle
            currentVehicle = this->vehicles.at(i);
            // Get current road
            currentRoad = currentVehicle->getRoad();
            // Simulate vehicle
            currentVehicle->simulate();
            vehiclePosition = currentVehicle->getVehiclePosition();
            roadLength = currentRoad->getLength();
            // Check if vehicle had gone off the road
            if (vehiclePosition > roadLength){
                // Remove the vehicle from the simulation
                currentRoad->removeVehicle(currentVehicle);
                this->vehicles.erase(vehicles.begin() + i);
            }
        }
        for (unsigned int j = 0; j < this->lights.size(); ++j) {
            // Simulate traffic light
            currentRoad = lights.at(j)->getRoad();
            if(currentRoad->getVehicleAmount() > 0){
                this->lights.at(j)->simulate(count);
            }
        }
        count ++;
    }
}

TrafficSimulation::~TrafficSimulation() {REQUIRE(this->properlyInitialized(), "TrafficSimulation was not initialized when calling destructor");}
