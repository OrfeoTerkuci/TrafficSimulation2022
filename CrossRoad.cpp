#include "CrossRoad.h"
#include "DesignByContract.h"
#include "Road.h"
#include "Vehicle.h"
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
    return rand() % 1 != 0;
}

Vehicle* CrossRoad::getNearestVehicle(Road* &road) {
    REQUIRE(this->properlyInitialized(), "TrafficSimulation was not initialized when calling getNearestVehicle");
    // Get crossroad position
    double pos = roads[road];
    if(road->getVehicleAmount() == 0){
        return NULL;
    }
    Vehicle* nearestVehicle = road->getVehicle(0);
    Vehicle* currentVehicle;
    for (int i = 0; i < road->getVehicleAmount(); ++i) {
        currentVehicle = road->getVehicle(i);
        if (currentVehicle->getVehiclePosition() < pos && currentVehicle->getVehiclePosition() > nearestVehicle->getVehiclePosition()){
            nearestVehicle = currentVehicle;
        }
    }
    return nearestVehicle;
}

int CrossRoad::getPosition(Road* &road) {
    return roads[road];
}


void CrossRoad::updateSwitchRoad(bool &random , int &time) {
    REQUIRE(this->properlyInitialized(), "Crossroad was not properly initialized when calling updateSwitchRoad");
    switchRoad = random ? randomBool() : ((time % MODULO_RANDOM) == 0) xor switchRoad;
}

void CrossRoad::simulateCrossroad(bool random , int time) {
    REQUIRE(this->properlyInitialized(), "Crossroad was not properly initialized when calling simulateCrossroad");
    Road* currentRoad;
    Road* newRoad;
    Vehicle* currentVehicle;
    Vehicle* tempVehicle;
    map<Road*,int>::iterator it2;
    double currentPos;
    double distance;
    // Loop through both roads
    for(map<Road*,int>::iterator it = roads.begin(); it != roads.end(); it++){
        // Get road , vehicle and position on road
        currentRoad = it->first;
        currentVehicle = getNearestVehicle(currentRoad);
        currentPos = roads[currentRoad];
        if(currentVehicle == NULL){
            continue;
        }
        distance = currentPos - currentVehicle->getVehiclePosition();
        it2 = it;
        it++;
        if(it == roads.end()){
            it = roads.begin();
        }
        newRoad = it->first;
        tempVehicle = getNearestVehicle(newRoad);
        // switchRoad?
        updateSwitchRoad(random , time);
        if (tempVehicle != NULL && roads[newRoad] - (tempVehicle->getVehiclePosition() + tempVehicle->getV_length() ) < tempVehicle->getV_min_followDistance() ){
            it = it2;
            continue;
        }
        else if (switchRoad && distance > 0 &&  distance < currentVehicle->getV_length() ){
            // Get remaining distance
            distance = currentVehicle->getV_length() - distance;
            // Move vehicle to different road
            newRoad->addVehicle(currentVehicle);
            currentVehicle->setRoad(newRoad);
            currentVehicle->setPosition(roads[newRoad] + distance);
            currentRoad->removeVehicle(currentVehicle);
        }
        it = it2;
    }

}

bool CrossRoad::isSwitchRoad() {
    REQUIRE(this->properlyInitialized(), "Crossroad was not properly initialized when calling isSwitchRoad");
    return switchRoad;
}

void CrossRoad::setSwitchRoad(bool new_switchRoad) {
    CrossRoad::switchRoad = new_switchRoad;
}

bool CrossRoad::properlyInitialized() const{
    return init == this;
}

CrossRoad::~CrossRoad() {
    REQUIRE(this->properlyInitialized(), "crossroad was not properly initialized when calling destructor");
}
