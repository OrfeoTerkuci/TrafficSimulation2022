//
// Created by jason on 05/04/2022.
//

#include "CrossRoad.h"

CrossRoad::CrossRoad() {}

CrossRoad::~CrossRoad() {}

void CrossRoad::addRoad(Road *road, int position) {
    roads[road] = position;
}

const map<Road *, int> &CrossRoad::getRoads() const {
    return roads;
}

void CrossRoad::setRoads(const map<Road *, int> &newRoads) {
    CrossRoad::roads = newRoads;
}
