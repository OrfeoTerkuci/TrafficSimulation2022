#ifndef TRAFFICSIMULATION2022_TRAFFICSIMULATIONREADER_H
#define TRAFFICSIMULATION2022_TRAFFICSIMULATIONREADER_H
#include <string>
#include <fstream>

using namespace std;

class TrafficSimulationReader {
    string filename;
public:
    TrafficSimulationReader(const string &filename);

    TrafficSimulationReader();

    virtual ~TrafficSimulationReader();


};


#endif //TRAFFICSIMULATION2022_TRAFFICSIMULATIONREADER_H
