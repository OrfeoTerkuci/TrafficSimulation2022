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

    int time;
    int stopTime;

    TrafficSimulation* _initCheck;
    Road* dummyRoad;
public:
    // members
    string outputFileName;
    string outputFileNameHTML;

public: // functions
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

    bool properlyInitialized() const;

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
     * REQUIRE(this->properlyInitialized(), "TrafficSimulation was not initialized when calling setStopTime");
     * ENSURE(newStopTime == stopTime, "stopTime was not assigned to newStopTime, when calling setStopTime");*/
    void setStopTime(int newStopTime);

    /**
     * REQUIRE(this->properlyInitialized(), "TrafficSimulation wasn't properly initialized when calling getVehicleGenerator");
     * @return A vector of pointers to VehicleGenerator elements
    */
    const vector<VehicleGenerator *> &getVehicleGenerators();

    /**
     * REQUIRE(this->properlyInitialized(), "TrafficSimulation wasn't properly initialized when calling getVehicles");
     * @return A vector of pointers to Vehicle elements
    */
    vector<Vehicle *> getVehicles();

    void setVehicles(const vector<Vehicle *> &newvehicles);

    /**
     * REQUIRE(this->properlyInitialized(), "TrafficSimulation wasn't properly initialized when calling getLights");
     * @return A vector of pointers to TrafficLight elements
    */
    const vector<TrafficLight *> &getLights();

    /**
     * REQUIRE(this->properlyInitialized(), "TrafficSimulation wasn't properly initialized when calling getCrossRoads");*/
    const vector<CrossRoad *> & getCrossRoads();

    /**
     * REQUIRE(this->properlyInitialized(), "TrafficSimulation wasn't properly initialized when calling getFilename");*/
    const string &getFilename();

    /**
     * REQUIRE(this->properlyInitialized(), "TrafficSimulation wasn't properly initialized when calling getDummyRoad");
     */
    Road *getDummyRoad() const;


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

    /**
     * REQUIRE(this->properlyInitialized(), "TrafficSimulation wasn't properly initialized when calling addCrossRoad");
     * REQUIRE(*typeid(crossRoad).name() == 'P' , "addCrossRoad was called with invalid parameter: wrong type");
     * REQUIRE(crossRoad->properlyInitialized(), "crossRoad wasn't properly initialized when calling addCrossRoad");
     * @param crossRoad A pointer to a crossRoad element*/
    void addCrossRoad(CrossRoad* crossRoad);

    /**
     * REQUIRE(this->properlyInitialized(), "TrafficSimulation wasn't properly initialized when calling addBusStop");
     * REQUIRE(*typeid(busStop).name() == 'P' , "addBusStop was called with invalid parameter : wrong type");
     * REQUIRE(busStop->properlyInitialized(), "crossRoad wasn't properly initialized when calling addCrossRoad");*/
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

    /**
     * REQUIRE(this->properlyInitialized(), "Trafficsimulation is properly initialized when calling parseXML");*/
    void parseXML();

    /**
     * REQUIRE(this->properlyInitialized(), "Trafficsimulation is properly initialized when calling parseJSON");*/
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
     * REQUIRE(properlyInitialized() , "TrafficSimulation was not properly initialized when calling generateIni");
     * @param override If true, the generated file overrides any existing file with the same name
     * @param lighting If true, there will be lighting
     * @param viewPos The view position
     */
    void generateIni(bool override = true , bool lighting = false , viewPosition viewPos = topView);

    /**
     * REQUIRE(properlyInitialized() , "TrafficSimulation was not properly initialized when calling generateImage");
     * @return 0 if no errors occured
     */
    int generateImage();

    int clearIniFile(string filename);

    /**
     * REQUIRE(this->properlyInitialized(), "TrafficSimulation wasn't properly initialized when calling startSimulation");
     * ENSURE(vehicles.empty() , "Simulation ended when it shouldn't");
     * ENSURE(vehicles.size() == MAX_VEHICLES , "Simulation ended before reaching vehicle limit");
     * @param countE enables simulation run until a determined count
     * @param outputE enables if we're outputting a file
     * @param printE enables if we're printing something on the terminal
     */
    void startSimulation(bool printE = true, bool outputE = true, bool countE = false, bool timeE = false , bool visualise = false , bool override = true , bool lighting = false , viewPosition viewPos = topView);

    /**
     * REQUIRE(this->properlyInitialized(), "TrafficSimulation was not initialized when calling outpputFile");
     * REQUIRE(type == create || type == update || type == closing, "type not matching with any of the file functions");
     * create:
       ENSURE(!outputNewFile.is_open(), "File is still open");
       ENSURE(!outputNewFileHTML.is_open(), "File is still open");
       ENSURE(codefile, "TXT outputfile doesn't exist");
       ENSURE(codefile, "HTML outputfile doesn't exist");
     * update:
       REQUIRE(codefile, "TXT outputfile doesn't exist");
       REQUIRE(codefile, "HTML outputfile doesn't exist");
       ENSURE(!outputFile.is_open(), "TXT-file is closed");
       ENSURE(!outputFileHTML.is_open(), "HTML-file is closed");
     * close:
       REQUIRE(codefile, "HTML outputfile doesn't exist");
       ENSURE(!outputFile.is_open(), "HTML-file is closed");
     * @param type type that determines what function we're committing
     * @param timestamp timestamp of current routine in simulation, default = 0
     */
    void outputFile(fileFunctionType type, int timestamp = 0);

    /**
     * REQUIRE(this->properlyInitialized(), "TrafficSimulation was not initialized when calling outputsStats");
     * ENSURE(!file.is_open(), "file is still open when ending outputStats");
     */
    void outputStats();

    /**
    REQUIRE(this->properlyInitialized(), "TrafficSimulation wasn't properly initialized when calling destructor");
    */
    virtual ~TrafficSimulation();

};


#endif //TRAFFICSIMULATION2022_TRAFFICSIMULATION_H
