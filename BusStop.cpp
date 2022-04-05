//
// Created by jason on 05/04/2022.
//

#include "BusStop.h"

BusStop::BusStop(int waitTime, int position, Road *road) : waitTime(waitTime), position(position), road(road) {}

BusStop::BusStop() {}

BusStop::~BusStop() {

}

int BusStop::getWaitTime() const {
    return waitTime;
}

void BusStop::setWaitTime(int newWaitTime) {
    BusStop::waitTime = newWaitTime;
}

int BusStop::getPosition() const {
    return position;
}

void BusStop::setPosition(int newPosition) {
    BusStop::position = newPosition;
}

Road *BusStop::getRoad() const {
    return road;
}

void BusStop::setRoad(Road *newRoad) {
    BusStop::road = newRoad;
}
