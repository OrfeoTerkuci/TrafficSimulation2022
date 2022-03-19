//
// Created by jason on 19/03/2022.
//

#ifndef TRAFFICSIMULATION2022_VEHICLEGENERATOR_H
#define TRAFFICSIMULATION2022_VEHICLEGENERATOR_H
#include "Road.h"

class VehicleGenerator {
    Road* road;
    int frequentie;

public:
    VehicleGenerator();

    Road *getRoad() const;

    void setRoad(Road *newRoad);

    double getFrequentie() const;

    void setFrequentie(double newFrequentie);

    virtual ~VehicleGenerator();
};


#endif //TRAFFICSIMULATION2022_VEHICLEGENERATOR_H
