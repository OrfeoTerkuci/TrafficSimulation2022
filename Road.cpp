#include "Road.h"

Road::Road(unsigned int length, const string &roadName) : length(length), roadName(roadName) {}

unsigned int Road::getLength() const {
    return length;
}

TrafficLight* &Road::getTrafficLights(int index) {
    return trafficLights.at(index);
}

Vehicle *&Road::getVehicles(int index) {
    return vehicles.at(index);
}

void Road::setLength(unsigned int newLength) {
    Road::length = newLength;
}

const string &Road::getRoadName() const {
    return roadName;
}

void Road::setRoadName(const string &newRoadName) {
    Road::roadName = newRoadName;
}

void Road::addVehicle(Vehicle *newVehicle) {
    vehicles.push_back(newVehicle);
}

void Road::addLight(TrafficLight *newLight) {
    trafficLights.push_back(newLight);
}

Road::~Road() {

}

Road::Road() {}
