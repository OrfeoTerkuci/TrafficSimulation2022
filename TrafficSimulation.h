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
public:
    TrafficSimulation(const string &filename);

    TrafficSimulation();

    const vector<Road *> &getRoads() const;

    void setRoads(const vector<Road *> &newRoads);

    void addTrafficLight(TrafficLight* &newLight);

    void addVehicle(Vehicle* &newVehicle);

    bool addRoad(Road* newRoad);

    bool parseRoad(TiXmlElement* &root);

    bool parseTrafficLight(TiXmlElement* &root);

    bool parseVehicle(TiXmlElement* &root);

    void print();

    void startSimulation();

    virtual ~TrafficSimulation();
};


#endif //TRAFFICSIMULATION2022_TRAFFICSIMULATIONREADER_H
