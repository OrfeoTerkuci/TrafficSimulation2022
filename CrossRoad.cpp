#include "CrossRoad.h"
#include "DesignByContract.h"
#include "Road.h"
#include <cstdlib>

using namespace std;

CrossRoad::CrossRoad() : switchRoad(false){
    init = this;
    ENSURE(this == init, "init is not equal to itself, when calling constructor");
}

void CrossRoad::addRoad(Road *road, int position) {
    REQUIRE(this->properlyInitialized(), "Crossroad was not properly initialized when calling addRoad");
    REQUIRE(road->properlyInitialized(), "Road is not properly initialized when calling addRoad");
    REQUIRE(position >= 0 and (unsigned) position <= road->getLength(), "position was out of bounds when calling addRoad");
    roads[road] = position;
    ENSURE(roads[road] == position, "road is not on the right position");
}

map<Road *, int> &CrossRoad::getRoads(){
    REQUIRE(this->properlyInitialized(), "Crossroad was not properly initialized when calling getRoad");
    return roads;
}

void CrossRoad::setRoads(const map<Road *, int> &newRoads) {
    REQUIRE(this->properlyInitialized(), "Crossroad was not properly initialized when calling setRoad");
    CrossRoad::roads = newRoads;
    ENSURE(roads == newRoads, "roads was not assigned to newRoads, when calling setRoads");
}

bool randomBool(){
    int i = rand() % 1;
    if (i == 0){
        return false;
    }
    return true;
}

void CrossRoad::simulateCrossroad(bool random, int modulo_number, int time) {
    REQUIRE(this->properlyInitialized(), "Crossroad was not properly initialized when calling simulateCrossroad");
    // determine to switchroad
    if (random) {
        switchRoad = randomBool();
    } else {
        if (time % modulo_number == 0){
            switchRoad = !switchRoad;
        }
    }
}

bool CrossRoad::isSwitchRoad() {
    REQUIRE(this->properlyInitialized(), "Crossroad was not properly initialized when calling isSwitchRoad");
    return switchRoad;
}

bool CrossRoad::properlyInitialized() const{
    return init == this;
}

CrossRoad::~CrossRoad() {
    REQUIRE(this->properlyInitialized(), "crossroad was not properly initialized when calling destructor");
}
