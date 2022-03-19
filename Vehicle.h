#ifndef TRAFFICSIMULATION2022_VOERTUIG_H
#define TRAFFICSIMULATION2022_VOERTUIG_H

#include "Road.h"
#include <iostream>

using namespace std;

class TrafficLight;
class TrafficSimulation;

enum vehicleStatus{ max_speed , accelerate , decelerate , stopping , idle };

class Vehicle {
    double speed;
    double position;
    double acceleration;
    double currentMaxSpeed;

    vehicleStatus status;
    Road* road;
    Vehicle* _initCheck;

public:
    /*
     * ENSURE(properlyInitialized() , "constructor must end in properlyInitialized state");
     */
    Vehicle(double speed, double position);
    /*
     * ENSURE(properlyInitialized() , "constructor must end in properlyInitialized state");
     */
    Vehicle();

    bool properlyInitialized() const;

    /*
     * REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling getCurrentMaxSpeed");
     */
    double getCurrentMaxSpeed() const;

    /*
     * REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling setCurrentMaxSpeed");
     */
    void setCurrentMaxSpeed(double newCurrentMaxSpeed);

    string getStatusString();

    /*
     * REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling getStatus");
     */
    vehicleStatus getStatus() const;

    /*
     * REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling setStatus");
     */
    void setStatus(vehicleStatus status);

    /*
     * REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling getSpeed");
     */
    double getSpeed() const;

    /*
     * REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling setSpeed");
     */
    void setSpeed(double newSpeed);

    /*
     * REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling getVehiclePosition");
     */
    double getVehiclePosition() const;

    /*
     * REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling setPosition");
     */
    void setPosition(double newPosition);

    /*
     * REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling getRoad");
     */
    Road* getRoad() const;

    /*
     * REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling setRoad");
     */
    void setRoad(Road *road);

    /*
     * REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling calculateNewAcceleration");
     */
    void calculateNewAcceleration(double maxSpeed);

    /*
     * REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling calculateNewSpeed");
     */
    void calculateNewSpeed();

    /*
     * REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling calculateNewPosition");
     */
    void calculateNewPosition();

    /*
     * REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling calculateFollowDistance");
     */
    double calculateFollowDistance();

    /*
     * REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling calculateSpeedRestriction");
     */
    double calculateSpeedRestriction();

    /*
     * REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling calculateSpeedDifference");
     */
    double calculateSpeedDifference();

    /*
     * REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling calculateStopDecelerate");
     */
    void calculateStopDecelerate();

    /*
     * REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling getNextVehicle");
     */
    Vehicle* getNextVehicle();

    /*
     * REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling simulateStop");
     */
    void simulateStop();

    /*
     * REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling simulateDecelerate");
     */
    void simulateDecelerate();

    /*
     * REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling simulateAccelerate");
     */
    void simulateAccelerate();

    /*
     * REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling simulate");
     */
    void simulate();

    /*
     * REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling print");
     */
    void print();

    /*
     * REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling destructor");
     */
    virtual ~Vehicle();
};


#endif //TRAFFICSIMULATION2022_VOERTUIG_H
