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

    TrafficLight* &getTrafficLights(int index);

    Vehicle* &getVehicles(int index);

    void setLength(unsigned int newLength);

    const string &getRoadName() const;

    void setRoadName(const string &newRoadName);

    void addVehicle (Vehicle* newVehicle);

    void addLight (TrafficLight* newLight);

    virtual ~Road();

    int getVehicleAmount();

    int getTrafficLightsAmount()

    void print();
};


#endif //TRAFFICSIMULATION2022_ROAD_H
