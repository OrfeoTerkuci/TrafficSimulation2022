// custom libs
#include "Vehicle.h"
#include "Standard_Values.h"
#include "DesignByContract.h"

// build in libs
#include <cmath>

using namespace std;


Vehicle::Vehicle(double speed, double position) : speed(speed), position(position) , acceleration(0.0) , _initCheck(this) {
    ENSURE(properlyInitialized() , "constructor must end in properlyInitialized state");
}

Vehicle::Vehicle() : speed(0.0) , position(0.0) , acceleration(0.0) , _initCheck(this) {
    ENSURE(properlyInitialized() , "constructor must end in properlyInitialized state");
}


bool Vehicle::properlyInitialized() const{
    return _initCheck == this;
}

double Vehicle::getCurrentMaxSpeed() const {
    return currentMaxSpeed;
}

void Vehicle::setCurrentMaxSpeed(double newCurrentMaxSpeed) {
    REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling setCurrentMaxSpeed");
    Vehicle::currentMaxSpeed = newCurrentMaxSpeed;
}

double Vehicle::getSpeed() const {
    REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling getSpeed");
    return speed;
}

void Vehicle::setSpeed(double newSpeed) {
    REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling setSpeed");
    Vehicle::speed = newSpeed;
}

double Vehicle::getVehiclePosition() const {
    REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling getVehiclePosition");
    return position;
}

void Vehicle::setPosition(double newPosition) {
    REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling setPosition");
    Vehicle::position = newPosition;
}

Road* Vehicle::getRoad() const {
    REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling getRoad");
    return road;
}

void Vehicle::setRoad(Road *newRoad) {
    REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling setRoad");
    Vehicle::road = newRoad;
}

void Vehicle::calculateNewAcceleration(double maxSpeed = MAX_SPEED) {
    REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling calculateNewAcceleration");
    this->currentMaxSpeed = maxSpeed;
    if(getNextVehicle() == NULL){
        this->acceleration = MAX_ACCELERATION * (1- pow((this->speed/this->currentMaxSpeed), 4));
    }
    else{
        this->acceleration = MAX_ACCELERATION * (1- pow((this->speed/this->currentMaxSpeed), 4) - pow(this->calculateSpeedRestriction(), 2));
    }
}

void Vehicle::calculateNewSpeed() {
    REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling calculateNewSpeed");
    double tempSpeed = this->speed + this->acceleration * SIMULATION_TIME;

    if (tempSpeed > 0){
        this->speed = tempSpeed;
        this->position = this->position + this->speed * SIMULATION_TIME + this->acceleration * (pow(SIMULATION_TIME,2) / 2);
    }
    else{
        calculateNewPosition();
    }
}

void Vehicle::calculateNewPosition() {
    REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling calculateNewPosition");
    this->position = this->position - (pow(this->speed, 2) / 2 * acceleration);
    this->speed = 0;
}

double Vehicle::calculateFollowDistance() {
    REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling calculateFollowDistance");
    if(this->getNextVehicle() == NULL){
        return 0;
    }
    return abs(this->getVehiclePosition() - this->getNextVehicle()->getVehiclePosition());
}

double Vehicle::calculateSpeedRestriction() {
    REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling calculateSpeedRestriction");
    return (MIN_FOLLOW_DISTANCE + max(0.0 , this->speed + ((this->speed * this->calculateSpeedDifference())/2* sqrt(MAX_ACCELERATION*MAX_BRAKE_FACTOR))))/this->calculateFollowDistance();
}

double Vehicle::calculateSpeedDifference() {
    REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling calculateSpeedDifference");
    if(this->getNextVehicle() == NULL){
        return 0;
    }
    return abs(this->getSpeed() - this->getNextVehicle()->getSpeed());
}

void Vehicle::calculateStopDecelerate() {
    REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling calculateStopDecelerate");
    this->acceleration = -(MAX_BRAKE_FACTOR * this->speed)/(MAX_SPEED);
}

Vehicle* Vehicle::getNextVehicle() {
    REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling getNextVehicle");

    if(this->road->getVehicleAmount() <= 1){
        return NULL;
    }
    else{
        Vehicle* nextVehicle;
        nextVehicle = new Vehicle(0 , this->getVehiclePosition());
        double oldPosition = this->getVehiclePosition();
        for(int i = 0; i < this->road->getVehicleAmount(); ++i){
            Vehicle* currentVehicle = this->road->getVehicle(i);
            if(currentVehicle->getVehiclePosition() > oldPosition && currentVehicle->getVehiclePosition() <= nextVehicle->getVehiclePosition()){
                nextVehicle = currentVehicle;
            }
        }
        return nextVehicle->getVehiclePosition() == oldPosition ? NULL : nextVehicle;
    }

}

void Vehicle::simulateStop() {
    REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling simulateStop");

}

void Vehicle::simulateDecelerate() {
    REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling simulateDecelerate");
    this->calculateNewAcceleration(DECELERATE);
    this->calculateNewSpeed();
}

void Vehicle::simulateAccelerate() {
    REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling simulateAccelerate");
    this->calculateNewAcceleration();
    this->calculateNewSpeed();
}

void Vehicle::simulate() {
    REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling simulate");

}

void Vehicle::print() {
    REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling print");
    cout << "Vehicle specifications:" << endl;
    cout << '\t' << "Road: " << this->road->getRoadName() << endl;
    cout << '\t' << "Position: " << this->position << endl;
    cout << '\t' << "Speed: " << this->speed << endl;
    cout << '\t' << "Acceleration: " << this->acceleration << endl;
}

Vehicle::~Vehicle() {
    REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling destructor");

}
