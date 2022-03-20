#ifndef TRAFFICSIMULATION2022_TRAFFICLIGHT_H
#define TRAFFICSIMULATION2022_TRAFFICLIGHT_H
#include "Road.h"

#include <iostream>

using namespace std;

enum lightColor {red , green};

class TrafficLight {
    unsigned int cyclus;

    Road* road;

    lightColor currentColor;

    unsigned int position;

    TrafficLight* _initCheck;
public:

    /** 
     *REQUIRE(*typeid(cyclus).name() == 'j' && cyclus >= 0 , "Constructor was called with invalid cyclus");
     *REQUIRE(*typeid(road).name() == 'P' , "constructor was called with invalid road");
     *ENSURE(TrafficLight::cyclus == cyclus , "cyclus was not properly initialized");
     *ENSURE(TrafficLight::road == road , "road was not properly initialized");
     *ENSURE(TrafficLight::currentColor == red , "currentColor was not properly initialized");
     *ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
     * @param cyclus The cycle duration of the traffic light
     * @param road A pointer to a road element
     */
    TrafficLight(unsigned int cyclus, Road *road);

    /**
     * ENSURE(TrafficLight::currentColor == red , "currentColor was not properly initialized");
     * ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
     */
    TrafficLight();

    bool properlyInitialized();

    /**
     * REQUIRE(this->properlyInitialized(), "TrafficSimulation was not initialized when calling getCyclus");
     * @return The trafficLight cyclus
     */
    int getCyclus();

    /**
     * REQUIRE(this->properlyInitialized(), "TrafficSimulation was not initialized when calling setCyclus");
     * REQUIRE(*typeid(newCyclus).name() == 'j' , "setCyclus was called with invalid parameter");
     * ENSURE(TrafficLight::cyclus == newCyclus , "setCyclus failed");
     * @param newCyclus The new trafficLight cycle
     */
    void setCyclus(unsigned int newCyclus);

    /**
     * REQUIRE(this->properlyInitialized(), "TrafficSimulation was not initialized when calling getPosition");
     * @return The position of the traffic light on the road
     */
    unsigned int getPosition();

    /**
     * REQUIRE(this->properlyInitialized(), "TrafficSimulation was not initialized when calling setPosition");
     * REQUIRE(*typeid(newPosition).name() == 'j' , "setPosition was called with invalid parameter");
     * TrafficLight::position = newPosition;
     * ENSURE(TrafficLight::position == newPosition , "setPosition failed");
     * @param newPosition The new position of the traffic light
     */
    void setPosition(unsigned int newPosition);

    /**
     * REQUIRE(this->properlyInitialized(), "TrafficSimulation was not initialized when calling getCurrentColor");
     * @return The current color of the traffic light
     */
    lightColor getCurrentColor();

    /**
     * REQUIRE(this->properlyInitialized(), "TrafficSimulation was not initialized when calling setCurrentColor");
     * REQUIRE(newColor == red || newColor == green , "setCurrentColor was called with invalid parameter");
     * ENSURE(TrafficLight::currentColor == newColor , "setCurrentColor failed");
     */
    void setCurrentColor(lightColor newColor);

    /**
     * REQUIRE(this->properlyInitialized(), "TrafficSimulation was not initialized when calling getRoad");
     * @return A pointer to the road the traffic light is on
     */
    Road* getRoad();

    /**
     * REQUIRE(this->properlyInitialized(), "TrafficSimulation was not initialized when calling setRoad");
     *REQUIRE(*typeid(newRoad).name() == 'P' , "setRoad was called with invalid parameter");
     *TrafficLight::road = newRoad;
     *ENSURE(TrafficLight::road == newRoad , "setRoad failed");
     * @param newRoad A pointer to the new road
     */
    void setRoad(Road* newRoad);

    /**
     * REQUIRE(this->properlyInitialized(), "TrafficSimulation was not initialized when calling getNearestVehicle");
     * @return A pointer to the vehicle in front
     */
    Vehicle* getNearestVehicle();

    /**
     * REQUIRE(this->properlyInitialized(), "TrafficSimulation was not initialized when calling simulate");
     * REQUIRE(*typeid(count).name() == 'i' , "simulate was called with invalid parameter");
     * @param count The time elapsed since the last light change
     */
    void simulate(int &count);

    /**
     * REQUIRE(this->properlyInitialized(), "TrafficSimulation was not initialized when calling print");
     */
    void print();

    /**
     * REQUIRE(this->properlyInitialized(), "TrafficSimulation was not initialized when calling destructor");
     */
    virtual ~TrafficLight();
};


#endif //TRAFFICSIMULATION2022_TRAFFICLIGHT_H
