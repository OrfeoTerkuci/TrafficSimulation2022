#include "TrafficLight.h"
#include "Vehicle.h"
#include "Standard_Values.h"
#include "DesignByContract.h"
#include <typeinfo>

TrafficLight::TrafficLight(unsigned int cyclus, Road *road) : cyclus(cyclus), road(road) , currentColor(red) , init(this) {
    REQUIRE(*typeid(cyclus).name() == 'j' && cyclus >= 0 , "constructor was called with invalid cyclus");
    REQUIRE(*typeid(road).name() == 'P' , "constructor was called with invalid road");
    REQUIRE(road->properlyInitialized() , "constructor was called with invalid road");
    ENSURE(TrafficLight::cyclus == cyclus , "cyclus was not properly initialized");
    ENSURE(TrafficLight::road == road , "road was not properly initialized");
    ENSURE(TrafficLight::currentColor == red , "currentColor was not properly initialized");
    ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
}

TrafficLight::TrafficLight() : road(NULL), currentColor(red) , init(this){
    ENSURE(TrafficLight::currentColor == red , "currentColor was not properly initialized");
    ENSURE(TrafficLight::road == NULL , "road was not properly initialized");
    ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
}

bool TrafficLight::properlyInitialized() {
    return init == this;
}

int TrafficLight::getCyclus() {
    REQUIRE(this->properlyInitialized(), "TrafficSimulation was not initialized when calling getCyclus");
    return cyclus;
}

void TrafficLight::setCyclus(unsigned int newCyclus) {
    REQUIRE(this->properlyInitialized(), "TrafficSimulation was not initialized when calling setCyclus");
    REQUIRE(*typeid(newCyclus).name() == 'j' , "setCyclus was called with invalid parameter");
    TrafficLight::cyclus = newCyclus;
    ENSURE(TrafficLight::cyclus == newCyclus , "setCyclus failed");
}

lightColor TrafficLight::getCurrentColor() {
    REQUIRE(this->properlyInitialized(), "TrafficSimulation was not initialized when calling getCurrentColor");
    return currentColor;
}

void TrafficLight::setCurrentColor(lightColor newColor) {
    REQUIRE(this->properlyInitialized(), "TrafficSimulation was not initialized when calling setCurrentColor");
    REQUIRE( newColor == red || newColor == green , "setCurrentColor was called with invalid parameter");
    TrafficLight::currentColor = newColor;
    ENSURE(TrafficLight::currentColor == newColor , "setCurrentColor failed");
}

Road* TrafficLight::getRoad(){
    REQUIRE(this->properlyInitialized(), "TrafficSimulation was not initialized when calling getRoad");
    return road;
}

void TrafficLight::setRoad(Road* newRoad) {
    REQUIRE(this->properlyInitialized(), "TrafficSimulation was not initialized when calling setRoad");
    REQUIRE(*typeid(newRoad).name() == 'P' , "setRoad was called with invalid parameter");
    REQUIRE(newRoad->properlyInitialized() , "setRoad was called with uninitialized parameter");
    TrafficLight::road = newRoad;
    ENSURE(TrafficLight::road == newRoad , "setRoad failed");
}

unsigned int TrafficLight::getPosition() {
    REQUIRE(this->properlyInitialized(), "TrafficSimulation was not initialized when calling getPosition");
    return position;
}

void TrafficLight::setPosition(unsigned int newPosition) {
    REQUIRE(this->properlyInitialized(), "TrafficSimulation was not initialized when calling setPosition");
    REQUIRE(*typeid(newPosition).name() == 'j' , "setPosition was called with invalid parameter");
    TrafficLight::position = newPosition;
    ENSURE(TrafficLight::position == newPosition , "setPosition failed");
}

Vehicle* TrafficLight::getNearestVehicle() {
    REQUIRE(this->properlyInitialized(), "TrafficSimulation was not initialized when calling getNearestVehicle");
    double pos = this->getPosition();
    Vehicle* nearestVehicle = this->road->getVehicle(0);
    Vehicle* currentVehicle;
    for (int i = 0; i < this->road->getVehicleAmount(); ++i) {
        currentVehicle = this->road->getVehicle(i);
        if (currentVehicle->getVehiclePosition() < pos && currentVehicle->getVehiclePosition() > nearestVehicle->getVehiclePosition()){
            nearestVehicle = currentVehicle;
        }
    }
    return nearestVehicle;
}

void TrafficLight::simulate(int &count) {
    REQUIRE(this->properlyInitialized(), "TrafficSimulation was not initialized when calling simulate");
    REQUIRE(*typeid(count).name() == 'i' , "simulate was called with invalid parameter");
    // Check if the cyclus has been completed
    if (count % this->getCyclus() == 0){
        // Change light color
        this->setCurrentColor(this->getCurrentColor() == green ? red : green);
    }
    Vehicle* currentVehicle;
    if (this->getCurrentColor() == green){
        // Vehicles before the light may accelerate again
        for (int i = 0; i < this->road->getVehicleAmount(); ++i) {
            currentVehicle = this->road->getVehicle(i);
            // Check for bus slowing down or stopping
            if(currentVehicle->isSlowing_bus() || currentVehicle->isStopping_bus()){
                continue;
            }
            if(this->road->getVehicleAmount() > 0 && currentVehicle->getVehiclePosition() + currentVehicle->getV_length()  < this->getPosition()){
                this->road->getVehicle(i)->setStatus(accelerate);
//                currentVehicle->simulate();
            }
        }
    }
    if (this->getCurrentColor() == red){
        currentVehicle = this->getNearestVehicle();
        if ( currentVehicle->getType() != T_AUTO && currentVehicle->getType() != T_BUS){
            return;
        }
        if(currentVehicle->isSlowing_bus() || currentVehicle->isStopping_bus()){
            return;
        }
        if ( (this->position - ( currentVehicle->getVehiclePosition() + currentVehicle->getV_length() ) ) <= STOPPING_DISTANCE){
            if( (this->position - ( currentVehicle->getVehiclePosition() + currentVehicle->getV_length() ) ) >= STOPPING_DISTANCE / 2 ){
                // Stop
                currentVehicle->setStatus(stopping);
            }
            if ( currentVehicle->getStatus() == idle){
                return;
            }
//            currentVehicle->simulate();
        }
        else if ( (this->position - ( currentVehicle->getVehiclePosition() + currentVehicle->getV_length() ) ) <= SLOWING_DISTANCE && currentVehicle->getStatus() != stopping ){
            // Slow down
            currentVehicle->setStatus(decelerate);
//            currentVehicle->simulate();
        }
        else{
            // Clear to accelerate
            currentVehicle->setStatus(accelerate);
//            currentVehicle->simulate();
        }
    }

}

void TrafficLight::print() {
    REQUIRE(this->properlyInitialized(), "TrafficSimulation was not initialized when calling print");
    cout << '\t' << "-> Road: " << this->road->getRoadName() << endl;
    cout << '\t' << "-> Position: " << this->position << endl;
    cout << '\t' << "-> Cycle: " << this->cyclus << endl;
}

TrafficLight::~TrafficLight() {
    REQUIRE(this->properlyInitialized(), "TrafficSimulation was not initialized when calling destructor");
}