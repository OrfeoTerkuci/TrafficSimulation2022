#ifndef TRAFFICSIMULATION2022_TRAFFICLIGHT_H
#define TRAFFICSIMULATION2022_TRAFFICLIGHT_H
#include "Road.h"

enum lightColor {red , green};

class TrafficLight {
    unsigned int cyclus;

    lightColor currentColor;

    Road* road;

    unsigned int position;
public:
    TrafficLight(unsigned int cyclus, Road *road);

    TrafficLight();

    int getCyclus() const;

    void setCyclus(int newCyclus);

    unsigned int getPosition() const;

    void setPosition(unsigned int newPosition);

    lightColor getCurrentColor() const;

    void setCurrentColor(lightColor newColor);

    const Road* getRoad();

    void setRoad(Road* newRoad);

    virtual ~TrafficLight();

    void print();
};


#endif //TRAFFICSIMULATION2022_TRAFFICLIGHT_H
