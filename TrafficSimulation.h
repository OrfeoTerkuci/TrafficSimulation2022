#ifndef TRAFFICSIMULATION2022_TRAFFICSIMULATIONREADER_H
#define TRAFFICSIMULATION2022_TRAFFICSIMULATIONREADER_H
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#include "tinyxml/tinyxml.h"
using namespace std;

class Road;
class Vehicle;
class TrafficLight;

class TrafficSimulation {
    string filename;
    vector<Vehicle*> vehicles;
    vector<TrafficLight*> lights;
    vector<Road*> roads;

    TrafficSimulation* _initCheck;
public:
    /**
    ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
    */
    TrafficSimulation(const string &filename);

    TrafficSimulation();

    bool properlyInitialized();

    /**
    REQUIRE(this->properlyInitialized(), "TrafficSimulation wasn't properly initialized when calling getRoads");
    */
    const vector<Road *> & getRoads();

    /**
    REQUIRE(this->properlyInitialized(), "TrafficSimulation wasn't properly initialized when calling setRoads");
    */
    void setRoads(const vector<Road *> &newRoads);

    /**
    REQUIRE(this->properlyInitialized(), "TrafficSimulation wasn't properly initialized when calling addTrafficLight");
    */
    void addTrafficLight(TrafficLight* &newLight);

    /**
    REQUIRE(this->properlyInitialized(), "TrafficSimulation wasn't properly initialized when calling addVehicle");
    */
    void addVehicle(Vehicle* &newVehicle);

    /**
    REQUIRE(this->properlyInitialized(), "TrafficSimulation wasn't properly initialized when calling addRoad");
    */
    bool addRoad(Road* newRoad);

    /**
    REQUIRE(this->properlyInitialized(), "TrafficSimulation wasn't properly initialized when calling parseRoad");
    */
    bool parseRoad(TiXmlElement* &root);

    /**
    REQUIRE(this->properlyInitialized(), "TrafficSimulation wasn't properly initialized when calling parseTrafficLight");
    */
    bool parseTrafficLight(TiXmlElement* &root);

    /**
    REQUIRE(this->properlyInitialized(), "TrafficSimulation wasn't properly initialized when calling parseVehicle");
    */
    bool parseVehicle(TiXmlElement* &root);

    /**
    REQUIRE(this->properlyInitialized(), "TrafficSimulation wasn't properly initialized when calling printAll");
    */
    void printAll();

    /**
    REQUIRE(this->properlyInitialized(), "TrafficSimulation wasn't properly initialized when calling print");
    */
    void print(int &count);

    /**
    REQUIRE(this->properlyInitialized(), "TrafficSimulation wasn't properly initialized when calling startSimulation");
    */
    void startSimulation();

    /**
    REQUIRE(this->properlyInitialized(), "TrafficSimulation wasn't properly initialized when calling destructor");
    */
    virtual ~TrafficSimulation();
};


#endif //TRAFFICSIMULATION2022_TRAFFICSIMULATIONREADER_H
