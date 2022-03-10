#include "TrafficSimulation.h"
#include "Road.h"
#include "TrafficLight.h"
#include "Vehicle.h"
#include "tinyxml/tinyxml.h"

TrafficSimulation::TrafficSimulation(const string &filename) : filename(filename) {
    TiXmlDocument doc;
    if(!doc.LoadFile(this->filename.c_str())) {
        cerr << doc.ErrorDesc() << endl;
    }
}

TrafficSimulation::TrafficSimulation() {}

TrafficSimulation::~TrafficSimulation() {}