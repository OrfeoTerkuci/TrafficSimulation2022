#include "VehicleGenerator.h"
#include "Vehicle.h"
#include "Standard_Values.h"
#include "DesignByContract.h"
#include <typeinfo>

VehicleGenerator::VehicleGenerator() : road(), frequentie(0) , cooldown(0) , type(T_AUTO) {

    _initCheck = this;
    ENSURE(VehicleGenerator::frequentie == 0 , "frequentie was not properly initialized");
    ENSURE(VehicleGenerator::cooldown == 0 , "cooldown was not properly initialized");
    ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
}

Road *VehicleGenerator::getRoad(){
    REQUIRE(this->properlyInitialized(), "VehicleGenerator was not initialized when calling getRoad");
    return road;
}

void VehicleGenerator::setRoad(Road *newRoad) {
    REQUIRE(this->properlyInitialized(), "VehicleGenerator was not initialized when calling setRoad");
    REQUIRE(*typeid(newRoad).name() == 'P' , "setRoad was called with invalid parameter");
    REQUIRE(newRoad->properlyInitialized() , "setRoad was called with uninitialized parameter");
    VehicleGenerator::road = newRoad;
    ENSURE(VehicleGenerator::road == newRoad , "setRoad failed");
}

int VehicleGenerator::getFrequentie(){
    REQUIRE(this->properlyInitialized(), "VehicleGenerator was not initialized when calling getFrequentie");
    return frequentie;
}

void VehicleGenerator::setFrequentie(int newFrequentie) {
    REQUIRE(this->properlyInitialized(), "VehicleGenerator was not initialized when calling setFrequentie");
    REQUIRE(*typeid(newFrequentie).name() == 'i' , "setFrequentie was called with invalid parameter : wrong type");
    REQUIRE(newFrequentie >= 0 , "setFrequentie was called with invalid parameter : negative frequence");
    VehicleGenerator::frequentie = newFrequentie;
    ENSURE(VehicleGenerator::frequentie == newFrequentie , "setFrequentie failed");
}

int VehicleGenerator::getCooldown() {
    REQUIRE(this->properlyInitialized(), "VehicleGenerator was not initialized when calling getCooldown");
    return cooldown;
}

void VehicleGenerator::setCooldown(int newCooldown) {
    REQUIRE(this->properlyInitialized(), "VehicleGenerator was not initialized when calling setCooldown");
    REQUIRE(*typeid(newCooldown).name() == 'i' , "setCooldown was called with invalid parameter : wrong type");
    REQUIRE(newCooldown >= 0 , "setCooldown was called with invalid parameter : negative cooldown");
    VehicleGenerator::cooldown = newCooldown;
    ENSURE(VehicleGenerator::cooldown == newCooldown , "setCooldown failed");
}

vehicleType VehicleGenerator::getType(){
    REQUIRE(this->properlyInitialized(), "VehicleGenerator was not initialized when calling setCooldown");
    return type;
}

void VehicleGenerator::setType(vehicleType newType){
    REQUIRE(this->properlyInitialized(), "VehicleGenerator was not initialized when calling setType");
    VehicleGenerator::type = newType;
    if(type == T_AMBULANCE){
        setMin_distance(AMBULANCE_LENGTH);
    }
    else if (type == T_FIRETRUCK){
        setMin_distance(FIRETRUCK_LENGTH);
    }
    else if (type == T_BUS){
        setMin_distance(BUS_LENGTH);
    }
    else if (type == T_POLICE){
        setMin_distance(POLICE_LENGTH);
    }
    else{
        setMin_distance(LENGTH);
    }
    ENSURE(VehicleGenerator::type == newType , "setType failed");
}

bool VehicleGenerator::properlyInitialized() {
    return _initCheck == this;
}

bool VehicleGenerator::simulate() {
    REQUIRE(this->properlyInitialized(), "VehicleGenerator was not initialized when calling simulate");
    // Check cooldown
    if (cooldown > 0){
        cooldown -= 1;
        return false;
    }
    bool canGenerate = true;
    // Check if there are vehicles on road between position 0 and 2 LENGTH
    for (int i = 0; i < this->road->getVehicleAmount(); i++){
        Vehicle* currentVehicle;
        currentVehicle = this->road->getVehicle(i);
        double currentPosition = currentVehicle->getVehiclePosition();
        if (currentPosition > 0 && currentPosition < 2 * getMin_distance() ) {
            canGenerate = false;
        }
    }
    // Check if we can generate
    if (canGenerate) {
        // Reset cooldown
        cooldown = frequentie;
    }
    // Return if we can generate or not
    return canGenerate;
}

VehicleGenerator::~VehicleGenerator() {
    REQUIRE(this->properlyInitialized(), "VehicleGenerator was not initialized when calling destructor");
}

double VehicleGenerator::getMin_distance() const {
    return min_distance;
}

void VehicleGenerator::setMin_distance(double min_distance) {
    VehicleGenerator::min_distance = min_distance;
}
