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

int BusStop::getWaitTime() const {
    REQUIRE(this->properlyInitialized(), "Bus stop was not properly initialized when calling getWaitTime");
    return waitTime;
}

void BusStop::setWaitTime(int newWaitTime) {
    REQUIRE(this->properlyInitialized(), "Bus stop was not properly initialized when calling setWaitTime");
    BusStop::waitTime = newWaitTime;
    ENSURE(waitTime == newWaitTime, "waitTime was not assigned to newWaitTime, when calling setWaitTime");
}

int BusStop::getPosition() const {
    REQUIRE(this->properlyInitialized(), "Bus stop was not properly initialized when calling getPosition");
    return position;
}

void BusStop::setPosition(int newPosition) {
    REQUIRE(this->properlyInitialized(), "Bus stop was not properly initialized when calling setPosition");
    BusStop::position = newPosition;
    ENSURE(position == newPosition, "position was not assigned to newPosition, when calling setPosition");
}

Road *BusStop::getRoad() {
    REQUIRE(this->properlyInitialized(), "Bus stop was not properly initialized when calling getRoad");
    return road;
}

void BusStop::setRoad(Road *newRoad) {
    REQUIRE(this->properlyInitialized(), "Bus stop was not properly initialized when calling setRoad");
    REQUIRE(newRoad->properlyInitialized(), "road was not properly initialized when calling setRoad");
    BusStop::road = newRoad;
    ENSURE(road == newRoad, "road was not assigned to newRoad, when calling setRoad");
}

int BusStop::getCooldown() const {
    return cooldown;
}

void BusStop::setCooldown(int cooldown) {
    BusStop::cooldown = cooldown;
}

Vehicle *BusStop::getNearestBus() {
    REQUIRE(this->properlyInitialized(), "Bus stop was not properly initialized when calling getNearestBus");
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
            if(cooldown < 0){
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
