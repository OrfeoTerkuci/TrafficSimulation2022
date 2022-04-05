//
// Created by jason on 05/04/2022.
//

#ifndef TRAFFICSIMULATION2022_BUSSTOP_H
#define TRAFFICSIMULATION2022_BUSSTOP_H
class Road;

class BusStop {
    int waitTime;
    int position;
    Road* road;
public:
    int getWaitTime() const;

    void setWaitTime(int newWaitTime);

    int getPosition() const;

    void setPosition(int newPosition);

    Road *getRoad() const;

    void setRoad(Road *newRoad);

    virtual ~BusStop();

    BusStop();

    BusStop(int waitTime, int position, Road *road);
};


#endif //TRAFFICSIMULATION2022_BUSSTOP_H
