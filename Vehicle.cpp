// custom libs
#include "Vehicle.h"
#include "Standard_Values.h"
#include "DesignByContract.h"

// build in libs
#include <cmath>

using namespace std;


Vehicle::Vehicle(double speed, double position) : speed(speed), position(position) , acceleration(0.0) {}

Vehicle::Vehicle() : speed(0.0) , position(0.0) , acceleration(0.0) {}

double Vehicle::getCurrentMaxSpeed() const {
    return currentMaxSpeed;
}

void Vehicle::setCurrentMaxSpeed(double newCurrentMaxSpeed) {
    Vehicle::currentMaxSpeed = newCurrentMaxSpeed;
}

double Vehicle::getSpeed() const {
    return speed;
}

void Vehicle::setSpeed(double newSpeed) {
    Vehicle::speed = newSpeed;
}

double Vehicle::getPosition() const {
    return position;
}

void Vehicle::setPosition(double newPosition) {
    Vehicle::position = newPosition;
}

Road* Vehicle::getRoad() const {
    return road;
}

void Vehicle::setRoad(Road *newRoad) {
    Vehicle::road = newRoad;
}

void Vehicle::calculateNewAcceleration(double maxSpeed = MAX_SPEED) {
    currentMaxSpeed = maxSpeed;
    if(getNextVehicle() == NULL){
        this->acceleration = MAX_ACCELERATION * (1- pow((this->speed/this->currentMaxSpeed), 4));
    }
    else{
        this->acceleration = MAX_ACCELERATION * (1- pow((this->speed/this->currentMaxSpeed), 4) - pow(this->calculateSpeedRestriction(), 2));
    }
}

void Vehicle::calculateNewSpeed() {
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
    this->position = this->position - (pow(this->speed, 2) / 2 * acceleration);
    this->speed = 0;
}

Vehicle* Vehicle::getNextVehicle() {

    if(this->road->getVehicleAmount() <= 1){
        return NULL;
    }
    else{
        Vehicle* nextVehicle;
        nextVehicle = new Vehicle(0 , this->getPosition());
        double oldPosition = this->getPosition();
        for(int i = 0; i < this->road->getVehicleAmount(); ++i){
            Vehicle* currentVehicle = this->road->getVehicle(i);
            if(currentVehicle->getPosition() > oldPosition && currentVehicle->getPosition() <= nextVehicle->getPosition()){
                nextVehicle = currentVehicle;
            }
        }
        return nextVehicle->getPosition() == oldPosition ? NULL : nextVehicle;
    }

}

double Vehicle::calculateFollowDistance() {
    if(this->getNextVehicle() == NULL){
        return 0;
    }
    return abs(this->getPosition() - this->getNextVehicle()->getPosition());
}

double Vehicle::calculateSpeedDifference() {
    if(this->getNextVehicle() == NULL){
        return 0;
    }
    return abs(this->getSpeed() - this->getNextVehicle()->getSpeed());
}

double Vehicle::calculateSpeedRestriction() {
    return (MIN_FOLLOW_DISTANCE + max(0.0 , this->speed + ((this->speed * this->calculateSpeedDifference())/2* sqrt(MAX_ACCELERATION*MAX_BRAKE_FACTOR))))/this->calculateFollowDistance();
}

double Vehicle::calculareStopDecelerate() {
    this->acceleration = -(MAX_BRAKE_FACTOR * this->speed)/(MAX_SPEED)
}

void Vehicle::simulateStop() {
    lightColor color = trafficLight->getCurrentColor();

    if (color == red and trafficLight->getPosition() - this->getPosition() <= 50){
        if (trafficLight->getPosition() - this->getPosition() <= 15){
            this->speed = 0;
            this->acceleration = 0;
        }
        else{
            this->calculateNewAcceleration(DECELERATE);
            this->calculateNewSpeed();
        }
    }
    else{
        this->calculateNewAcceleration();
        this->calculateNewSpeed();
    }
}

void Vehicle::print() {
    cout << "Vehicle specifications:" << endl;
    cout << '\t' << "Road: " << this->road->getRoadName() << endl;
    cout << '\t' << "Position: " << this->position << endl;
    cout << '\t' << "Speed: " << this->speed << endl;
    cout << '\t' << "Acceleration: " << this->acceleration << endl;
}

Vehicle::~Vehicle() {

}
