#include "Vehicle.h"

Vehicle::Vehicle(double speed, double position) : speed(speed), position(position) , acceleration(0.0) {}

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

double Vehicle::calculateAcceleration() {
    return 0;
}

double Vehicle::calculateSpeed() {
    return 0;
}

Vehicle::~Vehicle() {

}

Vehicle::Vehicle() {}

Road *Vehicle::getRoad() const {
    return road;
}

void Vehicle::setRoad(Road *newRoad) {
    Vehicle::road = newRoad;
}
