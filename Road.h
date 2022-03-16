#ifndef TRAFFICSIMULATION2022_ROAD_H
#define TRAFFICSIMULATION2022_ROAD_H
#include <string>
#include <vector>
#include <iostream>

using namespace std;

class TrafficLight;
class Vehicle;

class Road {
    unsigned int length;

    string roadName;
    vector<TrafficLight*> trafficLights;
    vector<Vehicle*> vehicles;

public:
    Road(unsigned int length, const string &roadName);

    Road();

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

    void addLight (TrafficLight* newLight);

    int getVehicleAmount();

    int getTrafficLightsAmount();

    void print();

    virtual ~Road();
};


#endif //TRAFFICSIMULATION2022_ROAD_H
