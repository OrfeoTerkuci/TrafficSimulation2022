#include "BusStop.h"
#include "Vehicle.h"
#include "DesignByContract.h"
#include <typeinfo>

BusStop::BusStop(int new_waitTime, int new_position, Road *new_road) : cooldown(new_waitTime) , waitTime(new_waitTime), position(new_position), road(new_road) , init(this) {
    ENSURE(road == new_road, "road was not correctly initialized");
    ENSURE(cooldown == new_waitTime, "cooldown was not correctly initialized");
    ENSURE(waitTime == new_waitTime , "waitTime was not correctly initialized");
    ENSURE(position == new_position, "position was not correctly initialized");
    ENSURE(properlyInitialized(), "BusStop constructor must end in properlyInitialized state");
}

BusStop::BusStop() : cooldown(0) , waitTime(0), position(0), road(NULL) , init(this) {
    ENSURE(road == NULL, "road was not correctly initialized");
    ENSURE(cooldown == 0, "cooldown was not correctly initialized");
    ENSURE(waitTime == 0 , "waitTime was not correctly initialized");
    ENSURE(position == 0, "position was not correctly initialized");
    ENSURE(properlyInitialized(), "BusStop constructor must end in properlyInitialized state");
}

bool BusStop::properlyInitialized() const {
    return init == this;
}

int BusStop::getCooldown() const {
    REQUIRE(this->properlyInitialized(), "BusStop was not properly initialized when calling getCooldown");
    return cooldown;
}

void BusStop::setCooldown(int new_cooldown) {
    REQUIRE(this->properlyInitialized(), "BusStop was not properly initialized when calling setCooldown");
    REQUIRE( *typeid(new_cooldown).name() == 'i' , "new_cooldown was not an int when calling setCooldown");
    BusStop::cooldown = new_cooldown;
    ENSURE(cooldown == new_cooldown, "cooldown was not assigned to new_cooldown, after calling setCooldown");
}

int BusStop::getWaitTime() const {
    REQUIRE(this->properlyInitialized(), "BusStop was not properly initialized when calling getWaitTime");
    return waitTime;
}

void BusStop::setWaitTime(int newWaitTime) {
    REQUIRE(this->properlyInitialized(), "BusStop was not properly initialized when calling setWaitTime");
    REQUIRE(*typeid(newWaitTime).name() == 'i' , "newWaitTime was not an int when calling setWaitTime");
    BusStop::waitTime = newWaitTime;
    ENSURE(waitTime == newWaitTime, "waitTime was not assigned to newWaitTime, when calling setWaitTime");
}

int BusStop::getPosition() const {
    REQUIRE(this->properlyInitialized(), "BusStop was not properly initialized when calling getPosition");
    return position;
}

void BusStop::setPosition(int newPosition) {
    REQUIRE(this->properlyInitialized(), "BusStop was not properly initialized when calling setPosition");
    BusStop::position = newPosition;
    ENSURE(position == newPosition, "position was not assigned to newPosition, when calling setPosition");
}

Road *BusStop::getRoad() const {
    REQUIRE(this->properlyInitialized(), "BusStop was not properly initialized when calling getRoad");
    return road;
}

void BusStop::setRoad(Road *newRoad) {
    REQUIRE(this->properlyInitialized(), "BusStop was not properly initialized when calling setRoad");
    REQUIRE(newRoad->properlyInitialized(), "road was not properly initialized when calling setRoad");
    BusStop::road = newRoad;
    ENSURE(road == newRoad, "road was not assigned to newRoad, when calling setRoad");
}

Vehicle *BusStop::getNearestBus() const {
    REQUIRE(this->properlyInitialized(), "BusStop was not properly initialized when calling getNearestBus");
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
    REQUIRE(this->properlyInitialized(), "BusStop was not properly initialized when calling simulateBusStop");
    // Get nearest bus type vehicle
    Vehicle* currentVehicle = getNearestBus();
    // If there are no buses , or all have passed the bus stop
    if(currentVehicle == NULL){
        return;
    }
    if(currentVehicle->getType() == T_BUS) {
        // If bus is in bus stop
        if(currentVehicle->getStatus() == idle){
            // Waiting time is over
            if(cooldown < 0){
                currentVehicle->setStatus(accelerate);
                currentVehicle->setSlowing_bus(false);
                currentVehicle->setStopping_bus(false);
                currentVehicle->setLeaving_bus(true);
                cooldown = waitTime;
                ENSURE(cooldown == waitTime, "cooldown wasn't reset");
            }
            else{
                cooldown--;
            }
        }
        // If bus already left
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

BusStop::~BusStop() {
    REQUIRE(this->properlyInitialized(), "BusStop was not properly initialized when calling destructor");
}
