#include "BusStop.h"
#include "Vehicle.h"
#include "DesignByContract.h"

BusStop::BusStop(int waitTime, int position, Road *road) : cooldown(waitTime) , waitTime(waitTime), position(position), road(road) {
    init = this;
    ENSURE(init == this, "init is not itself, when calling constructor");
}

BusStop::BusStop() : cooldown(0) , waitTime(0), position(0), road(NULL)  {
    init = this;
    ENSURE(init == this, "init is not itself, when calling constructor");
}

int BusStop::getWaitTime() {
    REQUIRE(this->properlyInitialized(), "Busstop was not properly initialized when calling getWaitTime");
    return waitTime;
}

void BusStop::setWaitTime(int newWaitTime) {
    REQUIRE(this->properlyInitialized(), "Busstop was not properly initialized when calling setWaitTime");
    BusStop::waitTime = newWaitTime;
}

int BusStop::getPosition() {
    REQUIRE(this->properlyInitialized(), "Busstop was not properly initialized when calling getPosition");
    return position;
}

void BusStop::setPosition(int newPosition) {
    REQUIRE(this->properlyInitialized(), "Busstop was not properly initialized when calling setPosition");
    BusStop::position = newPosition;
}

Road *BusStop::getRoad()  {
    REQUIRE(this->properlyInitialized(), "Busstop was not properly initialized when calling getRoad");
    return road;
}

void BusStop::setRoad(Road *newRoad) {
    REQUIRE(this->properlyInitialized(), "Busstop was not properly initialized when calling setRoad");
    REQUIRE(road->properlyInitialized(), "road was not properly initialized when calling setRoad");
    BusStop::road = newRoad;
}

Vehicle *BusStop::getNearestBus() {
    REQUIRE(this->properlyInitialized(), "Busstop was not properly initialized when calling getNearestBus");
    double pos = this->getPosition();
    Vehicle* nearestVehicle = NULL;
    Vehicle* currentVehicle;
    // Get bus type vehicles
    vector<Vehicle*> buses;
    for (int j = 0; j < this->road->getVehicleAmount(); ++j) {
        currentVehicle = this->road->getVehicle(j);
        // Check for correct type
        if(currentVehicle->getType() == T_BUS && currentVehicle->getVehiclePosition() < pos){
            buses.push_back(currentVehicle);
            // Update nearest vehicle
            if(buses.size() == 1){
                nearestVehicle = currentVehicle;
            }
            else if(nearestVehicle->getVehiclePosition() < currentVehicle->getVehiclePosition()){
                nearestVehicle = currentVehicle;
            }
        }
    }
    return nearestVehicle;
}

void BusStop::simulateBusStop() {
    REQUIRE(this->properlyInitialized(), "Busstop was not properly initialized when calling simulateBusStop");
    // Declare variables
    Vehicle* currentVehicle = getNearestBus();
    if(currentVehicle == NULL){
        return;
    }
    if(currentVehicle->getType() == T_BUS) {
        // Check cooldown
        if(currentVehicle->getStatus() == idle){
            if(cooldown == 0){
                currentVehicle->setStatus(accelerate);
                currentVehicle->setSlowing_bus(false);
                currentVehicle->setStopping_bus(false);
                currentVehicle->setLeaving_bus(true);
                cooldown = waitTime;
            }
            else{
                cooldown--;
            }
        }
        if(currentVehicle->isLeaving_bus()){
            return;
        }
        // Check if within stopping distance
        if (position - ( currentVehicle->getVehiclePosition() + currentVehicle->getV_length() ) < STOPPING_DISTANCE && !currentVehicle->isStopping_bus() ) {
            currentVehicle->setStatus(stopping);
            currentVehicle->setStopping_bus(true);
            currentVehicle->setSlowing_bus(false);
        }
        // check if within slowing distance
        else if (position - ( currentVehicle->getVehiclePosition() + currentVehicle->getV_length() ) < SLOWING_DISTANCE && !( currentVehicle->isStopping_bus() || currentVehicle->isSlowing_bus() ) ) {
            currentVehicle->setStatus(decelerate);
            currentVehicle->setSlowing_bus(true);
            currentVehicle->setStopping_bus(false);
        }
    }
}

bool BusStop::properlyInitialized() const {
    return init == this;
}

BusStop::~BusStop() {
    REQUIRE(this->properlyInitialized(), "Busstop was not properly initialized when calling destructor");
}
