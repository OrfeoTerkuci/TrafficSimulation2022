#ifndef TRAFFICSIMULATION2022_VOERTUIG_H
#define TRAFFICSIMULATION2022_VOERTUIG_H

#include "Road.h"
#include <iostream>

using namespace std;
class Vehicle {
    double speed;
    double position;
    double acceleration;

    Road* road;

public:
    Vehicle(double speed, double position);

    Vehicle();

    double getSpeed() const;

    void setSpeed(double newSpeed);

    double getPosition() const;

    void setPosition(double newPosition);

    Road* getRoad() const;

    void setRoad(Road *road);

    void calculateNewAcceleration();

    void calculateNewSpeed();

    void calculateNewPosition();

    void calulateFollowDistance();

    double calculateSpeedRestriction();

    Vehicle* getNextVehicle();

    void print();

    virtual ~Vehicle();
};


#endif //TRAFFICSIMULATION2022_VOERTUIG_H
