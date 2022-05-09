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
     * ENSURE(road == new_road, "road was not correctly initialized");
     * ENSURE(cooldown == new_waitTime, "cooldown was not correctly initialized");
     * ENSURE(waitTime == new_waitTime , "waitTime was not correctly initialized");
     * ENSURE(position == new_position, "position was not correctly initialized");
     * ENSURE(properlyInitialized(), "BusStop constructor must end in properlyInitialized state");
    */
    BusStop(int waitTime, int new_position, Road *new_road = NULL);

    /**
     * ENSURE(road == NULL, "road was not correctly initialized");
     * ENSURE(cooldown == 0, "cooldown was not correctly initialized");
     * ENSURE(waitTime == 0 , "waitTime was not correctly initialized");
     * ENSURE(position == 0, "position was not correctly initialized");
     * ENSURE(properlyInitialized(), "BusStop constructor must end in properlyInitialized state");
    */
    BusStop();

    bool properlyInitialized() const;

    /**
     * REQUIRE(this->properlyInitialized(), "Bus stop was not properly initialized when calling getCooldown");
     * */
    int getCooldown() const;

    /**
     * REQUIRE(this->properlyInitialized(), "Bus stop was not properly initialized when calling setCooldown");
     * REQUIRE( *typeid(new_cooldown).name() == 'i' , "new_cooldown was not an int when calling setCooldown");
     * ENSURE(cooldown == new_cooldown, "cooldown was not assigned to new_cooldown, after calling setCooldown");
     * */
    void setCooldown(int new_cooldown);

    /**
     * REQUIRE(this->properlyInitialized(), "Bus stop was not properly initialized when calling getWaitTime");
     * */
    int getWaitTime() const;

    /**
     * REQUIRE(this->properlyInitialized(), "Bus stop was not properly initialized when calling setWaitTime");
     * REQUIRE(*typeid(newWaitTime).name() == 'i' , "newWaitTime was not an int when calling setWaitTime");
     * ENSURE(waitTime == newWaitTime, "waitTime was not assigned to newWaitTime, when calling setWaitTime");
     * */
    void setWaitTime(int newWaitTime);


    /**
     * REQUIRE(this->properlyInitialized(), "Bus stop was not properly initialized when calling getPosition");
     * */
    int getPosition() const;

    /**
     * REQUIRE(this->properlyInitialized(), "Bus stop was not properly initialized when calling setPosition");
     * REQUIRE(*typeid(newPosition).name() == 'i' , "newPosition was not an int when calling setPosition");
     * ENSURE(position == newPosition, "position was not assigned to newPosition, when calling setPosition");
     * */
    void setPosition(int newPosition);

    /**
     * REQUIRE(this->properlyInitialized(), "Bus stop was not properly initialized when calling getRoad");
     * */
    Road *getRoad() const;

    /**
     * REQUIRE(this->properlyInitialized(), "Bus stop was not properly initialized when calling setRoad");
     * REQUIRE(*typeid(newRoad).name() == 'P' , "newRoad was not a pointer when calling setRoad");
     * REQUIRE(newRoad->properlyInitialized(), "road was not properly initialized when calling setRoad");
     * ENSURE(road == newRoad, "road was not assigned to newRoad, when calling setRoad");*/
    void setRoad(Road *newRoad);

    /**
     * REQUIRE(this->properlyInitialized(), "Bus stop was not properly initialized when calling getNearestBus");*/
    Vehicle* getNearestBus() const;

    /**
     * REQUIRE(this->properlyInitialized(), "Busstop was not properly initialized when calling simulateBusStop");
     * ENSURE(cooldown == waitTime, "cooldown wasn't reset");*/
    void simulateBusStop();


    /**
     * REQUIRE(this->properlyInitialized(), "Busstop was not properly initialized when calling destructor");*/
    virtual ~BusStop();
};


#endif //TRAFFICSIMULATION2022_BUSSTOP_H
