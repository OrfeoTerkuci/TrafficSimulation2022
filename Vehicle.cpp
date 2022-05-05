// custom libs
#include "Vehicle.h"
#include "Standard_Values.h"
#include "DesignByContract.h"

// build in libs
#include <cmath>
#include <typeinfo>
#include <fstream>

using namespace std;


Vehicle::Vehicle(double speed, double position , vehicleType type) :
    speed(speed), position(position) , acceleration(0.0) , type(type),
    slowing_bus(false) , stopping_bus(false) , leaving_bus(false) , _initCheck(this)
    {
    REQUIRE(*typeid(speed).name() == 'd' , "constructor called with invalid speed parameter");
    REQUIRE(*typeid(position).name() == 'd' , "constructor called with invalid position parameter");
   /* // Check speed
    if (speed == 0){
        this->status = idle;
    }
    else if (this->acceleration > 0){
        this->status = accelerate;
    }
    else if (this->acceleration < 0){
        this->status = decelerate;
    }
    else {
        this->status = stopping;
    }*/
    this->status = accelerate;
    setStandardValues();
    ENSURE(Vehicle::speed == speed , "speed was not properly initialized");
    ENSURE(Vehicle::position == position , "position was not properly initialized");
    ENSURE(Vehicle::acceleration == 0.0 , "acceleration was not properly initialized");
    ENSURE(Vehicle::currentMaxSpeed == v_max_speed , "currentMaxSpeed was not properly initialized");
    ENSURE(Vehicle::type == type , "vehicleType was not properly initialized");
    ENSURE(!Vehicle::slowing_bus , "slowing_bus was not properly initialized");
    ENSURE(!Vehicle::stopping_bus, "stopping_bus was not properly initialized");
    ENSURE(!Vehicle::leaving_bus, "leaving_bus was not properly initialized");
    ENSURE(properlyInitialized() , "constructor must end in properlyInitialized state");
}

Vehicle::Vehicle() : speed(0.0) , position(0.0) , acceleration(0.0) , type(T_AUTO) , slowing_bus(false) , stopping_bus(false)  , leaving_bus(false), status(accelerate) , _initCheck(this) {
    setStandardValues();
    ENSURE(Vehicle::speed == 0.0 , "speed was not properly initialized");
    ENSURE(Vehicle::position == 0.0 , "position was not properly initialized");
    ENSURE(Vehicle::acceleration == 0.0 , "acceleration was not properly initialized");
    ENSURE(Vehicle::currentMaxSpeed == v_max_speed , "currentMaxSpeed was not properly initialized");
    ENSURE(Vehicle::type == T_AUTO , "vehicleType was not properly initialized");
    ENSURE(!Vehicle::slowing_bus , "slowing_bus was not properly initialized");
    ENSURE(!Vehicle::stopping_bus, "stopping_bus was not properly initialized");
    ENSURE(!Vehicle::leaving_bus, "leaving_bus was not properly initialized");
    ENSURE(properlyInitialized() , "constructor must end in properlyInitialized state");
}


bool Vehicle::properlyInitialized() const{
    return _initCheck == this;
}

double Vehicle::getCurrentMaxSpeed() const {
    REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling getCurrentMaxSpeed");
    return currentMaxSpeed;
}

void Vehicle::setCurrentMaxSpeed(double newCurrentMaxSpeed) {
    REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling setCurrentMaxSpeed");
    REQUIRE(*typeid(newCurrentMaxSpeed).name() == 'd' , "setCurrentMaxSpeed was called with invalid parameter : wrong type");
    REQUIRE(newCurrentMaxSpeed >= 0 , "setCurrentMaxSpeed was called with invalid parameter : negative newCurrentMaxSpeed");
    Vehicle::currentMaxSpeed = newCurrentMaxSpeed;
    ENSURE(Vehicle::currentMaxSpeed == currentMaxSpeed , "setCurrentMaxSpeed failed");
}

string Vehicle::getStatusString() {
    REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling getStatusString");
    if (status == accelerate){
        return "Accelerating";
    }
    else if (status == decelerate){
        return "Decelerating";
    }
    else if (status == stopping){
        return "Stopping";
    }
    return "Stopped / Idle";
}

vehicleStatus Vehicle::getStatus() const {
    REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling getStatus");
    return status;
}

void Vehicle::setStatus(vehicleStatus newStatus) {
    REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling setStatus");
    REQUIRE(status == accelerate || status == decelerate || status == stopping || status == idle
            , "setStatus was called with invalid parameter");
    Vehicle::status = newStatus;
    ENSURE(Vehicle::status == status , "setStatus failed");
}

double Vehicle::getSpeed() const {
    REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling getSpeed");
    return speed;
}

void Vehicle::setSpeed(double newSpeed) {
    REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling setSpeed");
    REQUIRE(*typeid(newSpeed).name() == 'd' , "setSpeed was called with invalid parameter : wrong type");
    REQUIRE(newSpeed >= 0 , "setSpeed was called with invalid parameter : negative speed");
    Vehicle::speed = newSpeed;
    ENSURE(Vehicle::speed == newSpeed , "setSpeed failed");
}

double Vehicle::getVehiclePosition() const {
    REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling getVehiclePosition");
    return position;
}

void Vehicle::setPosition(double newPosition) {
    REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling setPosition");
    REQUIRE(*typeid(newPosition).name() == 'd' , "setPosition was called with invalid parameter : wrong type");
    REQUIRE(newPosition >= 0 , "setPosition was called with invalid parameter : negative position");
    Vehicle::position = newPosition;
    ENSURE(Vehicle::position == newPosition , "setPosition failed");
}

double Vehicle::getAcceleration() const {
    REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling getAcceleration");
    return acceleration;
}

void Vehicle::setAcceleration(double newAcceleration) {
    REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling setAcceleration");
    REQUIRE(*typeid(newAcceleration).name() == 'd' , "setAcceleration was called with invalid parameter");
    Vehicle::acceleration = newAcceleration;
    ENSURE(Vehicle::acceleration == newAcceleration , "setAcceleration failed");
}

Road* Vehicle::getRoad() const {
    REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling getRoad");
    return road;
}

void Vehicle::setRoad(Road *newRoad) {
    REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling setRoad");
    REQUIRE(*typeid(newRoad).name() == 'P' , "setRoad was called with invalid parameter");
    REQUIRE(newRoad->properlyInitialized() , "setRoad was called with uninitialized parameter");
    Vehicle::road = newRoad;
    ENSURE(Vehicle::road == newRoad , "setRoad failed");
}

const vehicleType &Vehicle::getType() const {
    REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling getType");
    return type;
}

void Vehicle::setType(const vehicleType &newType) {
    REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling setType");
    Vehicle::type = newType;
    setStandardValues();
    ENSURE(type == newType, "type was not assigned to newType, after calling setType");
}

void Vehicle::setStandardValues() {
    REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling setStandardValues");
    if (type == T_AMBULANCE){
        setV_length(AMBULANCE_LENGTH);
        setV_decelerate(AMBULANCE_DECELERATE);
        setV_max_acceleration(AMBULANCE_MAX_ACCELERATION);
        setV_max_brakefactor(AMBULANCE_MAX_BRAKE_FACTOR);
        setV_max_speed(AMBULANCE_MAX_SPEED);
        setV_min_followDistance(AMBULANCE_MIN_FOLLOW_DISTANCE);
    }
    else if (type == T_BUS){
        setV_length(BUS_LENGTH);
        setV_max_speed(BUS_MAX_SPEED);
        setV_max_acceleration(BUS_MAX_ACCELERATION);
        setV_max_brakefactor(BUS_MAX_BRAKE_FACTOR);
        setV_min_followDistance(BUS_MIN_FOLLOW_DISTANCE);
        setV_decelerate(BUS_DECELERATE);
    }
    else if (type == T_FIRETRUCK){
        setV_length(FIRETRUCK_LENGTH);
        setV_max_speed(FIRETRUCK_MAX_SPEED);
        setV_max_acceleration(FIRETRUCK_MAX_ACCELERATION);
        setV_max_brakefactor(FIRETRUCK_MAX_BRAKE_FACTOR);
        setV_min_followDistance(FIRETRUCK_MIN_FOLLOW_DISTANCE);
        setV_decelerate(FIRETRUCK_DECELERATE);
    }
    else if (type == T_POLICE){
        setV_length(POLICE_LENGTH);
        setV_max_speed(POLICE_MAX_SPEED);
        setV_max_acceleration(POLICE_MAX_ACCELERATION);
        setV_max_brakefactor(POLICE_MAX_BRAKE_FACTOR);
        setV_min_followDistance(POLICE_MIN_FOLLOW_DISTANCE);
        setV_decelerate(POLICE_DECELERATE);
    }
    else{
        setV_length(LENGTH);
        setV_max_speed(MAX_SPEED);
        setV_max_acceleration(MAX_ACCELERATION);
        setV_max_brakefactor(MAX_BRAKE_FACTOR);
        setV_min_followDistance(MIN_FOLLOW_DISTANCE);
        setV_decelerate(DECELERATE);
    }
    currentMaxSpeed = v_max_speed;
}

double Vehicle::getV_length() const {
    REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling getV_length");
    return v_length;
}

void Vehicle::setV_length(double new_v_length) {
    REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling setV_length");
    Vehicle::v_length = new_v_length;
    ENSURE(v_length == new_v_length, "v_length was not assigned to new_v_length, after calling setV_length");
}

double Vehicle::getV_max_speed() const {
    REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling getV_max_speed");
    return v_max_speed;
}

void Vehicle::setV_max_speed(double new_v_max_speed) {
    REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling setV_max_speed");
    Vehicle::v_max_speed = new_v_max_speed;
    ENSURE(v_max_speed == new_v_max_speed, "v_max_speed was not assigned to new_v_max_speed, after calling setV_max_speed");
}

double Vehicle::getV_max_acceleration() const {
    REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling getV_max_acceleration");
    return v_max_acceleration;
}

void Vehicle::setV_max_acceleration(double new_v_max_acceleration) {
    REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling setV_max_acceleration");
    Vehicle::v_max_acceleration = new_v_max_acceleration;
    ENSURE(v_max_acceleration == new_v_max_acceleration, "v_max_acceleration was not assigned to new_v_max_acceleration, after calling setV_max_acceleration");
}

double Vehicle::getV_max_brakefactor() const {
    REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling getV_max_brakefactor");
    return v_max_brakefactor;
}

void Vehicle::setV_max_brakefactor(double new_v_max_brakefactor) {
    REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling setV_max_brakefactor");
    Vehicle::v_max_brakefactor = new_v_max_brakefactor;
    ENSURE(v_max_brakefactor == new_v_max_brakefactor, "v_max_brakefactor was not assigned to new_v_max_brakefactor, after calling setV_max_brakefactor");
}

double Vehicle::getV_min_followDistance() const {
    REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling getV_min_followDistance");
    return v_min_followDistance;
}

void Vehicle::setV_min_followDistance(double new_v_min_followDistance) {
    REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling setV_min_followDistance");
    Vehicle::v_min_followDistance = new_v_min_followDistance;
    ENSURE(v_min_followDistance == new_v_min_followDistance, "followDistance was not assigned to new followDistance, after calling setV_min_followDistance");
}

double Vehicle::getV_decelerate() const {
    REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling getV_decelerate");
    return v_decelerate;
}

void Vehicle::setV_decelerate(double new_v_decelerate) {
    REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling setV_decelerate");
    Vehicle::v_decelerate = new_v_decelerate;
    ENSURE(v_decelerate == new_v_decelerate, "decelerate of vehicle was not assigende to new decelerate, after calling setV_decelerate");
}

bool Vehicle::isSlowing_bus() const {
    REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling isSlowing_bus");
    return slowing_bus;
}

void Vehicle::setSlowing_bus(bool new_slowing_bus) {
    REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling setSlowing_bus");
    Vehicle::slowing_bus = new_slowing_bus;
    ENSURE(slowing_bus == new_slowing_bus, "slowing bus was not assigned to new slowing bus, after calling setSlowing_bus");
}

bool Vehicle::isStopping_bus() const {
    REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling isStopping_bus");
    return stopping_bus;
}

void Vehicle::setStopping_bus(bool new_stopping_bus) {
    REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling setStopping_bus");
    Vehicle::stopping_bus = new_stopping_bus;
    ENSURE(stopping_bus == new_stopping_bus, "stopping bus was not assigned to new stopping bus, after calling setStopping_bus");
}

bool Vehicle::isLeaving_bus() const {
    REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling isLeaving_bus");
    return leaving_bus;
}

void Vehicle::setLeaving_bus(bool new_leaving_bus) {
    REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling setLeaving_bus");
    Vehicle::leaving_bus = new_leaving_bus;
    ENSURE(leaving_bus == new_leaving_bus, "leaving bus was not assigend to new leaving bus, after calling setLeaving_bus");
}

void Vehicle::calculateNewAcceleration(double maxSpeed) {
    REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling calculateNewAcceleration");
    REQUIRE(*typeid(maxSpeed).name() == 'd' , "calculateNewAcceleration was called with invalid parameter : wrong type");
    REQUIRE(maxSpeed >= 0 , "calculateNewAcceleration was called with invalid parameter : negative maxSpeed");
    setCurrentMaxSpeed(maxSpeed);
    if(getNextVehicle() == NULL || (getNextVehicle() != NULL && getNextVehicle()->getVehiclePosition() - (this->position + v_length) >= v_min_followDistance) ){
        setAcceleration(v_max_acceleration * ( 1- pow( (this->speed/this->currentMaxSpeed), 4) ) );
    }
    else{
        setAcceleration(v_max_acceleration * (1- pow((this->speed/this->currentMaxSpeed), 4) - pow(this->calculateSpeedRestriction(), 2)));
    }
}

void Vehicle::calculateNewSpeed() {
    REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling calculateNewSpeed");
    double tempSpeed = this->speed + this->acceleration * SIMULATION_TIME;

    if (tempSpeed > 0){
        setSpeed(tempSpeed);
        //ENSURE(Vehicle::speed == tempSpeed , "calculateNewSpeed failed");
        setPosition(this->position + this->speed * SIMULATION_TIME + this->acceleration * (pow(SIMULATION_TIME,2) / 2));
    }
    else{
        calculateNewPosition();
    }
}

void Vehicle::calculateNewPosition() {
    REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling calculateNewPosition");
    setPosition(this->position - (pow(this->speed, 2) / 2 * acceleration));
    setSpeed(0);
    //ENSURE(Vehicle::speed == 0.0 , "calculateNewPosition failed");
}

double Vehicle::calculateFollowDistance() {
    REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling calculateFollowDistance");
    if(this->getNextVehicle() == NULL){
        return 0;
    }
    return abs(this->getVehiclePosition() - this->getNextVehicle()->getVehiclePosition());
}

double Vehicle::calculateSpeedRestriction() {
    REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling calculateSpeedRestriction");
    return (v_min_followDistance + max(0.0 , this->speed + ( (this->speed * this->calculateSpeedDifference()) / ( 2 * sqrt(v_max_acceleration * v_max_brakefactor) ) ) ) / this->calculateFollowDistance() );
}

double Vehicle::calculateSpeedDifference() {
    REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling calculateSpeedDifference");
    if(this->getNextVehicle() == NULL){
        return 0;
    }
    return abs(this->getSpeed() - this->getNextVehicle()->getSpeed());
}

void Vehicle::calculateStopDecelerate() {
    REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling calculateStopDecelerate");
    setAcceleration( -(v_max_brakefactor * this->speed) / (v_max_speed) );
}

Vehicle* Vehicle::getNextVehicle() {
    REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling getNextVehicle");

    if(this->road == NULL || this->road->getVehicleAmount() <= 1){
        return NULL;
    }
    else{
        Vehicle* nextVehicle;
        Vehicle* currentVehicle;
        nextVehicle = this;
        double oldPosition = this->getVehiclePosition();
        double nextPos = this->road->getLength();
        for(int i = 0; i < this->road->getVehicleAmount(); ++i){
            currentVehicle = this->road->getVehicle(i);
            if(currentVehicle->getVehiclePosition() > oldPosition && currentVehicle->getVehiclePosition() <= nextPos){
                nextVehicle = currentVehicle;
                nextPos = nextVehicle->getVehiclePosition();
            }
        }
        return nextVehicle->getVehiclePosition() == oldPosition ? NULL : nextVehicle;
    }

}

void Vehicle::simulateStop() {
    REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling simulateStop");
    this->calculateStopDecelerate();
    this->calculateNewSpeed();
}

void Vehicle::simulateDecelerate() {
    REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling simulateDecelerate");
    this->calculateNewAcceleration(v_decelerate);
    this->calculateNewSpeed();
}

void Vehicle::simulateAccelerate() {
    REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling simulateAccelerate");
    this->calculateNewAcceleration(v_max_speed);
    this->calculateNewSpeed();
}

void Vehicle::simulate() {

    REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling simulate");
    // Check status of vehicle
    double oldPos = this->position;
    double oldSpeed = this->speed;
    double oldAcc = this->acceleration;
    if (status == idle){
        return;
    }
    if (status == decelerate){
        simulateDecelerate();
    }
    else if (status == stopping){
        simulateStop();
        // Update status
        if (speed <= 0.001) {
            setStatus(idle);
            setSpeed(0);
            setAcceleration(0);
        }
    }
    else if((getNextVehicle() != NULL && getNextVehicle()->getVehiclePosition() - (this->position + v_length) >= v_min_followDistance) || getNextVehicle() == NULL){
        // Update status
        setStatus(accelerate);
        simulateAccelerate();
    }
    else if(getNextVehicle() != NULL && getNextVehicle()->getVehiclePosition() - ( this->position + v_length) < v_min_followDistance){
        setPosition(oldPos);
        setSpeed(oldSpeed);
        setAcceleration(oldAcc);
        setStatus(decelerate);
        simulateDecelerate();
    }
    else if(getNextVehicle() != NULL && getNextVehicle()->getVehiclePosition() - ( this->position + v_length) < v_min_followDistance && this->status == decelerate){
        setPosition(oldPos);
        setSpeed(oldSpeed);
        setAcceleration(oldAcc);
        setStatus(stopping);
        simulateStop();
    }

}

void Vehicle::print() {
    REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling print");
    cout << '\t' << "-> Road: " << this->road->getRoadName() << endl;
    cout << '\t' << "-> Position: " << this->position << endl;
    cout << '\t' << "-> Speed: " << this->speed << endl;
    cout << '\t' << "-> Acceleration: " << this->acceleration << endl;

    cout << '\t' << "-> Status: " << this->getStatusString() << endl;

    cout << '\t' << "-> Type: " << this->getTypeString() << endl;

    cout << endl;
}

string Vehicle::getTypeString() const {
    REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling getTypeString");
    if(this->type == T_AUTO){
        return "Auto";
    }
    else if(this->type == T_AMBULANCE){
        return "Ambulance";
    }
    else if(this->type == T_BUS){
        return "Bus";
    }
    else if(this->type == T_FIRETRUCK){
        return "Firetruck";
    }
    else if(this->type == T_POLICE){
        return "Police";
    }
    else{
        return "";
    }
}

void Vehicle::outputStatsVehicle() {
    REQUIRE(this->properlyInitialized(), "TrafficSimulation was not initialized when calling outputsStats");
    fstream file("Stats.txt");
    file.open("Stats/StatsV.txt", fstream::out | fstream::in | ios::trunc);
    /*
    // Bus specific members
    bool slowing_bus;
    bool stopping_bus;
    bool leaving_bus;
    vehicleStatus status;
    Road* road;
    Vehicle* _initCheck;*/
    file << "vehicle length: " << this->getV_length() << endl;
    file << "vehicle max speed: " << this->getV_max_speed() << endl;
    file << "vehicle max acceleration: " << this->getV_max_acceleration() << endl;
    file << "vehicle max brakefactor: " << this->getV_max_brakefactor() << endl;
    file << "vehicle min follow distance: " << this->getV_min_followDistance() << endl;
    file << "vehicle decelerate: " << this->getV_decelerate() << endl;

    file << "slowing bus bool = " << this->isSlowing_bus() << endl;
    file << "stopping bus bool = " << this->isStopping_bus() << endl;
    file << "leaving bus bool = " << this->isLeaving_bus() << endl;

    file << "is properly initialized: " << boolalpha << (_initCheck == this) << endl;

    file.close();
    ENSURE(!file.is_open(), "file is still open when ending outputStats");
}

Vehicle::~Vehicle() {
    REQUIRE(this->properlyInitialized() , "Vehicle wasn't initialized when calling destructor");

}
