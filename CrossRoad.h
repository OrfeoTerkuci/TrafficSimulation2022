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
public:
    CrossRoad();

    bool isSwitchRoad() const;

    void addRoad(Road* road, int position);

    map<Road *, int> &getRoads();

    void setRoads(const map<Road *, int> &newRoads);

    void simulateCrossroad(bool random = true, int modulo_number = 0, int time = 0);

    virtual ~CrossRoad();
};


#endif //TRAFFICSIMULATION2022_CROSSROAD_H
