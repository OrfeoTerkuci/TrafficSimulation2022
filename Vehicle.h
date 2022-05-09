#ifndef TRAFFICSIMULATION2022_VOERTUIG_H
#define TRAFFICSIMULATION2022_VOERTUIG_H

#include "Road.h"
#include "Standard_Values.h"
#include <iostream>

using namespace std;

class TrafficLight;
class TrafficSimulation;

class Vehicle {
    // Standard members
    double speed;
    double position;
    double acceleration;
    double currentMaxSpeed;
    // Type specific members
    vehicleType type;
    double v_length;
    double v_max_speed;
    double v_max_acceleration;
    double v_max_brakefactor;
    double v_min_followDistance;
    double v_decelerate;
    // Bus specific members
    bool slowing_bus;
    bool stopping_bus;
    bool leaving_bus;
    vehicleStatus status;
    Road* road;
    Vehicle* _initCheck;
public:

    void setStandardValues();
    const vehicleType &getType() const;

    string getTypeString() const;

    void setType(const vehicleType &newType);
    /**
     * REQUIRE(*typeid(speed).name() == 'd' , "constructor called with invalid speed parameter");
     * REQUIRE(*typeid(position).name() == 'd' , "constructor called with invalid position parameter");
     * ENSURE(Vehicle::speed == speed , "speed was not properly initialized");
     * ENSURE(Vehicle::position == position , "position was not properly initialized");
     * ENSURE(Vehicle::acceleration == 0.0 , "acceleration was not properly initialized");
     * ENSURE(Vehicle::currentMaxSpeed == v_max_speed , "currentMaxSpeed was not properly initialized");
     * ENSURE(Vehicle::type == type , "vehicleType was not properly initialized");
     * ENSURE(!Vehicle::slowing_bus , "slowing_bus was not properly initialized");
     * ENSURE(!Vehicle::stopping_bus, "stopping_bus was not properly initialized");
     * ENSURE(!Vehicle::leaving_bus, "leaving_bus was not properly initialized");
     * ENSURE(Vehicle::road == NULL , "road was not properly initialized");
     * ENSURE(properlyInitialized() , "constructor must end in properlyInitialized state");
     * @param speed The speed of the vehicle
     * @param position The position of the vehicle on the road
     * @param type The vehicle type
     */
    Vehicle(double speed, double position , vehicleType type = T_AUTO);
    /**
     * ENSURE(Vehicle::speed == 0.0 , "speed was not properly initialized");
     * ENSURE(Vehicle::position == 0.0 , "position was not properly initialized");
     * ENSURE(Vehicle::acceleration == 0.0 , "acceleration was not properly initialized");
     * ENSURE(Vehicle::currentMaxSpeed == v_max_speed , "currentMaxSpeed was not properly initialized");
     * ENSURE(Vehicle::type == T_AUTO , "vehicleType was not properly initialized");
     * ENSURE(!Vehicle::slowing_bus , "slowing_bus was not properly initialized");
     * ENSURE(!Vehicle::stopping_bus, "stopping_bus was not properly initialized");
     * ENSURE(!Vehicle::leaving_bus, "leaving_bus was not properly initialized");
     * ENSURE(Vehicle::road == NULL , "road was not properly initialized");
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
    void setStatus(vehicleStatus newStatus);

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
    virtual void calculateNewAcceleration(double maxSpeed);

    /**
     * REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling getV_length");*/
    double getV_length() const;

    /**
     * REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling setV_length");
     * ENSURE(v_length == new_v_length, "v_length was not assigned to new_v_length, after calling setV_length");*/
    void setV_length(double new_v_length);

    /**
     * REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling getV_max_speed");*/
    double getV_max_speed() const;

    /**
     * REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling setV_max_speed");
     * ENSURE(v_max_speed == new_v_max_speed, "v_max_speed was not assigned to new_v_max_speed, after calling setV_max_speed");*/
    void setV_max_speed(double new_v_max_speed);

    /**
     * REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling getV_max_acceleration");*/
    double getV_max_acceleration() const;

    /**
     * REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling setV_max_acceleration");
     * ENSURE(v_max_acceleration == new_v_max_acceleration, "v_max_acceleration was not assigned to new_v_max_acceleration, after calling setV_max_acceleration");*/
    void setV_max_acceleration(double new_v_max_acceleration);

    /**
     * REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling getV_max_brakefactor");*/
    double getV_max_brakefactor() const;

    /**
     * REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling setV_max_brakefactor");
     * ENSURE(v_max_brakefactor == new_v_max_brakefactor, "v_max_brakefactor was not assigned to new_v_max_brakefactor, after calling setV_max_brakefactor");*/
    void setV_max_brakefactor(double new_v_max_brakefactor);

    /**
     * REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling getV_min_followDistance");*/
    double getV_min_followDistance() const;

    /**
     * REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling setV_min_followDistance");
     * ENSURE(v_min_followDistance == new_v_min_followDistance, "followDistance was not assigned to new followDistance, after calling setV_min_followDistance");*/
    void setV_min_followDistance(double new_v_min_followDistance);

    /**
     * REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling getV_decelerate");*/
    double getV_decelerate() const;

    /**
     * REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling setV_decelerate");
     * ENSURE(v_decelerate == new_v_decelerate, "decelerate of vehicle was not assigende to new decelerate, after calling setV_decelerate");*/
    void setV_decelerate(double new_v_decelerate);

    /**
     * REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling isSlowing_bus");*/
    bool isSlowing_bus() const;

    /**
     * REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling setSlowing_bus");
     * ENSURE(slowing_bus == new_slowing_bus, "slowing bus was not assigned to new slowing bus, after calling setSlowing_bus");*/
    void setSlowing_bus(bool new_slowing_bus);

    /**
     * REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling isStopping_bus");*/
    bool isStopping_bus() const;

    /**
     * REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling setStopping_bus");
     * ENSURE(stopping_bus == new_stopping_bus, "stopping bus was not assigned to new stopping bus, after calling setStopping_bus");*/
    void setStopping_bus(bool new_stopping_bus);

    /**
     * REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling isLeaving_bus");*/
    bool isLeaving_bus() const;

    /**
     * REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling setLeaving_bus");
     * ENSURE(leaving_bus == new_leaving_bus, "leaving bus was not assigend to new leaving bus, after calling setLeaving_bus");*/
    void setLeaving_bus(bool new_leaving_bus);

    /**
     * REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling calculateNewSpeed");
     * ENSURE(Vehicle::speed == tempSpeed , "calculateNewSpeed failed");
     */
    virtual void calculateNewSpeed();

    /**
     * REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling calculateNewPosition");
     * ENSURE(Vehicle::speed == 0.0 , "calculateNewPosition failed");
     */
    virtual void calculateNewPosition();

    /**
     * REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling calculateFollowDistance");
     * 
     */
    virtual double calculateFollowDistance();

    /**
     * REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling calculateSpeedRestriction");
     */
    virtual double calculateSpeedRestriction();

    /**
     * REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling calculateSpeedDifference");
     */
    virtual double calculateSpeedDifference();

    /**
     * REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling calculateStopDecelerate");
     */
    virtual void calculateStopDecelerate();

    /**
     * REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling getNextVehicle");
     * 
     */
    Vehicle* getNextVehicle();

    /**
     * REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling simulateStop");
     */
    virtual void simulateStop();

    /**
     * REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling simulateDecelerate");
     */
    virtual void simulateDecelerate();

    /**
     * REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling simulateAccelerate");
     */
    virtual void simulateAccelerate();

    /**
     * REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling simulate");
     */
    virtual void simulate();

    /**
     * REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling print");
     */
    virtual void print();

    void outputStatsVehicle();

    /**
     * REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling destructor");
     */
    virtual ~Vehicle();
};


#endif //TRAFFICSIMULATION2022_VOERTUIG_H
