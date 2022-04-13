// custom libs
#include "ParserXML.h"
#include "TrafficSimulation.h"

// c++ libs
#include <stdexcept>
#include <typeinfo>
#include <sstream>
#include <filesystem>

using namespace std;

//==== Constructors and Destructor ====//
TrafficSimulation::TrafficSimulation(const string &filename) : filename(filename) {
    REQUIRE(*typeid(filename).name() == 'N' , "constructor was called with invalid filename");
    _initCheck = this;
    if (filename.find(XMLL) != string::npos or filename.find(XMLU) != string::npos){
        parseXML();
    }
    else if (filename.find(JSONU) != string::npos or filename.find(JSONL) != string::npos){
        parseJSON();
    }
    else {
        cout << "No compatible parser for this type of file" << endl;
    }
    outputFile(create, 0);
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
        outputFile(update, count);
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

const string &TrafficSimulation::getFilename() const {
    return filename;
}

void TrafficSimulation::parseXML() {
    parseTrafficSimulationX(*this);
}

void TrafficSimulation::parseJSON() {

}

void TrafficSimulation::addCrossRoad(CrossRoad* crossRoad) {
    crossRoads.push_back(crossRoad);
}

void TrafficSimulation::addBusStop(BusStop* busStop) {
    busStops.push_back(busStop);
}
void addSpaces(fstream &file, int spaceAmount){
    for (int i = 0; i < spaceAmount; ++i) {
        file << " ";
    }
}
void TrafficSimulation::outputFile(fileFunctionType type, int timestamp) {
    // find file name
    string newFileName = filename.substr(0, filename.find('.'));
    newFileName += ".txt";

    if (type == create){
        // create file
        FILE* codefile;
        bool doesntExists = true;
        fstream outputNewFile;
        int i = 0;
        while (doesntExists){
            i++;
            codefile = fopen(newFileName.c_str(), "r");
            if (codefile){
                newFileName = filename.substr(0, filename.find('.'));
                stringstream intStr;
                intStr << i;
                newFileName += '(';
                newFileName += intStr.str();
                newFileName += ')';
                newFileName += ".txt";
            }
            else {
                outputNewFile.open(newFileName.c_str(), ios::app | ios::ate);
                outputFileName = newFileName;
                doesntExists = false;
            }
        }

        // write in file
        outputNewFile << "TrafficSimulation: " << filename << '\n' << '\n';

        // close file
        outputNewFile.close();

    }
    else if (type == update) {
        // open file
        fstream outputFile;
        outputFile.open(outputFileName.c_str(),ios::app | ios::ate);

        if (outputFile.fail()) {
            cout << "File doesn't exist" << endl;
        }

        // write file
        outputFile << "Time: ";
        outputFile << timestamp;
        outputFile << '\n';
        for (unsigned int j = 0; j < roads.size(); ++j) {
            int nameLenghth = 26;
            int roadLenghth = roads[j]->getLength();
            nameLenghth -= roads[j]->getRoadName().size();
            outputFile << roads[j]->getRoadName();
            addSpaces(outputFile, nameLenghth);
            outputFile << "| ";
            for (int k = 0; k < roadLenghth; ++k) {
                int count = 0;
                for (int l = 0; l < roads[j]->getVehicleAmount(); ++l) {
                    if (k >= (int) roads[j]->getVehicle(l)->getVehiclePosition() and k < (int) roads[j]->getVehicle(l)->getVehiclePosition()+8 and roads[j]->getVehicle(l)->getType() == T_POLICE){
                        outputFile << "P";
                    } else if (k >= (int) roads[j]->getVehicle(l)->getVehiclePosition() and k < (int) roads[j]->getVehicle(l)->getVehiclePosition()+8 and roads[j]->getVehicle(l)->getType() == T_AMBULANCE){
                        outputFile << "Z";
                    } else if (k >= (int) roads[j]->getVehicle(l)->getVehiclePosition() and k < (int) roads[j]->getVehicle(l)->getVehiclePosition()+4 and roads[j]->getVehicle(l)->getType() == T_AUTO){
                        outputFile << "A";
                    } else if (k >= (int) roads[j]->getVehicle(l)->getVehiclePosition() and k < (int) roads[j]->getVehicle(l)->getVehiclePosition()+12 and roads[j]->getVehicle(l)->getType() == T_BUS){
                        outputFile << "B";
                    } else if (k >= (int) roads[j]->getVehicle(l)->getVehiclePosition() and k < (int) roads[j]->getVehicle(l)->getVehiclePosition()+10 and roads[j]->getVehicle(l)->getType() == T_FIRETRUCK){
                        outputFile << "F";
                    } else {
                        count++;
                    }
                }
                if (count == roads[j]->getVehicleAmount()){
                    outputFile << "=";
                }
            }
            outputFile << '\n';
            outputFile << '\t';
            outputFile << "> verkeerslichten";
            addSpaces(outputFile, 5);
            outputFile << "| ";
            for (int i = 0; i < roadLenghth; ++i) {
                int lightsAmount = 0;
                for (int k = 0; k < roads[j]->getTrafficLightsAmount(); ++k) {
                    if (roads[j]->getTrafficLights()[k]->getPosition() == (unsigned) i){
                        if (roads[j]->getTrafficLight(k)->getCurrentColor() == green){
                            outputFile << "G";
                        }
                        else {
                            outputFile << "R";
                        }
                    }
                    else if (roads[j]->getTrafficLight(k)->getPosition()-15 == (unsigned) i){
                        outputFile << '|';
                    }
                    else {
                        lightsAmount++;
                    }
                }
                if (lightsAmount == roads[j]->getTrafficLightsAmount()){
                    outputFile << ' ';
                }
            }
            outputFile << '\n';
            outputFile << '\t';
            outputFile << "> bushaltes";
            addSpaces(outputFile, 11);
            outputFile << "| ";
            for (int i = 0; i < roadLenghth; ++i) {
                for (unsigned int k = 0; k < roads[j]->getBusStops().size(); ++k) {
                    if (roads[j]->getBusStops()[k]->getPosition() == i){
                        outputFile << "B";
                    }
                    else {
                        outputFile << " ";
                    }
                }
            }
            outputFile << '\n';
        }

        // close file
        outputFile.close();
    }
    else if (type == closing) {
        // open file
        fstream outputFile;
        outputFile.open(newFileName.c_str(), ios::app | ios::ate);

        // write file


        // close file
        outputFile.close();
    }
}

TrafficSimulation::~TrafficSimulation() {
    REQUIRE(this->properlyInitialized(), "TrafficSimulation was not initialized when calling destructor");

    // Deleting every object, from memory
    for (unsigned int i = 0; i < roads.size(); ++i) {
        delete roads[i];
    }
    for (unsigned int i = 0; i < lights.size(); ++i) {
        delete lights[i];
    }
    for (unsigned int i = 0; i < busStops.size(); ++i) {
        delete busStops[i];
    }
    for (unsigned int i = 0; i < crossRoads.size(); ++i) {
        delete crossRoads[i];
    }
    for (unsigned int i = 0; i < vehicles.size(); ++i) {
        delete vehicles[i];
    }
    for (unsigned int i = 0; i < vehicleGenerators.size(); ++i) {
        delete vehicleGenerators[i];
    }

    // clearing lists
    roads.clear();
    lights.clear();
    busStops.clear();
    crossRoads.clear();
    vehicles.clear();
    vehicleGenerators.clear();

    // ensuring every list is empty
    ENSURE(roads.empty(), "Roads are not properly destructed");
    ENSURE(lights.empty(), "Lights are not properly destructed");
    ENSURE(busStops.empty(), "Bus stops are not properly destructed");
    ENSURE(crossRoads.empty(), "Crossroads are not properly destructed");
    ENSURE(vehicles.empty(), "Vehicles are not properly destructed");
    ENSURE(vehicleGenerators.empty(), "Vehicle generators are not properly destructed");

}
