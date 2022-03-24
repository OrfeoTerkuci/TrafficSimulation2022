#ifndef TRAFFICSIMULATION2022_VOERTUIG_H
#define TRAFFICSIMULATION2022_VOERTUIG_H

#include "Road.h"
#include <iostream>

using namespace std;

class TrafficLight;
class TrafficSimulation;

enum vehicleStatus{ accelerate , decelerate , stopping , idle };

class Vehicle {
    double speed;
    double position;
    double acceleration;
    double currentMaxSpeed;

    vehicleStatus status;
    Road* road;
    Vehicle* _initCheck;

public:
    /**
     * REQUIRE(*typeid(speed).name() == 'd' , "constructor called with invalid speed parameter");
     * REQUIRE(*typeid(position).name() == 'd' , "constructor called with invalid position parameter");
     * ENSURE(Vehicle::speed == speed , "speed was not properly initialized");
     * ENSURE(Vehicle::position == position , "position was not properly initialized");
     * ENSURE(Vehicle::acceleration == 0.0 , "acceleration was not properly initialized");
     * ENSURE(Vehicle::currentMaxSpeed == MAX_SPEED , "currentMaxSpeed was not properly initialized");
     * ENSURE(properlyInitialized() , "constructor must end in properlyInitialized state");
     * @param speed The speed of the vehicle
     * @param position The position of the vehicle on the road
     */
    Vehicle(double speed, double position);
    /**
     * ENSURE(Vehicle::speed == 0.0 , "speed was not properly initialized");
     * ENSURE(Vehicle::position == 0.0 , "position was not properly initialized");
     * ENSURE(Vehicle::acceleration == 0.0 , "acceleration was not properly initialized");
     * ENSURE(Vehicle::currentMaxSpeed == MAX_SPEED , "currentMaxSpeed was not properly initialized");
     * ENSURE(properlyInitialized() , "constructor must end in properlyInitialized state");
     */
    Vehicle();

    bool properlyInitialized() const;

    /**
     * REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling getCurrentMaxSpeed");
     * @return Current MAX_SPEED modifier of the vehicle
     */
    double getCurrentMaxSpeed() const;

    /**
     * REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling setCurrentMaxSpeed");
     * REQUIRE(*typeid(newCurrentMaxSpeed).name() == 'd' , "setCurrentMaxSpeed was called with invalid parameter : wrong type");
     * REQUIRE(newCurrentMaxSpeed >= 0 , "setCurrentMaxSpeed was called with invalid parameter : negative newCurrentMaxSpeed");
     * ENSURE(Vehicle::currentMaxSpeed == currentMaxSpeed , "setCurrentMaxSpeed failed");
     */
    void setCurrentMaxSpeed(double newCurrentMaxSpeed);

    /**
     * REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling getStatusString");
     * @return The status of the vehicle as a string 
     */
    string getStatusString();

    /**
     * REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling getStatus");
     * @return The status of the vehicle
     */
    vehicleStatus getStatus() const;

    /**
     * REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling setStatus");
     * REQUIRE(status == accelerate || status == decelerate || status == stopping || status == idle , "setStatus was called with invalid parameter");
     * ENSURE(Vehicle::status == status , "setStatus failed");
     * @param status A vehicleStatus type object
     */
    void setStatus(vehicleStatus status);

    /**
     * REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling getSpeed");
     * @return The speed of the vehicle
     */
    double getSpeed() const;

    /**
     * REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling setSpeed");
     * REQUIRE(*typeid(newSpeed).name() == 'd' , "setSpeed was called with invalid parameter : wrong type");
     * REQUIRE(newSpeed >= 0 , "setSpeed was called with invalid parameter : negative speed");
     * ENSURE(Vehicle::speed == newSpeed , "setSpeed failed");
     * @param newSpeed The new speed of the vehicle
     */
    void setSpeed(double newSpeed);

    /**
     * REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling getAcceleration");
     * @return The acceleration of the vehicle
     */
    double getAcceleration() const;

    /**
     * REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling setAcceleration");
     * REQUIRE(*typeid(newAcceleration).name() == 'd' , "setAcceleration was called with invalid parameter");
     * ENSURE(Vehicle::acceleration == newAcceleration , "setAcceleration failed");
     * @param newAcceleration The new acceleration of the vehicle
     */
    void setAcceleration(double newAcceleration);

    /**
     * REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling getVehiclePosition");
     * @return The position of the vehicle on the road
     */
    double getVehiclePosition() const;

    /**
     * REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling setPosition");
     * REQUIRE(*typeid(newPosition).name() == 'd' , "setPosition was called with invalid parameter : wrong type");
     * REQUIRE(newPosition >= 0 , "setPosition was called with invalid parameter : negative position");
     * ENSURE(Vehicle::position == newPosition , "setPosition failed");
     */
    void setPosition(double newPosition);

    /**
     * REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling getRoad");
     * @return A pointer to the road the vehicle is on
     */
    Road* getRoad() const;

    /**
     * REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling setRoad");
     * REQUIRE(*typeid(newRoad).name() == 'P' , "setRoad was called with invalid parameter");
     * REQUIRE(newRoad->properlyInitialized() , "setRoad was called with uninitialized parameter");
     * ENSURE(Vehicle::road == newRoad , "setRoad failed");
     * @param newRoad A pointer to a Road class object
     */
    void setRoad(Road *newRoad);

    /**
     * REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling calculateNewAcceleration");
     * REQUIRE(*typeid(maxSpeed).name() == 'd' , "calculateNewAcceleration was called with invalid parameter");
     * REQUIRE(maxSpeed >= 0 , "calculateNewAcceleration was called with invalid parameter : negative maxSpeed");
     * @param maxSpeed The MAX_SPEED modifier of the vehicle
     */
    void calculateNewAcceleration(double maxSpeed);

    /**
     * REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling calculateNewSpeed");
     * ENSURE(Vehicle::speed == tempSpeed , "calculateNewSpeed failed");
     */
    void calculateNewSpeed();

    /**
     * REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling calculateNewPosition");
     * ENSURE(Vehicle::speed == 0.0 , "calculateNewPosition failed");
     */
    void calculateNewPosition();

    /**
     * REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling calculateFollowDistance");
     * 
     */
    double calculateFollowDistance();

    /**
     * REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling calculateSpeedRestriction");
     */
    double calculateSpeedRestriction();

    /**
     * REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling calculateSpeedDifference");
     */
    double calculateSpeedDifference();

    /**
     * REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling calculateStopDecelerate");
     */
    void calculateStopDecelerate();

    /**
     * REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling getNextVehicle");
     * 
     */
    Vehicle* getNextVehicle();

    /**
     * REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling simulateStop");
     */
    void simulateStop();

    /**
     * REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling simulateDecelerate");
     */
    void simulateDecelerate();

    /**
     * REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling simulateAccelerate");
     */
    void simulateAccelerate();

    /**
     * REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling simulate");
     */
    void simulate();

    /**
     * REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling print");
     */
    void print();

    /**
     * REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling destructor");
     */
    virtual ~Vehicle();
};


#endif //TRAFFICSIMULATION2022_VOERTUIG_H
