#include "CrossRoad.h"
#include "DesignByContract.h"
#include "Road.h"
#include "Vehicle.h"

#include <cstdlib>
#include <typeinfo>
using namespace std;

CrossRoad::CrossRoad() : switchRoad(false) , init(this) {
    ENSURE(!switchRoad, "switchRoad was not properly initialized");
    ENSURE(properlyInitialized(), "CrossRoad was not properly initialized");
}

bool CrossRoad::properlyInitialized() const{
    return init == this;
}

bool CrossRoad::isSwitchRoad() {
    REQUIRE(this->properlyInitialized(), "Crossroad was not properly initialized when calling isSwitchRoad");
    return switchRoad;
}

void CrossRoad::setSwitchRoad(bool new_switchRoad) {
    REQUIRE(this->properlyInitialized(), "Crossroad was not properly initialized, when calling setSwitchRoad");
    REQUIRE(*typeid(new_switchRoad).name() == 'b', "new_switchRoad is not of type bool");
    CrossRoad::switchRoad = new_switchRoad;
    ENSURE(CrossRoad::switchRoad == new_switchRoad , "setSwitchRoad failed");
}

void CrossRoad::updateSwitchRoad(bool &random , int &time) {
    REQUIRE(this->properlyInitialized(), "Crossroad was not properly initialized when calling updateSwitchRoad");
    switchRoad = random ? rand() % 1 != 0 : ((time % MODULO_RANDOM) == 0) xor switchRoad;
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


void CrossRoad::addRoad(Road *road, int position) {
    REQUIRE(this->properlyInitialized(), "Crossroad was not properly initialized when calling addRoad");
    REQUIRE(*typeid(road).name() == 'P' , "addRoad was called with invalid road parameter : wrong type");
    REQUIRE(road->properlyInitialized(), "Road is not properly initialized when calling addRoad");
    REQUIRE(*typeid(position).name() == 'i' , "addRoad was called with invalid position parameter : wrong type");
    REQUIRE(position >= 0 and (unsigned) position <= road->getLength(), "position was out of bounds when calling addRoad");
    roads[road] = position;
    ENSURE(roads[road] == position, "road is not on the right position");
}

int CrossRoad::getPosition(Road* &road) {
    REQUIRE(this->properlyInitialized(), "TrafficSimulation was not initialized when calling getPosition");
    REQUIRE(*typeid(road).name() == 'P', "getPosition was called with invalid road parameter : wrong type");
    REQUIRE(road->properlyInitialized() , "road was not properly initialized when calling getPosition");
    return roads[road];
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

void CrossRoad::simulateCrossroad(bool random , int time) {
    REQUIRE(this->properlyInitialized(), "Crossroad was not properly initialized when calling simulateCrossroad");
    REQUIRE(*typeid(random).name() == 'b', "simulateCrossroad was called with invalid random parameter : wrong type");
    REQUIRE(*typeid(time).name() == 'i', "simulateCrossroad was called with invalid time parameter : wrong type");
    Road* currentRoad;
    Road* newRoad;
    Vehicle* currentVehicle;
    Vehicle* tempVehicle;
    map<Road*,int>::iterator it2;
    double currentPos;
    double distance;
    // switchRoad?
    updateSwitchRoad(random , time);
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
        if (tempVehicle != NULL && roads[newRoad] - (tempVehicle->getVehiclePosition() + tempVehicle->getV_length() ) < tempVehicle->getV_min_followDistance() ){
            it = it2;
            continue;
        }
        else if (switchRoad && distance > 0 &&  distance < currentVehicle->getV_length() ){
            // Move vehicle to different road
            newRoad->addVehicle(currentVehicle);
            currentVehicle->setPosition(roads[newRoad] - distance);
            currentRoad->removeVehicle(currentVehicle);
            setSwitchRoad(false);
        }
        it = it2;
    }

}

CrossRoad::~CrossRoad() {
    REQUIRE(this->properlyInitialized(), "crossroad was not properly initialized when calling destructor");
}
