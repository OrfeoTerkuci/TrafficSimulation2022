#ifndef TRAFFICSIMULATION2022_VOERTUIG_H
#define TRAFFICSIMULATION2022_VOERTUIG_H

#include "Road.h"
#include <iostream>

using namespace std;

enum vehicleStatus{ max_speed , accelerate , decelerate , stopped };

class Vehicle {
    double speed;
    double position;
    double acceleration;
    vehicleStatus status;
    Road* road;

public:
    Vehicle(double speed, double position);

    Vehicle();

    double getSpeed() const;

    void setSpeed(double newSpeed);

    double getVehiclePosition() const;

    void setPosition(double newPosition);

    Road* getRoad() const;

    void setRoad(Road *road);

    void calculateNewAcceleration();

    void calculateNewSpeed();

    void calculateNewPosition();

    double calculateFollowDistance();

    double calculateSpeedRestriction();

    double calculateSpeedDifference();

    Vehicle* getNextVehicle();

    void print();

    virtual ~Vehicle();
};


#endif //TRAFFICSIMULATION2022_VOERTUIG_H
