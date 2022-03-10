#include "Vehicle.h"

Vehicle::Vehicle(double speed, double position) : speed(speed), position(position) {}

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

Vehicle::~Vehicle() {

}
