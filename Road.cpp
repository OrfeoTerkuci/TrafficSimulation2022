#include "Road.h"

Road::Road(unsigned int length, const string &roadName) : length(length), roadName(roadName) {}

Road::~Road() {

}

unsigned int Road::getLength() const {
    return length;
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
