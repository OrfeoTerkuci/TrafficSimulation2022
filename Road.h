#ifndef TRAFFICSIMULATION2022_ROAD_H
#define TRAFFICSIMULATION2022_ROAD_H
#include <string>
#include <vector>
#include <iostream>

using namespace std;

class TrafficLight;
class Vehicle;

class Road {
    // Parsed variables
    unsigned int length;
    string roadName;
    // Necessary containers for implementation
    vector<TrafficLight*> trafficLights;
    vector<Vehicle*> vehicles;
    // Self-pointer
    Road* _initCheck;

public:

    /*
     * ENSURE(properlyInitialized() , "constructor must end in properlyInitialized state");
     */
    Road(unsigned int length, const string &roadName);

    /*
     * ENSURE(properlyInitialized() , "constructor must end in properlyInitialized state");
     */
    Road();

    bool properlyInitialized() const;

    unsigned int getLength() const;

    TrafficLight* &getTrafficLight(int index);

    const vector<TrafficLight *> &getTrafficLights() const;

    void setTrafficLights(const vector<TrafficLight *> &newTrafficLights);

    const vector<Vehicle *> &getVehicles() const;

    void setVehicles(const vector<Vehicle *> &newVehicles);

    Vehicle* &getVehicle(int index);

    void setLength(unsigned int newLength);

    const string &getRoadName() const;

    void setRoadName(const string &newRoadName);

    void addVehicle (Vehicle* newVehicle);

    void removeVehicle(Vehicle* oldVehicle);

    void addLight (TrafficLight* newLight);

    int getVehicleAmount();

    int getTrafficLightsAmount();

    void print();

    virtual ~Road();
};


#endif //TRAFFICSIMULATION2022_ROAD_H
