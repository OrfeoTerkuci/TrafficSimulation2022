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
class VehicleGenerator;

class TrafficSimulation {
    string filename;
    vector<Vehicle*> vehicles;
    vector<TrafficLight*> lights;
    vector<Road*> roads;
    vector<VehicleGenerator*> vehicleGenerators;

    TrafficSimulation* _initCheck;
public:
    /**
    * REQUIRE(*typeid(filename).name() == 'N' , "constructor was called with invalid filename");
    * ENSURE(TrafficSimulation::filename == filename , "filename was not properly initialized");
    * ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
    * @param filename The TO BE PARSED file's name
    */
    explicit TrafficSimulation(const string &filename);

    /**
     * ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
     */
    TrafficSimulation();

    bool properlyInitialized();

    /**
    REQUIRE(this->properlyInitialized(), "TrafficSimulation wasn't properly initialized when calling getRoads");
    */
    const vector<Road *> & getRoads();

    /**
    * REQUIRE(this->properlyInitialized(), "TrafficSimulation wasn't properly initialized when calling setRoads");
    * REQUIRE(*typeid(newRoads).name() == 'S' , "setRoads was called with invalid parameter");
    * ENSURE(TrafficSimulation::roads == newRoads , "setRoads failed");
    * @param newRoads A vector of pointers to Road elements
    */
    void setRoads(const vector<Road *> &newRoads);

    /**
    * REQUIRE(this->properlyInitialized(), "TrafficSimulation wasn't properly initialized when calling getVehicleGenerator");
    * 
    */
    const vector<VehicleGenerator *> &getVehicleGenerators();

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
    REQUIRE(this->properlyInitialized(), "TrafficSimulation wasn't properly initialized when calling addVehicleGenerator");
    */
    bool addVehicleGenerator(VehicleGenerator* newVehicleGenerator);

    /**
     * REQUIRE(this->properlyInitialized(), "TrafficSimulation wasn't properly initialized when calling parseRoad");
     * REQUIRE(*typeid(root).name() == 'P' , "parseRoad was called with invalid parameter");
     * @param root A pointer to a TiXmlElement
     * @return True if parsing was successful
    */
    bool parseRoad(TiXmlElement* &root);

    /**
    * REQUIRE(this->properlyInitialized(), "TrafficSimulation wasn't properly initialized when calling parseTrafficLight");
    * REQUIRE(*typeid(root).name() == 'P' , "parseTrafficLight was called with invali parameter");
    * @param root A pointer to a TiXmlElement
    * @return True if parsing was successful
    */
    bool parseTrafficLight(TiXmlElement* &root);

    /**
    * REQUIRE(this->properlyInitialized(), "TrafficSimulation wasn't properly initialized when calling parseVehicle");
    * REQUIRE(*typeid(root).name() == 'P' , "parseVehicle was called with invalid parameter");
    * @param root A pointer to a TiXmlElement
    * @return True if parsing was successful
    */
    bool parseVehicle(TiXmlElement* &root);

    /**
    * REQUIRE(this->properlyInitialized(), "TrafficSimulation wasn't properly initialized when calling parseVehicleGenerator");
    * REQUIRE(*typeid(root).name() == 'P' , "parseVehicleGenerator was called with invalid parameter");
    * @param root A pointer to a TiXmlElement
    * @return True if parsing was successful
    */
    bool parseVehicleGenerator(TiXmlElement* &root);

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
    REQUIRE(this->properlyInitialized(), "TrafficSimulation wasn't properly initialized when calling startSimNoPrint");
    */
    void startSimNoPrint();

    /**
    REQUIRE(this->properlyInitialized(), "TrafficSimulation wasn't properly initialized when calling startSimUntilCount");
    */
    void startSimUntilCount();

    /**
    REQUIRE(this->properlyInitialized(), "TrafficSimulation wasn't properly initialized when calling destructor");
    */
    virtual ~TrafficSimulation();
};


#endif //TRAFFICSIMULATION2022_TRAFFICSIMULATIONREADER_H
