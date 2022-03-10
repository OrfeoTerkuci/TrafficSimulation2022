#ifndef TRAFFICSIMULATION2022_ROAD_H
#define TRAFFICSIMULATION2022_ROAD_H
#include <string>

using namespace std;

class Road {
    unsigned int length;

    string roadName;
public:
    Road(unsigned int length, const string &roadName);

    unsigned int getLength() const;

    void setLength(unsigned int newLength);

    const string &getRoadName() const;

    void setRoadName(const string &newRoadName);

    virtual ~Road();
};


#endif //TRAFFICSIMULATION2022_ROAD_H
