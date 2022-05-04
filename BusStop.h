//
// Created by jason on 05/04/2022.
//

#ifndef TRAFFICSIMULATION2022_BUSSTOP_H
#define TRAFFICSIMULATION2022_BUSSTOP_H

#include "Vehicle.h"

class Road;

class BusStop {
    int cooldown;
    int waitTime;
    int position;
    Road* road;
    BusStop* init;
public:
    BusStop();

    BusStop(int waitTime, int position, Road *road);

    int getWaitTime() const;

    void setWaitTime(int newWaitTime);

    int getPosition() const;

    void setPosition(int newPosition);

    Road *getRoad() const;

    void setRoad(Road *newRoad);

    Vehicle* getNearestBus();

    void simulateBusStop();

    bool properlyInitialized() const;

    virtual ~BusStop();
};


#endif //TRAFFICSIMULATION2022_BUSSTOP_H
