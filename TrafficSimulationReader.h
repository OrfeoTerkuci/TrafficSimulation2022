#ifndef TRAFFICSIMULATION2022_TRAFFICSIMULATIONREADER_H
#define TRAFFICSIMULATION2022_TRAFFICSIMULATIONREADER_H
#include <string>
#include <vector>
#include <fstream>

using namespace std;

class Road;
class TrafficLight;
class Vehicle;

class TrafficSimulationReader {
    string filename;

    vector<Road> roads;
    vector<TrafficLight> trafficLights;
    vector<Vehicle> vehicles;

public:
    TrafficSimulationReader(const string &filename);

    TrafficSimulationReader();

    virtual ~TrafficSimulationReader();
};


#endif //TRAFFICSIMULATION2022_TRAFFICSIMULATIONREADER_H
