//
// Created by jason on 19/03/2022.
//

#ifndef TRAFFICSIMULATION2022_VEHICLEGENERATOR_H
#define TRAFFICSIMULATION2022_VEHICLEGENERATOR_H
#include "Road.h"

class VehicleGenerator {
    Road* road;
    int frequentie;

    VehicleGenerator* _initCheck;
public:
    VehicleGenerator();

    bool properlyInitialized();

    Road *getRoad();

    void setRoad(Road *newRoad);

    double getFrequentie();

    void setFrequentie(double newFrequentie);

    void simulate();

    virtual ~VehicleGenerator();
};


#endif //TRAFFICSIMULATION2022_VEHICLEGENERATOR_H
