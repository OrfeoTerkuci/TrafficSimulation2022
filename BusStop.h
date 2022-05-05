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
    /**
     * ENSURE(init == this, "init is not itself, when calling constructor");*/
    BusStop();

    /**
     * ENSURE(init == this, "init is not itself, after calling constructor");
     * ENSURE(road == new_road, "road was not assigned to new_road, after calling constructor");
     * ENSURE(waitTime == cooldown, "cooldown was not assigned to waitTime, after calling constructor");
     * ENSURE(position == new_position, "position was not assigned to new_position, after calling constructor");*/
    BusStop(int waitTime, int position, Road *road);

    /**
     * REQUIRE(this->properlyInitialized(), "Bus stop was not properly initialized when calling getWaitTime");*/
    int getWaitTime() const;

    /**
     * REQUIRE(this->properlyInitialized(), "Bus stop was not properly initialized when calling setWaitTime");
     * ENSURE(waitTime == newWaitTime, "waitTime was not assigned to newWaitTime, when calling setWaitTime");*/
    void setWaitTime(int newWaitTime);

    /**
     * REQUIRE(this->properlyInitialized(), "Bus stop was not properly initialized when calling getCooldown");*/
    int getCooldown() const;

    /**
    * REQUIRE(this->properlyInitialized(), "Bus stop was not properly initialized when calling setCooldown");
    * ENSURE(cooldown == new_cooldown, "cooldown was not assigned to new_cooldown, after calling setCooldown");*/
    void setCooldown(int new_cooldown);

    /**
     * REQUIRE(this->properlyInitialized(), "Bus stop was not properly initialized when calling getPosition");*/
    int getPosition() const;

    /**
     * REQUIRE(this->properlyInitialized(), "Bus stop was not properly initialized when calling setPosition");
     * ENSURE(position == newPosition, "position was not assigned to newPosition, when calling setPosition");*/
    void setPosition(int newPosition);

    /**
     * REQUIRE(this->properlyInitialized(), "Bus stop was not properly initialized when calling getRoad");*/
    Road *getRoad();

    /**
     * REQUIRE(this->properlyInitialized(), "Bus stop was not properly initialized when calling setRoad");
     * REQUIRE(newRoad->properlyInitialized(), "road was not properly initialized when calling setRoad");
     * ENSURE(road == newRoad, "road was not assigned to newRoad, when calling setRoad");*/
    void setRoad(Road *newRoad);

    /**
     * REQUIRE(this->properlyInitialized(), "Bus stop was not properly initialized when calling getNearestBus");*/
    Vehicle* getNearestBus();

    /**
     * REQUIRE(this->properlyInitialized(), "Busstop was not properly initialized when calling simulateBusStop");
     * ENSURE(cooldown == waitTime, "cooldown wasn't reset");*/
    void simulateBusStop();

    bool properlyInitialized() const;

    /**
     * REQUIRE(this->properlyInitialized(), "Busstop was not properly initialized when calling destructor");*/
    virtual ~BusStop();
};


#endif //TRAFFICSIMULATION2022_BUSSTOP_H
