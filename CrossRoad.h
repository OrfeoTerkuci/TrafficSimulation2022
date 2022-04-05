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
};


#endif //TRAFFICSIMULATION2022_CROSSROAD_H
