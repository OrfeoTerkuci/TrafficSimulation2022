// custom libs
#include "Vehicle.h"
#include "Standard_Values.h"

// build in libs
#include <cmath>

using namespace std;

Vehicle::Vehicle(double speed, double position) : speed(speed), position(position) , acceleration(0.0) {}

Vehicle::Vehicle() : speed(0.0) , position(0.0) , acceleration(0.0) {}

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

void Vehicle::calculateNewAcceleration() {
    if(getNextVehicle() == NULL){
        this->acceleration = MAX_ACCELERATION * (1- pow((this->speed/MAX_SPEED), 4));
    }
    else{
        this->acceleration = MAX_ACCELERATION * (1- pow((this->speed/MAX_SPEED), 4) - pow(this->calculateSpeedRestriction(), 2));
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

void Vehicle::calulateFollowDistance() {

}

double Vehicle::calculateSpeedDifference() {
    return 0;
}

double Vehicle::calculateSpeedRestriction() {
    return (MIN_FOLLOW_DISTANCE + max(0 , this->speed + ((this->speed * this->calculateSpeedDifference())/2* sqrt(MAX_ACCELERATION*MAX_BRAKE_FACTOR))))/this->calulateFollowDistance();
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
