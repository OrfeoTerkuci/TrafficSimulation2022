#ifndef TRAFFICSIMULATION2022_TRAFFICLIGHT_H
#define TRAFFICSIMULATION2022_TRAFFICLIGHT_H


enum lightColor {red , green};

class TrafficLight {
    int cyclus;

    lightColor currentColor;

public:
    TrafficLight(int cyclus);

    int getCyclus() const;

    void setCyclus(int cyclus);

    lightColor getCurrentColor() const;

    void setCurrentColor(lightColor currentColor);
};


#endif //TRAFFICSIMULATION2022_TRAFFICLIGHT_H
