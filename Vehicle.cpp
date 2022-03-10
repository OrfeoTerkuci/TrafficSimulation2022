#include "Vehicle.h"

Vehicle::Vehicle(double speed, double position) : speed(speed), position(position) {}

double Vehicle::getSpeed() const {
    return speed;
}

void Vehicle::setSpeed(double speed) {
    Vehicle::speed = speed;
}

double Vehicle::getPosition() const {
    return position;
}

void Vehicle::setPosition(double position) {
    Vehicle::position = position;
}
