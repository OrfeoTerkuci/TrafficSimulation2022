#ifndef TRAFFICSIMULATION2022_TRAFFICLIGHT_H
#define TRAFFICSIMULATION2022_TRAFFICLIGHT_H
#include "Road.h"

enum lightColor {red , green};

class TrafficLight {
    unsigned int cyclus;

    lightColor currentColor;

    Road road;

public:

    TrafficLight(unsigned int cyclus, const Road &road);

    int getCyclus() const;

    void setCyclus(int newCyclus);

    lightColor getCurrentColor() const;

    void setCurrentColor(lightColor newColor);

    const Road &getRoad() const;

    void setRoad(const Road &newRoad);

    virtual ~TrafficLight();
};


#endif //TRAFFICSIMULATION2022_TRAFFICLIGHT_H
