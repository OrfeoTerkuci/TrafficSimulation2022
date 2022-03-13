#ifndef TRAFFICSIMULATION2022_VOERTUIG_H
#define TRAFFICSIMULATION2022_VOERTUIG_H

#include "Road.h"

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

    double calculateAcceleration();

    double calculateSpeed();

    virtual ~Vehicle();

    Road *getRoad() const;

    void setRoad(Road *road);

    void print();
};


#endif //TRAFFICSIMULATION2022_VOERTUIG_H
