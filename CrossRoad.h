//
// Created by jason on 05/04/2022.
//

#ifndef TRAFFICSIMULATION2022_CROSSROAD_H
#define TRAFFICSIMULATION2022_CROSSROAD_H
#include <map>

using namespace std;

class Road;

class CrossRoad {
    map<Road*, int> roads;
    bool switchRoad;
    CrossRoad* init;
public:
    CrossRoad();

    bool isSwitchRoad();

    void addRoad(Road* road, int position);

    map<Road *, int> &getRoads();

    void setRoads(const map<Road *, int> &newRoads);

    void simulateCrossroad(bool random = true, int modulo_number = 0, int time = 0);

    bool properlyInitialized();

    virtual ~CrossRoad();
};


#endif //TRAFFICSIMULATION2022_CROSSROAD_H
