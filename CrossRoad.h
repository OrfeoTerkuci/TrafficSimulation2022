//
// Created by jason on 05/04/2022.
//

#ifndef TRAFFICSIMULATION2022_CROSSROAD_H
#define TRAFFICSIMULATION2022_CROSSROAD_H
#include <map>

using namespace std;

class Road;
class Vehicle;

class CrossRoad {
    map<Road*, int> roads;
    bool switchRoad;
    CrossRoad* init;
public:
    /**
     * ENSURE(this == init, "init is not equal to itself, when calling constructor");*/
    CrossRoad();

    /**
     * REQUIRE(this->properlyInitialized(), "Crossroad was not properly initialized when calling isSwitchRoad");*/
    bool isSwitchRoad();

    /**
     * REQUIRE(this->properlyInitialized(), "Crossroad was not properly initialized, when calling setSwitchRoad");
     * REQUIRE(*typeid(new_switchRoad).name() == 'b', "new_switchRoad is not of type bool");*/
    void setSwitchRoad(bool switchRoad);

    /**
     * REQUIRE(this->properlyInitialized(), "Crossroad was not properly initialized when calling updateSwitchRoad");*/
    void updateSwitchRoad(bool &random , int &time);

    /**
     * REQUIRE(this->properlyInitialized(), "Crossroad was not properly initialized when calling addRoad");
     * REQUIRE(road->properlyInitialized(), "Road is not properly initialized when calling addRoad");
     * REQUIRE(position >= 0 and (unsigned) position <= road->getLength(), "position was out of bounds when calling addRoad");
     * ENSURE(roads[road] == position, "road is not on the right position");*/
    void addRoad(Road* road, int position);

    /**
     * REQUIRE(this->properlyInitialized(), "Crossroad was not properly initialized when calling getRoad");*/
    map<Road *, int> &getRoads();

    /**
     * REQUIRE(this->properlyInitialized(), "Crossroad was not properly initialized when calling setRoad");
     * ENSURE(roads == newRoads, "roads was not assigned to newRoads, when calling setRoads");*/
    void setRoads(const map<Road *, int> &newRoads);

    /**
     * REQUIRE(this->properlyInitialized(), "TrafficSimulation was not initialized when calling getPosition");
     * REQUIRE(*typeid(road).name() == 'P', "road is not a pointer");*/
    int getPosition(Road* &road);

    /**
     * REQUIRE(this->properlyInitialized(), "TrafficSimulation was not initialized when calling getNearestVehicle");*/
    Vehicle* getNearestVehicle(Road* &road);

    /**
     * REQUIRE(this->properlyInitialized(), "Crossroad was not properly initialized when calling simulateCrossroad");
     * REQUIRE(*typeid(random).name() == 'b', "type was not boolean");*/
    void simulateCrossroad(bool random = true , int time = 0);

    bool properlyInitialized() const;

    /**
     * REQUIRE(this->properlyInitialized(), "crossroad was not properly initialized when calling destructor");*/
    virtual ~CrossRoad();
};


#endif //TRAFFICSIMULATION2022_CROSSROAD_H
