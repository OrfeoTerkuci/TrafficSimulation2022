//
// Created by jason on 19/03/2022.
//

#include "VehicleGenerator.h"

VehicleGenerator::VehicleGenerator() {}

Road *VehicleGenerator::getRoad() const {
    return road;
}

void VehicleGenerator::setRoad(Road *newRoad) {
    VehicleGenerator::road = newRoad;
}

double VehicleGenerator::getFrequentie() const {
    return frequentie;
}

void VehicleGenerator::setFrequentie(double newFrequentie) {
    VehicleGenerator::frequentie = newFrequentie;
}

VehicleGenerator::~VehicleGenerator() {}
