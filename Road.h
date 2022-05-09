#ifndef TRAFFICSIMULATION2022_ROAD_H
#define TRAFFICSIMULATION2022_ROAD_H
#include <string>
#include <vector>
#include <iostream>
#include "Standard_Values.h"

using namespace std;

class TrafficLight;
class Vehicle;
class BusStop;
class CrossRoad;

class Road {
    // Parsed variables
    unsigned int length;
    string roadName;
    // Necessary containers for implementation
    vector<TrafficLight*> trafficLights;
    vector<Vehicle*> vehicles;
    vector<BusStop*> busStops;
    vector<CrossRoad*> crossRoads;

    // Self-pointer
    Road* init;

public:

    /**
     * REQUIRE( *typeid(length).name() == 'j' && length >= 0, "Length is not a number");
     * REQUIRE( *typeid(roadName).name() == 'N' && roadName.length() > 0 , "Road has no name" );
     * ENSURE(Road::length == length , "Length was not properly initialized");
     * ENSURE(Road::roadName == roadName , "roadName was not properly initialized");
     * ENSURE(properlyInitialized() , "constructor must end in properlyInitialized state");
     * @param Length Length of the road
     * @param roadName Name of the road
     */
    Road(unsigned int length, const string &roadName);

    /**
     * ENSURE(length == 0 , "Length was not properly initialized");
     * ENSURE(properlyInitialized() , "constructor must end in properlyInitialized state");
     */
    Road();

    bool properlyInitialized() const;

    /**
     * REQUIRE(properlyInitialized() , "Road wasn't initialized when calling getLength");
     * @return The length of the road
     */
    unsigned int getLength() const;

    /**
     * REQUIRE(properlyInitialized() , "Road wasn't initialized when calling setLength");
     * REQUIRE( *typeid(newLength).name() == 'j' , "setLength was called with invalid parameter");
     * ENSURE(Road::length == newLength , "setLength was failed");
     * @param newLength The new length.
     */
    void setLength(unsigned int newLength);

    /**
     * REQUIRE(properlyInitialized() , "Road wasn't initialized when calling getRoadName");
     * @return The name of the road
     */
    const string &getRoadName() const;

    /**
     * REQUIRE(properlyInitialized() , "Road wasn't initialized when calling setRoadName");
     * REQUIRE( *typeid(newRoadName).name() == 'N' && newRoadName.length() > 0 , "setRoadName was called with invalid parameter");
     * ENSURE( Road::roadName == newRoadName , "setRoadName failed");
     * @param newRoadName The new name
     */
    void setRoadName(const string &newRoadName);

    /**
     * REQUIRE(properlyInitialized() , "Road wasn't initialized when calling getTrafficLights");
     * @return A vector of pointers to TrafficLight elements
     */
    const vector<TrafficLight *> &getTrafficLights() const;

    /**
     * REQUIRE(properlyInitialized() , "Road wasn't initialized when calling setTrafficLights");
     * REQUIRE(*typeid(newTrafficLights).name() == 'S' , "setTrafficLights was called with invalid parameter");
     * ENSURE(Road::trafficLights == newTrafficLights , "setTrafficLights failed");
     * @param newTrafficLights A vector of pointers to TrafficLight elements
     */
    void setTrafficLights(const vector<TrafficLight *> &newTrafficLights);

    /**
     * REQUIRE(properlyInitialized() , "Road wasn't initialized when calling getTrafficLight");
     * REQUIRE( *typeid(index).name() == 'j' , "Index was not a number when calling getTrafficLight");
     * REQUIRE( index < trafficLights.size() , "Index was out of range when calling getTrafficLight");
     * @param index The index of the TrafficLight
     * @return A pointer to a TrafficLight element
     */
    TrafficLight* &getTrafficLight(unsigned int index);

    /**
     * REQUIRE(properlyInitialized() , "Road wasn't initialized when calling addLight");
     * REQUIRE(*typeid(newLight).name() == 'P' , "addLight was called with invalid parameter");
     * REQUIRE(newLight->properlyInitialized(), "addLight was called with uninitialized parameter");
     * ENSURE(*oldSize == trafficLights.size() - 1 , "addLight failed");
     */
    void addLight (TrafficLight* newLight);

    /**
     * REQUIRE(properlyInitialized() , "Road wasn't initialized when calling getVehicles");
     */
    const vector<Vehicle *> &getVehicles() const;

    /**
     * REQUIRE(properlyInitialized() , "Road wasn't initialized when calling setVehicles");
     * REQUIRE(*typeid(newVehicles).name() == 'S' , "setVehicles was called with invalid parameter");
     * ENSURE(Road::vehicles == newVehicles , "setVehicles failed");
     */
    void setVehicles(const vector<Vehicle *> &newVehicles);

    /**
     * REQUIRE(properlyInitialized() , "Road wasn't initialized when calling getVehicle");
     * REQUIRE( *typeid(index).name() == 'j' , "Index was not a number when calling getVehicle");
     * REQUIRE( index < vehicles.size() , "Index was out of range when calling getVehicle");
     * @param index The index of the Vehicle
     * @return A pointer to a Vehicle element
     */
    Vehicle* &getVehicle(unsigned int index);

    /**
     * REQUIRE(properlyInitialized() , "Road wasn't initialized when calling addVehicle");
     * REQUIRE(*typeid(newVehicle).name() == 'P' , "addVehicle was called with invalid parameter");
     * REQUIRE(newVehicle->properlyInitialized() , "addVehicle was called with uninitialized parameter");
     * ENSURE(*oldSize == vehicles.size() - 1 , "addVehicle failed");
     * @param newVehicle A pointer to a Vehicle element
     */
    void addVehicle (Vehicle* newVehicle);

    /**
     * REQUIRE(properlyInitialized() , "Road wasn't initialized when calling removeVehicle");
     * REQUIRE(*typeid(oldVehicle).name() == 'P' , "removeVehicle was called with invalid parameter");
     * REQUIRE(oldVehicle->properlyInitialized() , "removeVehicle was called with uninitialized parameter");
     * ENSURE(*oldSize == vehicles.size() + 1 , "removeVehicle failed");
     */
    void removeVehicle(Vehicle* oldVehicle);

    /**
     * REQUIRE(properlyInitialized() , "Road wasn't initialized when calling getBusStops");
     */
    const vector<BusStop *> &getBusStops();

    /**
     * REQUIRE(properlyInitialized() , "Road wasn't initialized when calling setBusStops");
     * ENSURE(busStops == newBusStops, "busStops was not assigned to newBusStops, when calling setBusStops");
     */
    void setBusStops(const vector<BusStop *> &newBusStops);

    /**
     * REQUIRE(properlyInitialized() , "Road wasn't initialized when calling addBusStop");
     * REQUIRE(*typeid(newBusStop).name() == 'P' , "addBusStop was called with invalid parameter: wrong type");
     * REQUIRE(newBusStop->properlyInitialized(), "bus stop isn't properly initialized");
     * ENSURE(busStops.size() == originalSize + 1, "newBusStop wasn't appended in vector busStops, when calling addBusStop");
     * ENSURE(busStops[originalSize] == newBusStop, "last item in vector busStops is not equal to newBusStop, when calling addBusStop");
     */
    void addBusStop (BusStop* newBusStop);

    /**
     * REQUIRE(properlyInitialized() , "Road wasn't initialized when calling getCrossRaods");
     */
    const vector<CrossRoad *> &getCrossRaods();

    /**
     * REQUIRE(properlyInitialized() , "Road wasn't initialized when calling setCrossRaods");
     * ENSURE(crossRoads == newCrossRaods, "crossRoads was not assigned to newCrossRoads, when calling newCrossRoads");
     */
    void setCrossRaods(const vector<CrossRoad *> &newCrossRaods);

    /**
     * REQUIRE(properlyInitialized() , "Road wasn't initialized when calling addCrossRoad");
     * REQUIRE(*typeid(crossRoad).name() == 'P' , "addCrossRoad was called with invalid parameter: wrong type");
     * REQUIRE(crossRoad->properlyInitialized(), "crossroad wasn't properly initialized");
     * ENSURE(crossRoads.size() == originalSize + 1, "crossRoads didn't change in size, when calling addCrossRoad");
     * ENSURE(crossRoads[originalSize] == crossRoad, "Last item in crossRoads is not the same as crossRoad, when calling addCrossRoad");
     */
    void addCrossRoad(CrossRoad* crossRoad);

    /**
     * REQUIRE(properlyInitialized() , "Road wasn't initialized when calling getVehicleAmount");
     * @return The number of vehicles on the road
     */
    int getVehicleAmount();

    /**
     * REQUIRE(properlyInitialized() , "Road wasn't initialized when calling getTrafficLightsAmount");
     * @return The number of traffic lights on the road
     */
    int getTrafficLightsAmount();

    /**
     * REQUIRE(properlyInitialized() , "Road wasn't initialized when calling print");
     * @brief Prints the road name and length
     */
    void print();

    /**
     * REQUIRE(properlyInitialized() , "Road wasn't initialized when calling destructor");
     */
    virtual ~Road();
};


#endif //TRAFFICSIMULATION2022_ROAD_H
