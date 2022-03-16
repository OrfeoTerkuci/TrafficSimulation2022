#include "Vehicle.h"

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

double Vehicle::calculateAcceleration() {
    return 0;
}

double Vehicle::calculateSpeed() {
    return 0;
}

Road *Vehicle::getRoad() const {
    return road;
}

void Vehicle::setRoad(Road *newRoad) {
    Vehicle::road = newRoad;
}

void Vehicle::print() {
    cout << "Vehicle specifications:" << endl;
    cout << '\t' << "Name: " << this->road->getRoadName() << endl;
    cout << '\t' << "Position: " << this->position << endl;
    cout << '\t' << "Speed: " << this->speed << endl;
    cout << '\t' << "Acceleration: " << this->acceleration << endl;
}

Vehicle::~Vehicle() {

}
