#include "TrafficLight.h"

TrafficLight::TrafficLight(int cyclus) : cyclus(cyclus) {}

int TrafficLight::getCyclus() const {
    return cyclus;
}

void TrafficLight::setCyclus(int cyclus) {
    TrafficLight::cyclus = cyclus;
}

lightColor TrafficLight::getCurrentColor() const {
    return currentColor;
}

void TrafficLight::setCurrentColor(lightColor currentColor) {
    TrafficLight::currentColor = currentColor;
}
