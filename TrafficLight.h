#ifndef TRAFFICSIMULATION2022_TRAFFICLIGHT_H
#define TRAFFICSIMULATION2022_TRAFFICLIGHT_H

enum lightColor {red , green};

class TrafficLight {
    int cyclus;

    lightColor currentColor;

public:
    TrafficLight(int cyclus);

    int getCyclus() const;

    void setCyclus(int newCyclus);

    lightColor getCurrentColor() const;

    void setCurrentColor(lightColor newColor);
};


#endif //TRAFFICSIMULATION2022_TRAFFICLIGHT_H
