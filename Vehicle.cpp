// custom libs
#include "Vehicle.h"
#include "Standard_Values.h"
#include "DesignByContract.h"
#include <typeinfo>
// build in libs
#include <cmath>

using namespace std;


Vehicle::Vehicle(double speed, double position) : speed(speed), position(position) , acceleration(0.0) , currentMaxSpeed(MAX_SPEED) , _initCheck(this) {
    REQUIRE(*typeid(speed).name() == 'd' , "constructor called with invalid speed parameter");
    REQUIRE(*typeid(position).name() == 'd' , "constructor called with invalid position parameter");
    // Check speed
    if (speed == 0){
        this->status = idle;
    }
    else if (this->acceleration > 0){
        this->status = accelerate;
    }
    else if (this->acceleration < 0){
        this->status = decelerate;
    }
    else {
        this->status = stopping;
    }
    ENSURE(Vehicle::speed == speed , "speed was not properly initialized");
    ENSURE(Vehicle::position == position , "position was not properly initialized");
    ENSURE(Vehicle::acceleration == 0.0 , "acceleration was not properly initialized");
    ENSURE(Vehicle::currentMaxSpeed == MAX_SPEED , "currentMaxSpeed was not properly initialized");
    ENSURE(properlyInitialized() , "constructor must end in properlyInitialized state");
}

Vehicle::Vehicle() : speed(0.0) , position(0.0) , acceleration(0.0) , currentMaxSpeed(MAX_SPEED) , _initCheck(this) {
    ENSURE(Vehicle::speed == 0.0 , "speed was not properly initialized");
    ENSURE(Vehicle::position == 0.0 , "position was not properly initialized");
    ENSURE(Vehicle::acceleration == 0.0 , "acceleration was not properly initialized");
    ENSURE(Vehicle::currentMaxSpeed == MAX_SPEED , "currentMaxSpeed was not properly initialized");
    ENSURE(properlyInitialized() , "constructor must end in properlyInitialized state");
}


bool Vehicle::properlyInitialized() const{
    return _initCheck == this;
}

double Vehicle::getCurrentMaxSpeed() const {
    REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling getCurrentMaxSpeed");
    return currentMaxSpeed;
}

void Vehicle::setCurrentMaxSpeed(double newCurrentMaxSpeed) {
    REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling setCurrentMaxSpeed");
    REQUIRE(*typeid(newCurrentMaxSpeed).name() == 'd' , "setCurrentMaxSpeed was called with invalid parameter : wrong type");
    REQUIRE(newCurrentMaxSpeed >= 0 , "setCurrentMaxSpeed was called with invalid parameter : negative newCurrentMaxSpeed");
    Vehicle::currentMaxSpeed = newCurrentMaxSpeed;
    ENSURE(Vehicle::currentMaxSpeed == currentMaxSpeed , "setCurrentMaxSpeed failed");
}

string Vehicle::getStatusString() {
    REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling getStatusString");
    if (status == accelerate){
        return "Accelerating";
    }
    else if (status == decelerate){
        return "Decelerating";
    }
    else if (status == stopping){
        return "Stopping";
    }
    return "Stopped / Idle";
}

vehicleStatus Vehicle::getStatus() const {
    REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling getStatus");
    return status;
}

void Vehicle::setStatus(vehicleStatus status) {
    REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling setStatus");
    REQUIRE(status == accelerate || status == decelerate || status == stopping || status == idle
            , "setStatus was called with invalid parameter");
    Vehicle::status = status;
    ENSURE(Vehicle::status == status , "setStatus failed");
}

double Vehicle::getSpeed() const {
    REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling getSpeed");
    return speed;
}

void Vehicle::setSpeed(double newSpeed) {
    REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling setSpeed");
    REQUIRE(*typeid(newSpeed).name() == 'd' , "setSpeed was called with invalid parameter : wrong type");
    REQUIRE(newSpeed >= 0 , "setSpeed was called with invalid parameter : negative speed");
    Vehicle::speed = newSpeed;
    ENSURE(Vehicle::speed == newSpeed , "setSpeed failed");
}

double Vehicle::getVehiclePosition() const {
    REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling getVehiclePosition");
    return position;
}

void Vehicle::setPosition(double newPosition) {
    REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling setPosition");
    REQUIRE(*typeid(newPosition).name() == 'd' , "setPosition was called with invalid parameter : wrong type");
    REQUIRE(newPosition >= 0 , "setPosition was called with invalid parameter : negative position");
    Vehicle::position = newPosition;
    ENSURE(Vehicle::position == newPosition , "setPosition failed");
}

double Vehicle::getAcceleration() const {
    REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling getAcceleration");
    return acceleration;
}

void Vehicle::setAcceleration(double newAcceleration) {
    REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling setAcceleration");
    REQUIRE(*typeid(newAcceleration).name() == 'd' , "setAcceleration was called with invalid parameter");
    Vehicle::acceleration = newAcceleration;
    ENSURE(Vehicle::acceleration == newAcceleration , "setAcceleration failed");
}

Road* Vehicle::getRoad() const {
    REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling getRoad");
    return road;
}

void Vehicle::setRoad(Road *newRoad) {
    REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling setRoad");
    REQUIRE(*typeid(newRoad).name() == 'P' , "setRoad was called with invalid parameter");
    REQUIRE(newRoad->properlyInitialized() , "setRoad was called with uninitialized parameter");
    Vehicle::road = newRoad;
    ENSURE(Vehicle::road == newRoad , "setRoad failed");
}

void Vehicle::calculateNewAcceleration(double maxSpeed = MAX_SPEED) {
    REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling calculateNewAcceleration");
    REQUIRE(*typeid(maxSpeed).name() == 'd' , "calculateNewAcceleration was called with invalid parameter : wrong type");
    REQUIRE(maxSpeed >= 0 , "calculateNewAcceleration was called with invalid parameter : negative maxSpeed");
    setCurrentMaxSpeed(maxSpeed);
    if(getNextVehicle() == NULL){
        setAcceleration(MAX_ACCELERATION * (1- pow((this->speed/this->currentMaxSpeed), 4)));
    }
    else{
        setAcceleration(MAX_ACCELERATION * (1- pow((this->speed/this->currentMaxSpeed), 4) - pow(this->calculateSpeedRestriction(), 2)));
    }
}

void Vehicle::calculateNewSpeed() {
    REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling calculateNewSpeed");
    double tempSpeed = this->speed + this->acceleration * SIMULATION_TIME;

    if (tempSpeed > 0){
        setSpeed(tempSpeed);
        //ENSURE(Vehicle::speed == tempSpeed , "calculateNewSpeed failed");
        setPosition(this->position + this->speed * SIMULATION_TIME + this->acceleration * (pow(SIMULATION_TIME,2) / 2));
    }
    else{
        calculateNewPosition();
    }
}

void Vehicle::calculateNewPosition() {
    REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling calculateNewPosition");
    setPosition(this->position - (pow(this->speed, 2) / 2 * acceleration));
    setSpeed(0);
    //ENSURE(Vehicle::speed == 0.0 , "calculateNewPosition failed");
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
    setAcceleration(-(MAX_BRAKE_FACTOR * this->speed)/(MAX_SPEED));
}

Vehicle* Vehicle::getNextVehicle() {
    REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling getNextVehicle");

    if(this->road == NULL || this->road->getVehicleAmount() <= 1){
        return NULL;
    }
    else{
        Vehicle* nextVehicle;
        Vehicle* currentVehicle;
        nextVehicle = this->road->getVehicle(0);
        double oldPosition = this->getVehiclePosition();
        for(int i = 1; i < this->road->getVehicleAmount(); ++i){
            currentVehicle = this->road->getVehicle(i);
            if(currentVehicle->getVehiclePosition() > oldPosition && currentVehicle->getVehiclePosition() <= nextVehicle->getVehiclePosition()){
                nextVehicle = currentVehicle;
            }
        }
        return nextVehicle->getVehiclePosition() == oldPosition ? NULL : nextVehicle;
    }

}

void Vehicle::simulateStop() {
    REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling simulateStop");
    this->calculateStopDecelerate();
    this->calculateNewSpeed();
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
    // Check status of vehicle

    if (status == decelerate){
        simulateDecelerate();
    }
    else if (status == stopping){
        simulateStop();
        // Update status
        setStatus(speed == 0 && acceleration == 0 ? idle : stopping);
    }
    else if (status == accelerate){
        simulateAccelerate();
        // Update status
        setStatus(accelerate);
    }


}

void Vehicle::print() {
    REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling print");
    cout << '\t' << "-> Road: " << this->road->getRoadName() << endl;
    cout << '\t' << "-> Position: " << this->position << endl;
    cout << '\t' << "-> Speed: " << this->speed << endl;
    cout << '\t' << "-> Acceleration: " << this->acceleration << endl;

    cout << '\t' << "-> Status: " << this->getStatusString() << endl;

    cout << endl;
}

Vehicle::~Vehicle() {
    REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling destructor");

}

const string &Vehicle::getType() const {
    return type;
}

void Vehicle::setType(const string &type) {
    Vehicle::type = type;
}
