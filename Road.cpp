#include "Road.h"
#include "Vehicle.h"
#include "TrafficLight.h"
#include "DesignByContract.h"
#include "BusStop.h"
#include "CrossRoad.h"
#include <typeinfo>

Road::Road(unsigned int length, const string &roadName) : length(length), roadName(roadName) , init(this) {
    REQUIRE( *typeid(length).name() == 'j' && length >= 0, "Length is not a number or is negative");
    REQUIRE( *typeid(roadName).name() == 'N' && roadName.length() > 0 , "Road has no name" );
    ENSURE(Road::length == length , "Length was not properly initialized");
    ENSURE(Road::roadName == roadName , "roadName was not properly initialized");
    ENSURE(properlyInitialized() , "constructor must end in properlyInitialized state");
}

Road::Road() : length(0) , roadName("") , init(this) {
    ENSURE(length == 0 , "Length was not properly initialized");
    ENSURE(roadName.empty(), "roadName was not properly initialized");
    ENSURE(properlyInitialized() , "constructor must end in properlyInitialized state");
}

bool Road::properlyInitialized() const {
    return init == this;
}

unsigned int Road::getLength() const {
    // Returns the length of the road
    REQUIRE(properlyInitialized() , "Road wasn't initialized when calling getLength");
    return length;
}

void Road::setLength(unsigned int newLength) {
    REQUIRE(properlyInitialized() , "Road wasn't initialized when calling setLength");
    REQUIRE( *typeid(newLength).name() == 'j' , "setLength was called with invalid parameter");
    Road::length = newLength;
    ENSURE( Road::length == newLength , "setLength was failed");
}

const string &Road::getRoadName() const {
    REQUIRE(properlyInitialized() , "Road wasn't initialized when calling getRoadName");
    return roadName;
}

void Road::setRoadName(const string &newRoadName) {
    REQUIRE(properlyInitialized() , "Road wasn't initialized when calling setRoadName");
    REQUIRE( *typeid(newRoadName).name() == 'N' && newRoadName.length() > 0 , "setRoadName was called with invalid parameter");
    Road::roadName = newRoadName;
    ENSURE( Road::roadName == newRoadName , "setRoadName failed");
}

const vector<TrafficLight *> &Road::getTrafficLights() const {
    REQUIRE(properlyInitialized() , "Road wasn't initialized when calling getTrafficLights");
    return trafficLights;
}

void Road::setTrafficLights(const vector<TrafficLight *> &newTrafficLights) {
    REQUIRE(properlyInitialized() , "Road wasn't initialized when calling setTrafficLights");
    REQUIRE(*typeid(newTrafficLights).name() == 'S' , "setTrafficLights was called with invalid parameter");
    Road::trafficLights = newTrafficLights;
    ENSURE(Road::trafficLights == newTrafficLights , "setTrafficLights failed");
}

TrafficLight* &Road::getTrafficLight(unsigned int index) {
    REQUIRE(properlyInitialized() , "Road wasn't initialized when calling getTrafficLight");
    REQUIRE( *typeid(index).name() == 'j' , "Index was not a number when calling getTrafficLight");
    REQUIRE( index < trafficLights.size() , "Index was out of range when calling getTrafficLight");
    return trafficLights.at(index);
}

void Road::addLight(TrafficLight *newLight) {
    REQUIRE(properlyInitialized() , "Road wasn't initialized when calling addLight");
    REQUIRE(*typeid(newLight).name() == 'P' , "addLight was called with invalid parameter");
    REQUIRE(newLight->properlyInitialized(), "addLight was called with uninitialized parameter");
    unsigned int* oldSize = new unsigned int;
    *oldSize = static_cast<unsigned int>(trafficLights.size());
    trafficLights.push_back(newLight);
    ENSURE(*oldSize == trafficLights.size() - 1 , "addLight failed");
    delete oldSize;
}

const vector<Vehicle *> &Road::getVehicles() const {
    REQUIRE(properlyInitialized() , "Road wasn't initialized when calling getVehicles");
    return vehicles;
}

void Road::setVehicles(const vector<Vehicle *> &newVehicles) {
    REQUIRE(properlyInitialized() , "Road wasn't initialized when calling setVehicles");
    REQUIRE(*typeid(newVehicles).name() == 'S' , "setVehicles was called with invalid parameter");
    Road::vehicles = newVehicles;
    ENSURE(Road::vehicles == newVehicles , "setVehicles failed");
}

Vehicle *&Road::getVehicle(unsigned int index) {
    REQUIRE(properlyInitialized() , "Road wasn't initialized when calling getVehicle");
    REQUIRE( *typeid(index).name() == 'j' , "Index was not a number when calling getVehicle");
    REQUIRE( index < vehicles.size() , "Index was out of range when calling getVehicle");
    return vehicles.at(index);
}

void Road::addVehicle(Vehicle *newVehicle) {
    REQUIRE(properlyInitialized() , "Road wasn't initialized when calling addVehicle");
    REQUIRE(*typeid(newVehicle).name() == 'P' , "addVehicle was called with invalid parameter");
    REQUIRE(newVehicle->properlyInitialized() , "addVehicle was called with uninitialized parameter");
    unsigned int* oldSize = new unsigned int;
    *oldSize = static_cast<unsigned int>(vehicles.size());
    vehicles.push_back(newVehicle);
    newVehicle->setRoad(this);
    ENSURE( *oldSize == vehicles.size() - 1 , "addVehicle failed");
    ENSURE( newVehicle->getRoad() == this , "addVehicle failed");
    delete oldSize;
}

void Road::removeVehicle(Vehicle *oldVehicle) {
    REQUIRE(properlyInitialized() , "Road wasn't initialized when calling removeVehicle");
    REQUIRE(*typeid(oldVehicle).name() == 'P' , "removeVehicle was called with invalid parameter");
    REQUIRE(oldVehicle->properlyInitialized() , "removeVehicle was called with uninitialized parameter");
    unsigned int* oldSize = new unsigned int;
    *oldSize = static_cast<unsigned int>(vehicles.size());
    for (long unsigned int i = 0; i < this->vehicles.size(); ++i) {
        if (oldVehicle == this->vehicles.at(i)){
            this->vehicles.erase(vehicles.begin() + i);
        }
    }
    ENSURE(*oldSize == vehicles.size() + 1 , "removeVehicle failed");
    delete oldSize;
}

const vector<BusStop *> &Road::getBusStops() {
    REQUIRE(properlyInitialized() , "Road wasn't initialized when calling getBusStops");
    return busStops;
}

void Road::setBusStops(const vector<BusStop *> &newBusStops) {
    REQUIRE(properlyInitialized() , "Road wasn't initialized when calling setBusStops");
    Road::busStops = newBusStops;
    ENSURE(busStops == newBusStops, "busStops was not assigned to newBusStops, when calling setBusStops");
}

void Road::addBusStop(BusStop *newBusStop) {
    REQUIRE(properlyInitialized() , "Road wasn't initialized when calling addBusStop");
    REQUIRE(*typeid(newBusStop).name() == 'P' , "addBusStop was called with invalid parameter: wrong type");
    REQUIRE(newBusStop->properlyInitialized(), "bus stop isn't properly initialized");
    unsigned int originalSize = busStops.size();
    busStops.push_back(newBusStop);
    ENSURE(busStops.size() == originalSize + 1, "newBusStop wasn't appended in vector busStops, when calling addBusStop");
    ENSURE(busStops[originalSize] == newBusStop, "last item in vector busStops is not equal to newBusStop, when calling addBusStop");
}

const vector<CrossRoad *> &Road::getCrossRaods() {
    REQUIRE(properlyInitialized() , "Road wasn't initialized when calling getCrossRaods");
    return crossRoads;
}

void Road::setCrossRaods(const vector<CrossRoad *> &newCrossRaods) {
    REQUIRE(properlyInitialized() , "Road wasn't initialized when calling setCrossRaods");
    Road::crossRoads = newCrossRaods;
    ENSURE(crossRoads == newCrossRaods, "crossRoads was not assigned to newCrossRoads, when calling newCrossRoads");
}

void Road::addCrossRoad(CrossRoad *crossRoad) {
    REQUIRE(properlyInitialized() , "Road wasn't initialized when calling addCrossRoad");
    REQUIRE(*typeid(crossRoad).name() == 'P' , "addCrossRoad was called with invalid parameter: wrong type");
    REQUIRE(crossRoad->properlyInitialized(), "crossroad wasn't properly initialized");
    unsigned int originalSize = static_cast<unsigned int>(crossRoads.size());
    crossRoads.push_back(crossRoad);
    ENSURE(crossRoads.size() == originalSize + 1, "crossRoads didn't change in size, when calling addCrossRoad");
    ENSURE(crossRoads[originalSize] == crossRoad, "Last item in crossRoads is not the same as crossRoad, when calling addCrossRoad");
}

int Road::getVehicleAmount() {
    REQUIRE(properlyInitialized() , "Road wasn't initialized when calling getVehicleAmount");
    return static_cast<int>(this->vehicles.size());
}

int Road::getTrafficLightsAmount() {
    REQUIRE(properlyInitialized() , "Road wasn't initialized when calling getTrafficLightsAmount");
    return static_cast<int>(this->trafficLights.size());
}

void Road::print() {
    REQUIRE(properlyInitialized() , "Road wasn't initialized when calling print");
    cout << '\t' << "-> Name: " << this->getRoadName() << endl;
    cout << '\t' << "-> Length: " << this->getLength() << endl;
}

Road::~Road() {
    REQUIRE(properlyInitialized() , "Road wasn't initialized when calling destructor");
}
