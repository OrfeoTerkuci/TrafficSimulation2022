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
     * REQUIRE(this->properlyInitialized(), "TrafficSimulation wasn't properly initialized when calling getRoads");
     * @return A vector of pointers to Road elements
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
    * @return A vector of pointers to VehicleGenerator elements
    */
    const vector<VehicleGenerator *> &getVehicleGenerators();

    /**
    * REQUIRE(this->properlyInitialized(), "TrafficSimulation wasn't properly initialized when calling getVehicles");
    * @return A vector of pointers to Vehicle elements
    */
    const vector<Vehicle *> &getVehicles();

    /**
    * REQUIRE(this->properlyInitialized(), "TrafficSimulation wasn't properly initialized when calling getLights");
    * @return A vector of pointers to TrafficLight elements
    */
    const vector<TrafficLight *> &getLights();

    /**
     * REQUIRE(this->properlyInitialized(), "TrafficSimulation wasn't properly initialized when calling addTrafficLight");
     * REQUIRE(*typeid(newLight).name() == 'P' , "addTrafficLight was called with invalid parameter");
     * ENSURE(*oldSize == lights.size() - 1 , "addTrafficLight failed");
     * @param newLight A pointer to a TrafficLight element
    */
    void addTrafficLight(TrafficLight* &newLight);

    /**
     * REQUIRE(this->properlyInitialized(), "TrafficSimulation wasn't properly initialized when calling addVehicle");
     * REQUIRE(*typeid(newVehicle).name() == 'P' , "addVehicle was called with invalid parameter");
     * ENSURE(*oldSize == vehicles.size() - 1 , "addVehicle failed");
     * @param newVehicle A pointer to a Vehicle element
    */
    void addVehicle(Vehicle* &newVehicle);

    /**
     * REQUIRE(this->properlyInitialized(), "TrafficSimulation wasn't properly initialized when calling addRoad");
     * REQUIRE(*typeid(newRoad).name() == 'P' , "addRoad was called with invalid parameter");
     * ENSURE(*oldSize == roads.size() - 1 , "addRoad failed");
     * ENSURE(*oldSize == roads.size() , "addRoad: vector modified when it shouldn't");
     * @param newRoad A pointer to a Road element
     * @return True if the addition was successful
    */
    bool addRoad(Road* newRoad);

    /**
     * REQUIRE(this->properlyInitialized(), "TrafficSimulation wasn't properly initialized when calling addVehicleGenerator");
     * REQUIRE (*typeid(newVehicleGenerator).name() == 'P' , "addVehicleGenerator was called with invalid parameter");
     * ENSURE(*oldSize == vehicleGenerators.size() , "addVehicleGenerator : vector modified when it shouldn't");
     * ENSURE(*oldSize == vehicleGenerators.size() - 1 , "addVehicleGenerator failed");
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
     * REQUIRE(this->properlyInitialized(), "TrafficSimulation wasn't properly initialized when calling printAll");
    */
    void printAll();

    /**
     * REQUIRE(this->properlyInitialized(), "TrafficSimulation wasn't properly initialized when calling print");
    */
    void print(int &count);

    /**
     * REQUIRE(this->properlyInitialized(), "TrafficSimulation wasn't properly initialized when calling startSimulation");
     * ENSURE(vehicles.empty() , "Simulation ended when it shouldn't");
    */
    void startSimulation();

    /**
     * REQUIRE(this->properlyInitialized(), "TrafficSimulation wasn't properly initialized when calling startSimNoPrint");
     * ENSURE(vehicles.empty() || vehicleGenerators.empty() , "Simulation ended when it shouldn't");
    */
    void startSimNoPrint();

    /**
     * REQUIRE(this->properlyInitialized(), "TrafficSimulation wasn't properly initialized when calling startSimUntilCount");
     * REQUIRE(!this->vehicleGenerators.empty(), "This type of simulation works only for traffic simulations with a vehicle generator");
     * ENSURE(vehicles.size() == MAX_VEHICLES , "Simulation ended before reaching vehicle limit");
    */
    void startSimUntilCount();

    /**
    REQUIRE(this->properlyInitialized(), "TrafficSimulation wasn't properly initialized when calling destructor");
    */
    virtual ~TrafficSimulation();
};


#endif //TRAFFICSIMULATION2022_TRAFFICSIMULATIONREADER_H
