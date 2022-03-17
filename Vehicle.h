#ifndef TRAFFICSIMULATION2022_VOERTUIG_H
#define TRAFFICSIMULATION2022_VOERTUIG_H

#include "Road.h"
#include <iostream>

using namespace std;

class TrafficLight;


enum vehicleStatus{ max_speed , accelerate , decelerate , stopped };

class Vehicle {
    double speed;
    double position;
    double acceleration;
    double currentMaxSpeed;

    vehicleStatus status;
    Road* road;

public:
    Vehicle(double speed, double position);

    Vehicle();

    double getCurrentMaxSpeed() const;

    void setCurrentMaxSpeed(double newCurrentMaxSpeed);

    double getSpeed() const;

    void setSpeed(double newSpeed);

    double getVehiclePosition() const;

    void setPosition(double newPosition);

    Road* getRoad() const;

    void setRoad(Road *road);

    void calculateNewAcceleration(double maxSpeed);

    void calculateNewSpeed();

    void calculateNewPosition();

    double calculateFollowDistance();

    double calculateSpeedRestriction();

    double calculateSpeedDifference();

    double calculareStopDecelerate();

    Vehicle* getNextVehicle();

    void simulateStop();

    void simulateDecelerate();

    void simulateAccelerate();

    void print();

    virtual ~Vehicle();
};


#endif //TRAFFICSIMULATION2022_VOERTUIG_H
