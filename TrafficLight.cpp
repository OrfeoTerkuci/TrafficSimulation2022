#include "TrafficLight.h"

TrafficLight::TrafficLight(int cyclus) : cyclus(cyclus) {}

int TrafficLight::getCyclus() const {
    return cyclus;
}

void TrafficLight::setCyclus(int newCyclus) {
    TrafficLight::cyclus = newCyclus;
}

lightColor TrafficLight::getCurrentColor() const {
    return currentColor;
}

void TrafficLight::setCurrentColor(lightColor newColor) {
    TrafficLight::currentColor = newColor;
}

const Road &TrafficLight::getRoad() const {
    return road;
}

void TrafficLight::setRoad(const Road &newRoad) {
    TrafficLight::road = newRoad;
}
