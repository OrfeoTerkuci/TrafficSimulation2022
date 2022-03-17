#include "TrafficLight.h"
#include "Vehicle.h"
#include "Standard_Values.h"

TrafficLight::TrafficLight(unsigned int cyclus, Road *road) : cyclus(cyclus), road(road) {}

TrafficLight::TrafficLight() {}

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

unsigned int TrafficLight::getPosition() const {
    return position;
}

void TrafficLight::setPosition(unsigned int newPosition) {
    TrafficLight::position = newPosition;
}

Vehicle* TrafficLight::getNearestVehicle() {
    double pos = this->getPosition();
    Vehicle* nearestVehicle = this->road->getVehicle(0);
    Vehicle* currentVehicle;
    for (int i = 0; i < this->road->getVehicleAmount(); ++i) {
        currentVehicle = this->road->getVehicle(i);
        if (currentVehicle->getVehiclePosition() < pos && currentVehicle->getVehiclePosition() > nearestVehicle->getVehiclePosition()){
            nearestVehicle = currentVehicle;
        }
    }
    return nearestVehicle;
}

void TrafficLight::simulate(int &count) {
    // Check if the cyclus has been completed
    if (count > this->getCyclus()){
        // Change light color
        this->setCurrentColor(this->getCurrentColor() == green ? red : green);
    }
    if (this->getCurrentColor() == green){
        // Vehicles before the light may accelerate again
    }
    if (this->getCurrentColor() == red){
        if ( (this->position - getNearestVehicle()->getVehiclePosition() ) <= SLOWING_DISTANCE){
            // Slow down
        }
        else if ( (this->position - getNearestVehicle()->getVehiclePosition() ) <= STOPPING_DISTANCE / 2){
            // Stop
        }
    }

}

void TrafficLight::print() {
    cout << "Traffic light specifications: " << endl;
    cout << '\t' << "In road " << this->road->getRoadName() << endl;
    cout << '\t' << "On position " << this->position << endl;
    cout << '\t' << "Has " << this->cyclus << " Cycles" << endl;
}

TrafficLight::~TrafficLight() {

}
