//
// Created by jason on 05/04/2022.
//

#include "CrossRoad.h"
#include <cstdlib>

using namespace std;

CrossRoad::CrossRoad() : switchRoad(false){}

void CrossRoad::addRoad(Road *road, int position) {
    roads[road] = position;
}

map<Road *, int> &CrossRoad::getRoads(){
    return roads;
}

void CrossRoad::setRoads(const map<Road *, int> &newRoads) {
    CrossRoad::roads = newRoads;
}

bool randomBool(){
    int i = rand() % 200;
    if (i % 2 == 0){
        return false;
    }
    return true;
}

void CrossRoad::simulateCrossroad(bool random, int modulo_number, int time) {
    // determine to switchroad
    if (random) {
        switchRoad = randomBool();
    } else {
        if (time % modulo_number == 0){
            switchRoad = !switchRoad;
        }
    }

    // simulate

}

CrossRoad::~CrossRoad() {}
