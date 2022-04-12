#ifndef TRAFFICSIMULATION2022_TRAFFICSIMULATION_H
#define TRAFFICSIMULATION2022_TRAFFICSIMULATION_H
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#include "tinyxml/tinyxml.h"
#include "Standard_Values.h"
using namespace std;

class Road;
class Vehicle;
class TrafficLight;
class VehicleGenerator;
class CrossRoad;
class BusStop;

class TrafficSimulation {
    string filename;
    vector<Vehicle*> vehicles;
    vector<TrafficLight*> lights;
    vector<Road*> roads;
    vector<VehicleGenerator*> vehicleGenerators;
    vector<CrossRoad*> crossRoads;
    vector<BusStop*> busStops;

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

    const string &getFilename() const;

    /**
     * REQUIRE(this->properlyInitialized(), "TrafficSimulation wasn't properly initialized when calling addTrafficLight");
     * REQUIRE(*typeid(newLight).name() == 'P' , "addTrafficLight was called with invalid parameter");
     * REQUIRE(newLight->properlyInitialized() , "addTrafficLight was called with uninitialized parameter");
     * ENSURE(*oldSize == lights.size() - 1 , "addTrafficLight failed");
     * @param newLight A pointer to a TrafficLight element
    */
    void addTrafficLight(TrafficLight* &newLight);

    /**
     * REQUIRE(this->properlyInitialized(), "TrafficSimulation wasn't properly initialized when calling addVehicle");
     * REQUIRE(*typeid(newVehicle).name() == 'P' , "addVehicle was called with invalid parameter");
     * REQUIRE(newVehicle->properlyInitialized() , "addVehicle was called with uninitialized parameter");
     * ENSURE(*oldSize == vehicles.size() - 1 , "addVehicle failed");
     * @param newVehicle A pointer to a Vehicle element
    */
    void addVehicle(Vehicle* &newVehicle);

    void addCrossRoad(CrossRoad* crossRoad);

    void addBusStop(BusStop* busStop);

    /**
     * REQUIRE(this->properlyInitialized(), "TrafficSimulation wasn't properly initialized when calling addRoad");
     * REQUIRE(*typeid(newRoad).name() == 'P' , "addRoad was called with invalid parameter");
     * REQUIRE(newRoad->properlyInitialized() , "addRoad was called with uninitialized parameter");
     * ENSURE(*oldSize == roads.size() - 1 , "addRoad failed");
     * ENSURE(*oldSize == roads.size() , "addRoad: vector modified when it shouldn't");
     * @param newRoad A pointer to a Road element
     * @return True if the addition was successful
    */
    bool addRoad(Road* newRoad);

    /**
     * REQUIRE(this->properlyInitialized(), "TrafficSimulation wasn't properly initialized when calling addVehicleGenerator");
     * REQUIRE (*typeid(newVehicleGenerator).name() == 'P' , "addVehicleGenerator was called with invalid parameter");
     * REQUIRE (newVehicleGenerator->properlyInitialized() , "addVehicleGenerator was called with uninitialized parameter");
     * ENSURE(*oldSize == vehicleGenerators.size() , "addVehicleGenerator : vector modified when it shouldn't");
     * ENSURE(*oldSize == vehicleGenerators.size() - 1 , "addVehicleGenerator failed");
    */
    bool addVehicleGenerator(VehicleGenerator* newVehicleGenerator);

    void parseXML();

    void parseJSON();
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

    void outputFile(fileFunctionType type);
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


#endif //TRAFFICSIMULATION2022_TRAFFICSIMULATION_H
