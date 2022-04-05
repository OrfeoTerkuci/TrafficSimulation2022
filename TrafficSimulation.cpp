// custom libs
#include "TrafficSimulation.h"
#include "Road.h"
#include "TrafficLight.h"
#include "Vehicle.h"
#include "VehicleGenerator.h"
#include "Standard_Values.h"
#include "DesignByContract.h"
#include "ExtraFunctions.h"

// c++ libs
#include <stdexcept>
#include <typeinfo>
#include <sstream>

//==== Parsing Functions ====//
bool TrafficSimulation::parseRoad(TiXmlElement* &root){
    REQUIRE(this->properlyInitialized(), "TrafficSimulation was not initialized when calling parseRoad");
    REQUIRE(*typeid(root).name() == 'P' , "parseRoad was called with invalid parameter");
    // create road object
    Road *newRoad = new Road();

    // temp values
    string tempn;
    int tempi;

    // Parsing
    for(TiXmlElement* elem = root->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement()) {
        string elemName = elem->Value();

        if(elem->NoChildren()){
            delete newRoad;
            REQUIRE(!elem->NoChildren(), "One of the parameters was empty");
            return false;
        }

        tempn = elem->GetText();


        if(elemName == NAAM){
            newRoad->setRoadName(tempn);
        }
        else if(elemName == LENGTE){
            tempi = convertStrToInt(tempn);
            if(tempi <= 0){
                delete newRoad;
                REQUIRE(tempi >= 0, "Road length is not valid");
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
    REQUIRE(*typeid(root).name() == 'P' , "parseTrafficLight was called with invali parameter");
    // Create object
    TrafficLight* trafficLight = new TrafficLight();

    // Create temp values
    string tempn;
    int tempi;

    // Parsing
    for(TiXmlElement* elem = root->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement()) {
        string elemName = elem->Value();

        // if elem is empty, end parsing and return false
        if(elem->NoChildren()){
            delete trafficLight;
            REQUIRE(!elem->NoChildren(), "One of the parameters was empty");
            return false;
        }

        tempn = elem->GetText();


        if(elemName == BAANL){
            for (unsigned int i = 0; i < this->roads.size(); ++i) {
                if (tempn == this->roads[i]->getRoadName()) {
                    trafficLight->setRoad(this->roads[i]);
                    break;
                }
            }
        }
        else if(elemName == POSITIE){
            tempi = convertStrToInt(elem->GetText());
            if (tempi < 0 || tempi > int(trafficLight->getRoad()->getLength()) ){
                delete trafficLight;
                REQUIRE(false, "Position is not valid");
            }
            trafficLight->setPosition(tempi);
        }
        else if(elemName == CYCLUS){
            tempi = convertStrToInt(elem->GetText());
            if (tempi <= 0){
                delete trafficLight;
                REQUIRE(tempi >= 0, "Cycle is not valid");
                return false;
            }
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
    REQUIRE(*typeid(root).name() == 'P' , "parseVehicle was called with invalid parameter");
    Vehicle* vehicle = new Vehicle();

    string tempn;
    int tempi;

    for(TiXmlElement* elem = root->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement()) {
        string elemName = elem->Value();

        // if elem is empty, end parsing and return false
        if(elem->NoChildren()){
            delete vehicle;
            REQUIRE(!elem->NoChildren(), "One of the parameters was empty");
            return false;
        }
        tempn = elem->GetText();

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
            tempi = convertStrToInt(tempn);
            if (tempi < 0){
                delete vehicle;
                REQUIRE(tempi > 0, "Position is not valid");
                return false;
            }
            vehicle->setPosition(tempi);
        }
    }

    return true;
}

bool TrafficSimulation::parseVehicleGenerator(TiXmlElement *&root) {
    REQUIRE(this->properlyInitialized(), "TrafficSimulation was not initialized when calling parseVehicleGenerator");
    REQUIRE(*typeid(root).name() == 'P' , "parseVehicleGenerator was called with invalid parameter");
    VehicleGenerator* vehicleGenerator = new VehicleGenerator();

    string tempn;
    int tempf;

    for(TiXmlElement* elem = root->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement()) {
        string elemName = elem->Value();

        // if elem is empty, end parsing and return false
        if(elem->NoChildren()){
            delete vehicleGenerator;
            REQUIRE(!elem->NoChildren(), "One of the parameters was empty");
            return false;
        }
        tempn = elem->GetText();


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
            tempf = convertStrToInt(elem->GetText());
            if (tempf < 0){
                delete vehicleGenerator;
                REQUIRE(tempf > 0, "Frequency is not valid");
                return false;
            }
            vehicleGenerator->setFrequentie(tempf);
            // Set cooldown : 0 for instant generation upon simulation start
            vehicleGenerator->setCooldown(tempf);
        }
    }
    return true;
}



//==== Constructors and Destructor ====//
TrafficSimulation::TrafficSimulation(const string &filename) : filename(filename) {
    REQUIRE(*typeid(filename).name() == 'N' , "constructor was called with invalid filename");
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
    ENSURE(TrafficSimulation::filename == filename , "filename was not properly initialized");
    ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
}

TrafficSimulation::TrafficSimulation() {_initCheck = this;
    ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
    }

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
    REQUIRE(*typeid(newRoads).name() == 'S' , "setRoads was called with invalid parameter");
    TrafficSimulation::roads = newRoads;
    ENSURE(TrafficSimulation::roads == newRoads , "setRoads failed");
}

const vector<TrafficLight *> &TrafficSimulation::getLights() {
    REQUIRE(this->properlyInitialized(), "TrafficSimulation wasn't properly initialized when calling getLights");
    return lights;
}

const vector<Vehicle *> &TrafficSimulation::getVehicles(){
    REQUIRE(this->properlyInitialized(), "TrafficSimulation wasn't properly initialized when calling getVehicles");
    return vehicles;
}

void TrafficSimulation::addTrafficLight(TrafficLight *&newLight) {
    REQUIRE(this->properlyInitialized(), "TrafficSimulation was not initialized when calling addTrafficLight");
    REQUIRE(*typeid(newLight).name() == 'P' , "addTrafficLight was called with invalid parameter");
    REQUIRE(newLight->properlyInitialized() , "addTrafficLight was called with uninitialized parameter");
    unsigned int* oldSize = new unsigned int;
    *oldSize = lights.size();
    this->lights.push_back(newLight);
    ENSURE(*oldSize == lights.size() - 1 , "addTrafficLight failed");
    delete oldSize;
}

void TrafficSimulation::addVehicle(Vehicle *&newVehicle) {
    REQUIRE(this->properlyInitialized(), "TrafficSimulation was not initialized when calling addVehicle");
    REQUIRE(*typeid(newVehicle).name() == 'P' , "addVehicle was called with invalid parameter");
    REQUIRE(newVehicle->properlyInitialized() , "addVehicle was called with uninitialized parameter");
    unsigned int* oldSize = new unsigned int;
    *oldSize = vehicles.size();
    this->vehicles.push_back(newVehicle);
    ENSURE(*oldSize == vehicles.size() - 1 , "addVehicle failed");
    delete oldSize;
}

bool TrafficSimulation::addRoad(Road *newRoad) {
    REQUIRE(this->properlyInitialized(), "TrafficSimulation was not initialized when calling addRoad");
    REQUIRE(*typeid(newRoad).name() == 'P' , "addRoad was called with invalid parameter");
    REQUIRE(newRoad->properlyInitialized() , "addRoad was called with uninitialized parameter");
    unsigned int* oldSize = new unsigned int;
    *oldSize = roads.size();
    for (unsigned int i = 0; i < this->roads.size(); ++i) {
        if(this->roads[i] == newRoad){
            ENSURE(*oldSize == roads.size() , "addRoad: vector modified when it shouldn't");
            return false;
        }
    }
    this->roads.push_back(newRoad);
    ENSURE(*oldSize == roads.size() - 1 , "addRoad failed");
    delete oldSize;
    return true;
}

bool TrafficSimulation::addVehicleGenerator(VehicleGenerator *newVehicleGenerator) {
    REQUIRE(this->properlyInitialized(), "TrafficSimulation was not initialized when calling addVehicleGenerator");
    REQUIRE (*typeid(newVehicleGenerator).name() == 'P' , "addVehicleGenerator was called with invalid parameter");
    REQUIRE (newVehicleGenerator->properlyInitialized() , "addVehicleGenerator was called with uninitialized parameter");
    unsigned int* oldSize = new unsigned int;
    *oldSize = vehicleGenerators.size();
    // Check if the vehicle generator is already present
    for (unsigned int i = 0; i < this->vehicleGenerators.size(); ++i) {
        if (this->vehicleGenerators[i]->getRoad() == newVehicleGenerator->getRoad()){
            ENSURE(*oldSize == vehicleGenerators.size() , "addVehicleGenerator : vector modified when it shouldn't");
            return false;
        }
    }
    this->vehicleGenerators.push_back(newVehicleGenerator);
    ENSURE(*oldSize == vehicleGenerators.size() - 1 , "addVehicleGenerator failed");
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

            if(this->vehicleGenerators.size() == 1){
                cout << "Consists of " << vehicleGenerators.size() << " Vehicle Generator: " << endl;
            }
            else if(this->vehicleGenerators.size() > 1){
                cout << "Consists of " << vehicleGenerators.size() << " Vehicle Generators: " << endl;
            }

            cout << endl;

            for (long unsigned int l = 0; l < this->vehicleGenerators.size(); ++l) {
                cout << "Vehicle Generator " << l << " : " << endl;
                cout << '\t' << "-> Road: " << this->vehicleGenerators[l]->getRoad()->getRoadName() << endl;
                cout << '\t' << "-> Frequency: " << this->vehicleGenerators[l]->getFrequentie() << endl;
                cout << endl;
            }
        }
    }
    else{
        cout << "There are no roads." << endl;
    }
}

void TrafficSimulation::print( int &count) {
    REQUIRE(this->properlyInitialized(), "TrafficSimulation was not initialized when calling print");
    if (!this->vehicles.empty() || !this->vehicleGenerators.empty()){
        cout << "Time: " << count << endl;
        for (long unsigned int i = 0; i < this->vehicles.size(); ++i) {
            cout << "Vehicle " << i+1 << ": " << endl;
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

    while (!this->vehicles.empty() || !this->vehicleGenerators.empty()){
        for (unsigned int i = 0; i < this->vehicles.size(); ++i){
            // Get current vehicle
            currentVehicle = this->vehicles.at(i);
            // Get current road
            currentRoad = currentVehicle->getRoad();
            // Simulate vehicle
            currentVehicle->simulate();
            // Get vehicle position
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
        for (unsigned int k = 0; k < this->vehicleGenerators.size(); k++){
            VehicleGenerator* currentGenerator;
            currentGenerator = this->vehicleGenerators.at(k);
            // Check if we can generate
            if (currentGenerator->simulate())
            {
                // Generate new vehicle
                Vehicle* newVehicle;
                newVehicle = new Vehicle();
                // Add road to vehicle
                newVehicle->setRoad(currentGenerator->getRoad());
                // Add vehicle to road
                newVehicle->setRoad(currentGenerator->getRoad());
                currentGenerator->getRoad()->addVehicle(newVehicle);
                // Add vehicle to our simulation
                this->addVehicle(newVehicle);
            }
        }
        print(count);
        count ++;
    }
    cout << "- There are no vehicles on the road network." << endl;
    cout << "- Ending simulation" << endl;
    ENSURE(vehicles.empty() , "Simulation ended when it shouldn't");
}

void TrafficSimulation::startSimNoPrint() {
    REQUIRE(this->properlyInitialized(), "TrafficSimulation was not initialized when calling startSimNoPrint");
    int count = 0;
    double vehiclePosition;
    int roadLength;
    Vehicle* currentVehicle;
    Road* currentRoad;

    while (!this->vehicles.empty() || !this->vehicleGenerators.empty()){
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
        for (unsigned int k = 0; k < this->vehicleGenerators.size(); k++){
            VehicleGenerator* currentGenerator;
            currentGenerator = this->vehicleGenerators.at(k);
            // Check if we can generate
            if (currentGenerator->simulate())
            {
                // Generate new vehicle
                Vehicle* newVehicle;
                newVehicle = new Vehicle();
                // Add road to vehicle
                newVehicle->setRoad(currentGenerator->getRoad());
                // Add vehicle to road
                currentGenerator->getRoad()->addVehicle(newVehicle);
                // Add vehicle to our simulation
                this->addVehicle(newVehicle);
            }
        }
        count ++;
    }
    ENSURE(vehicles.empty() || vehicleGenerators.empty() , "Simulation ended when it shouldn't");
}

void TrafficSimulation::startSimUntilCount() {
    REQUIRE(this->properlyInitialized(), "TrafficSimulation was not initialized when calling startSimUntilCount");
    REQUIRE(!this->vehicleGenerators.empty(), "This type of simulation works only for traffic simulations with a vehicle generator");
    int count = 0;
    double vehiclePosition;
    int roadLength;
    Vehicle* currentVehicle;
    Road* currentRoad;

    while (this->vehicles.size() != MAX_VEHICLES * this->vehicleGenerators.size()){
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
        for (unsigned int k = 0; k < this->vehicleGenerators.size(); k++){
            VehicleGenerator* currentGenerator;
            currentGenerator = this->vehicleGenerators.at(k);
            // Check if we can generate
            if (currentGenerator->simulate())
            {
                // Generate new vehicle
                Vehicle* newVehicle;
                newVehicle = new Vehicle();
                // Add road to vehicle
                newVehicle->setRoad(currentGenerator->getRoad());
                // Add vehicle to road
                currentGenerator->getRoad()->addVehicle(newVehicle);
                // Add vehicle to our simulation
                this->addVehicle(newVehicle);
            }
        }
        count ++;
    }
    ENSURE(vehicles.size() == MAX_VEHICLES * this->vehicleGenerators.size(), "Simulation ended before reaching vehicle limit");
}

TrafficSimulation::~TrafficSimulation() {
    REQUIRE(this->properlyInitialized(), "TrafficSimulation was not initialized when calling destructor");
}

const string &TrafficSimulation::getFilename() const {
    return filename;
}
