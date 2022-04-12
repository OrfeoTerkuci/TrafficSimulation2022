#ifndef TRAFFICSIMULATION2022_VEHICLEGENERATOR_H
#define TRAFFICSIMULATION2022_VEHICLEGENERATOR_H
#include "Road.h"

class VehicleGenerator {
    Road* road;
    int frequentie;
    int cooldown;
    vehicleType type;
    double min_distance;
    VehicleGenerator* _initCheck;
public:

    /**
     * ENSURE(VehicleGenerator::frequentie == 0 , "frequentie was not properly initialized");
     * ENSURE(VehicleGenerator::cooldown == 0 , "cooldown was not properly initialized");
     * ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
     */
    VehicleGenerator();

    double getMin_distance() const;

    void setMin_distance(double min_distance);

    bool properlyInitialized();

    /**
     * REQUIRE(this->properlyInitialized(), "VehicleGenerator was not initialized when calling getRoad");
     * @return A pointer to the road the VehicleGenerator is on 
     */
    Road *getRoad();

    /**
     * REQUIRE(this->properlyInitialized(), "VehicleGenerator was not initialized when calling setRoad");
     * REQUIRE(*typeid(newRoad).name() == 'P' , "setRoad was called with invalid parameter");
     * REQUIRE(newRoad->properlyInitialized() , "setRoad was called with uninitialized parameter");
     * ENSURE(VehicleGenerator::road == newRoad , "setRoad failed");
     * @param newRoad A pointer to a Road type object
     */
    void setRoad(Road *newRoad);

    /**
     * REQUIRE(this->properlyInitialized(), "VehicleGenerator was not initialized when calling getFrequentie");
     * @return The frequentie of the VehicleGenerator 
     */
    int getFrequentie();

    /**
     * REQUIRE(this->properlyInitialized(), "VehicleGenerator was not initialized when calling setFrequentie");
     * REQUIRE(*typeid(newFrequentie).name() == 'i' , "setFrequentie was called with invalid parameter : wrong type");
     * REQUIRE(newFrequentie >= 0 , "setFrequentie was called with invalid parameter : negative frequence");
     * ENSURE(VehicleGenerator::frequentie == newFrequentie , "setFrequentie failed");
     * @param newFrequentie The new frequence of the VehicleGenerator
     */
    void setFrequentie(int newFrequentie);
    
    /**
     * REQUIRE(this->properlyInitialized(), "VehicleGenerator was not initialized when calling getCooldown");
     * @return The current cooldown of the VehicleGenerator 
     */
    int getCooldown();

    /**
     * REQUIRE(this->properlyInitialized(), "VehicleGenerator was not initialized when calling setCooldown");
     * REQUIRE(*typeid(newCooldown).name() == 'i' , "setCooldown was called with invalid parameter : wrong type");
     * REQUIRE(newCooldown >= 0 , "setCooldown was called with invalid parameter : negative cooldown");
     * ENSURE(VehicleGenerator::cooldown == newCooldown , "setCooldown failed");
     * @param newCooldown The new cooldown of the VehicleGenerator
     */
    void setCooldown(int newCooldown);

    vehicleType getType();

    void setType(const vehicleType newType);

    /**
     * REQUIRE(this->properlyInitialized(), "VehicleGenerator was not initialized when calling simulate");
     * @return true if we must generate a new vehicle
     */
    bool simulate();

    /**
     * REQUIRE(this->properlyInitialized(), "VehicleGenerator was not initialized when calling destructor");
     */
    virtual ~VehicleGenerator();
};


#endif //TRAFFICSIMULATION2022_VEHICLEGENERATOR_H
