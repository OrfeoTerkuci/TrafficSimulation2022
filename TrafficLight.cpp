#include "TrafficLight.h"


TrafficLight::TrafficLight(unsigned int cyclus, Road *road) : cyclus(cyclus), road(road) {}

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

const Road* TrafficLight::getRoad() {
    return road;
}

void TrafficLight::setRoad(Road* newRoad) {
    TrafficLight::road = newRoad;
}

TrafficLight::~TrafficLight() {

}

TrafficLight::TrafficLight() {}

unsigned int TrafficLight::getPosition() const {
    return position;
}

void TrafficLight::setPosition(unsigned int newPosition) {
    TrafficLight::position = newPosition;
}

void TrafficLight::print() {
    cout << "Traffic light: " << endl;
    cout << '\t' << "In road " << this->road->getRoadName() << endl;
    cout << '\t' << "On position " << this->position << endl;
    cout << '\t' << "Has " << this->cyclus << " Cycles" << endl;
}
