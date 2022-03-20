#include "Road.h"
#include "Vehicle.h"
#include "DesignByContract.h"
#include <typeinfo>

Road::Road(unsigned int length, const string &roadName) : length(length), roadName(roadName) , _initCheck(this) {
    REQUIRE( *typeid(length).name() == 'i' && length >= 0, "Length is not a number");
    REQUIRE( *typeid(roadName).name() == 's' && roadName.length() > 0 , "Road has no name" );
    ENSURE(properlyInitialized() , "constructor must end in properlyInitialized state");
}

Road::Road() : length(0) , _initCheck(this) {
    ENSURE(properlyInitialized() , "constructor must end in properlyInitialized state");
}

bool Road::properlyInitialized() const {
    return _initCheck == this;
}

unsigned int Road::getLength() const {
    REQUIRE(properlyInitialized() , "Road wasn't initialized when calling getLength");
    return length;
}

TrafficLight* &Road::getTrafficLight(int index) {
    REQUIRE(properlyInitialized() , "Road wasn't initialized when calling getTrafficLight");
    return trafficLights.at(index);
}

Vehicle *&Road::getVehicle(int index) {
    REQUIRE(properlyInitialized() , "Road wasn't initialized when calling getVehicle");
    return vehicles.at(index);
}

void Road::setLength(unsigned int newLength) {
    REQUIRE(properlyInitialized() , "Road wasn't initialized when calling setLength");
    Road::length = newLength;
}

const string &Road::getRoadName() const {
    REQUIRE(properlyInitialized() , "Road wasn't initialized when calling getRoadName");
    return roadName;
}

void Road::setRoadName(const string &newRoadName) {
    REQUIRE(properlyInitialized() , "Road wasn't initialized when calling setRoadName");
    Road::roadName = newRoadName;
}

const vector<TrafficLight *> &Road::getTrafficLights() const {
    REQUIRE(properlyInitialized() , "Road wasn't initialized when calling getTrafficLights");
    return trafficLights;
}

void Road::setTrafficLights(const vector<TrafficLight *> &newTrafficLights) {
    REQUIRE(properlyInitialized() , "Road wasn't initialized when calling setTrafficLights");
    Road::trafficLights = newTrafficLights;
}

const vector<Vehicle *> &Road::getVehicles() const {
    REQUIRE(properlyInitialized() , "Road wasn't initialized when calling getVehicles");
    return vehicles;
}

void Road::setVehicles(const vector<Vehicle *> &newVehicles) {
    REQUIRE(properlyInitialized() , "Road wasn't initialized when calling setVehicles");
    Road::vehicles = newVehicles;
}

void Road::addVehicle(Vehicle *newVehicle) {
    REQUIRE(properlyInitialized() , "Road wasn't initialized when calling addVehicle");
    vehicles.push_back(newVehicle);
}

void Road::removeVehicle(Vehicle *oldVehicle) {
    for (long unsigned int i = 0; i < this->vehicles.size(); ++i) {
        if (oldVehicle == this->vehicles.at(i)){
            delete this->vehicles.at(i);
            this->vehicles.erase(vehicles.begin() + i);
        }
    }
}

void Road::addLight(TrafficLight *newLight) {
    REQUIRE(properlyInitialized() , "Road wasn't initialized when calling addLight");
    trafficLights.push_back(newLight);
}

int Road::getVehicleAmount() {
    REQUIRE(properlyInitialized() , "Road wasn't initialized when calling getVehicleAmount");
    return this->vehicles.size();
}

int Road::getTrafficLightsAmount() {
    REQUIRE(properlyInitialized() , "Road wasn't initialized when calling getTrafficLightsAmount");
    return this->trafficLights.size();
}

void Road::print() {
    REQUIRE(properlyInitialized() , "Road wasn't initialized when calling print");
    cout << "Road specifications: " << endl;
    cout << '\t' << "Name: " << this->getRoadName() << endl;
    cout << '\t' << "Length: " << this->getLength() << endl;
    // Traffic lights

    // Vehicles
}

Road::~Road() {
    REQUIRE(properlyInitialized() , "Road wasn't initialized when calling destructor");

}
