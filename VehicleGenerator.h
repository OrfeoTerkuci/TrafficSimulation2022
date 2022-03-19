//
// Created by jason on 19/03/2022.
//

#ifndef TRAFFICSIMULATION2022_VEHICLEGENERATOR_H
#define TRAFFICSIMULATION2022_VEHICLEGENERATOR_H
#include "Road.h"

class VehicleGenerator {
    Road* road;
    double frequentie;

public:
    VehicleGenerator();

    virtual ~VehicleGenerator();
};


#endif //TRAFFICSIMULATION2022_VEHICLEGENERATOR_H
