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
public:
    CrossRoad();

    virtual ~CrossRoad();

    void addRoad(Road* road, int position);

    map<Road *, int> &getRoads();

    void setRoads(const map<Road *, int> &newRoads);
};


#endif //TRAFFICSIMULATION2022_CROSSROAD_H
