//
// Created by jason on 05/04/2022.
//

#include "BusStop.h"
#include "Vehicle.h"

BusStop::BusStop(int waitTime, int position, Road *road) : cooldown(waitTime) , waitTime(waitTime), position(position), road(road) {}

BusStop::BusStop() : cooldown(0) , waitTime(0), position(0), road(NULL)  {}

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

Vehicle *BusStop::getNearestBus() {
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

BusStop::~BusStop() {

}
