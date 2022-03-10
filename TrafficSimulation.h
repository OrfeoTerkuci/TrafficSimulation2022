#ifndef TRAFFICSIMULATION2022_TRAFFICSIMULATIONREADER_H
#define TRAFFICSIMULATION2022_TRAFFICSIMULATIONREADER_H
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
using namespace std;

class Road;
class TrafficLight;
class Vehicle;

class TrafficSimulation {
    string filename;

    vector<Road> roads;
    vector<TrafficLight> trafficLights;
    vector<Vehicle> vehicles;

public:
    TrafficSimulation(const string &filename);

    TrafficSimulation();

    virtual ~TrafficSimulation();
};


#endif //TRAFFICSIMULATION2022_TRAFFICSIMULATIONREADER_H
