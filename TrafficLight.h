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
    TrafficLight(unsigned int cyclus, Road *road);

    TrafficLight();

    bool properlyInitialized();

    int getCyclus();

    void setCyclus(int newCyclus);

    unsigned int getPosition();

    void setPosition(unsigned int newPosition);

    lightColor getCurrentColor();

    void setCurrentColor(lightColor newColor);

    const Road* getRoad();

    void setRoad(Road* newRoad);

    Vehicle* getNearestVehicle();

    void simulate(int &count);

    void print();

    virtual ~TrafficLight();
};


#endif //TRAFFICSIMULATION2022_TRAFFICLIGHT_H
