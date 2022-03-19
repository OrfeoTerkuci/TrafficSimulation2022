#include "VehicleGenerator.h"
#include "DesignByContract.h"

VehicleGenerator::VehicleGenerator() : road(), frequentie() {
    _initCheck = this;
    ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
}

Road *VehicleGenerator::getRoad(){
    REQUIRE(this->properlyInitialized(), "VehicleGenerator was not initialized when calling getRoad");
    return road;
}

void VehicleGenerator::setRoad(Road *newRoad) {
    REQUIRE(this->properlyInitialized(), "VehicleGenerator was not initialized when calling setRoad");
    VehicleGenerator::road = newRoad;
}

double VehicleGenerator::getFrequentie(){
    REQUIRE(this->properlyInitialized(), "VehicleGenerator was not initialized when calling getFrequentie");
    return frequentie;
}

void VehicleGenerator::setFrequentie(double newFrequentie) {
    REQUIRE(this->properlyInitialized(), "VehicleGenerator was not initialized when calling setFrequentie");
    VehicleGenerator::frequentie = newFrequentie;
}

VehicleGenerator::~VehicleGenerator() {
    REQUIRE(this->properlyInitialized(), "VehicleGenerator was not initialized when calling destructor");
}

bool VehicleGenerator::properlyInitialized() {
    return _initCheck == this;
}

void VehicleGenerator::simulate() {

}
