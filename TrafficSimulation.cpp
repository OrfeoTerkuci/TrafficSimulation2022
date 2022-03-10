#include "TrafficSimulation.h"
#include "Road.h"
#include "TrafficLight.h"
#include "Vehicle.h"
#include "tinyxml/tinyxml.h"
TrafficSimulation::TrafficSimulation(const string &filename) : filename(filename) {}

TrafficSimulation::TrafficSimulation() {}

TrafficSimulation::~TrafficSimulation() {}