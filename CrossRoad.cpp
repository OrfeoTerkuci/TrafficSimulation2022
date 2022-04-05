//
// Created by jason on 05/04/2022.
//

#include "CrossRoad.h"

CrossRoad::CrossRoad() {}

CrossRoad::~CrossRoad() {}

void CrossRoad::addRoad(Road *road, int position) {
    roads[road] = position;
}
