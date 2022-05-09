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
     * ENSURE(!switchRoad, "switchRoad was not properly initialized");
     * ENSURE(properlyInitialized(), "CrossRoad was not properly initialized");
     **/
    CrossRoad();

    bool properlyInitialized() const;

    /**
     * REQUIRE(this->properlyInitialized(), "Crossroad was not properly initialized when calling isSwitchRoad");
     * */
    bool isSwitchRoad();

    /**
     * REQUIRE(this->properlyInitialized(), "Crossroad was not properly initialized, when calling setSwitchRoad");
     * REQUIRE(*typeid(new_switchRoad).name() == 'b', "new_switchRoad is not of type bool");
     * ENSURE(CrossRoad::switchRoad == new_switchRoad , "setSwitchRoad failed");
     **/
    void setSwitchRoad(bool switchRoad);

    /**
     * REQUIRE(this->properlyInitialized(), "Crossroad was not properly initialized when calling updateSwitchRoad");
     **/
    void updateSwitchRoad(bool &random , int &time);

    /**
     * REQUIRE(this->properlyInitialized(), "Crossroad was not properly initialized when calling getRoad");
     **/
    map<Road *, int> &getRoads();

    /**
     * REQUIRE(this->properlyInitialized(), "Crossroad was not properly initialized when calling setRoad");
     * ENSURE(roads == newRoads, "roads was not assigned to newRoads, when calling setRoads");
     **/
    void setRoads(const map<Road *, int> &newRoads);

    /**
     * REQUIRE(this->properlyInitialized(), "Crossroad was not properly initialized when calling addRoad");
     * REQUIRE(*typeid(road).name() == 'P' , "addRoad was called with invalid road parameter : wrong type");
     * REQUIRE(road->properlyInitialized(), "Road is not properly initialized when calling addRoad");
     * REQUIRE(*typeid(position).name() == 'i' , "addRoad was called with invalid position parameter : wrong type");
     * REQUIRE(position >= 0 and (unsigned) position <= road->getLength(), "position was out of bounds when calling addRoad");
     * ENSURE(roads[road] == position, "road is not on the right position");
     **/
    void addRoad(Road* road, int position);

    /**
     * REQUIRE(this->properlyInitialized(), "TrafficSimulation was not initialized when calling getPosition");
     * REQUIRE(*typeid(road).name() == 'P', "getPosition was called with invalid road parameter : wrong type");
     * REQUIRE(road->properlyInitialized() , "road was not properly initialized when calling getPosition");
     **/
    int getPosition(Road* &road);

    /**
     * REQUIRE(this->properlyInitialized(), "TrafficSimulation was not initialized when calling getNearestVehicle");*/
    Vehicle* getNearestVehicle(Road* &road);

    /**
     * REQUIRE(this->properlyInitialized(), "Crossroad was not properly initialized when calling simulateCrossroad");
     * REQUIRE(*typeid(random).name() == 'b', "simulateCrossroad was called with invalid random parameter : wrong type");
     * REQUIRE(*typeid(time).name() == 'i', "simulateCrossroad was called with invalid time parameter : wrong type");
     **/
    void simulateCrossroad(bool random = true , int time = 0);

    /**
     * REQUIRE(this->properlyInitialized(), "crossroad was not properly initialized when calling destructor");*/
    virtual ~CrossRoad();
};

#endif //TRAFFICSIMULATION2022_CROSSROAD_H
