#include "gtest/gtest.h"
#include <iostream>

using namespace std;

#include "TrafficSimulation.h"
#include "Road.h"
#include "TrafficLight.h"
#include "Vehicle.h"
#include "VehicleGenerator.h"
#include "Standard_Values.h"

class TrafficSimulationTest: public ::testing::Test {
protected:
    // You should make the members protected s.t. they can be
    // accessed from sub-classes.

    // virtual void SetUp() will be called before each test is run.  You
    // should define it if you need to initialize the variables.
    // Otherwise, this can be skipped.
    virtual void SetUp() {
    }

    // virtual void TearDown() will be called after each test is run.
    // You should define it if there is cleanup work to do.  Otherwise,
    // you don't have to provide it.
    virtual void TearDown() {
    }

    // Declares the variables your tests want to use.
    TrafficSimulation ts;
};

TEST_F(TrafficSimulationTest, DefaultConstructor){
    // test if the object is properly initialized
    EXPECT_TRUE(ts.properlyInitialized());
}

TEST(ParserTest, Parser){
    // test if the parser fully works
    TrafficSimulation testFile(SIM1);
    EXPECT_TRUE(testFile.getRoads()[0]->properlyInitialized());
    EXPECT_TRUE(testFile.getRoads()[0]->getRoadName() == "Middelheimlaan" and testFile.getRoads()[0]->getLength() == 500);
    EXPECT_TRUE(testFile.getRoads()[0]->getTrafficLight(0)->properlyInitialized());
    EXPECT_EQ((unsigned int)1, testFile.getRoads()[0]->getTrafficLights().size());
    EXPECT_EQ((unsigned int)400, testFile.getRoads()[0]->getTrafficLight(0)->getPosition());
    EXPECT_EQ((int)20, testFile.getRoads()[0]->getTrafficLight(0)->getCyclus());
    EXPECT_EQ((int)2, testFile.getRoads()[0]->getVehicleAmount());
    for (int i = 0; i < testFile.getRoads()[0]->getVehicleAmount(); ++i) {
        EXPECT_TRUE(testFile.getRoads()[0]->getVehicle(i)->properlyInitialized());
        EXPECT_EQ((int)0, testFile.getRoads()[0]->getVehicle(i)->getSpeed());
    }
}

TEST(VehiclePosTest, Position){
    // test if the car position is the right position
    TrafficSimulation testFile(SIM1);
    EXPECT_TRUE(testFile.getRoads()[0]->getVehicle(0)->getNextVehicle() == NULL);
    EXPECT_TRUE(testFile.getRoads()[0]->getVehicle(0) == testFile.getRoads()[0]->getVehicle(1)->getNextVehicle());
}

TEST(FailTest, fails){
    // test on fails
    TrafficSimulation testFile(SIM3);
    EXPECT_NE((unsigned int)1, testFile.getRoads().size());
    EXPECT_FALSE(testFile.getRoads()[0]->getVehicle(0)->getVehiclePosition() == 0);
    EXPECT_NE(testFile.getRoads()[0]->getVehicle(0)->getRoad()->getRoadName(), "Groeneborgenlaan");
}

TEST(OnlyRoadTest, EmptyRoad){
    // test if there is an empty road
    TrafficSimulation testFile(SIM2);
    EXPECT_FALSE(testFile.getRoads().empty());
    EXPECT_TRUE(testFile.getVehicles().empty());
    EXPECT_TRUE(testFile.getLights().empty());
}

TEST(SimTest, simulation1){
    // test on simulation file 1, basic trafficSimulation
    TrafficSimulation testFile(SIM1);
    EXPECT_FALSE(testFile.getRoads()[0]->getVehicleAmount() == 0);
    testFile.startSimNoPrint();
    EXPECT_TRUE(testFile.getRoads()[0]->getVehicleAmount() == 0);
}

TEST(SimTest, simulation3){
    // test on simulation file 3, multiple roads
    TrafficSimulation testFile(SIM3);
    for (unsigned int i = 0; i < testFile.getRoads().size(); i++){
        EXPECT_FALSE(testFile.getRoads()[i]->getVehicleAmount() == 0);
    }
    testFile.startSimNoPrint();
    for (unsigned int i = 0; i < testFile.getRoads().size(); i++){
        EXPECT_TRUE(testFile.getRoads()[i]->getVehicleAmount() == 0);
    }
}

TEST(SimTest, simulation4){
    // test on simulation file 4, vehicle generator
    TrafficSimulation testFile(SIM4);
    EXPECT_FALSE(testFile.getVehicleGenerators().empty());
    EXPECT_TRUE(testFile.getVehicles().empty());
    testFile.startSimUntilCount();
    EXPECT_EQ((unsigned int)MAX_VEHICLES, testFile.getVehicles().size());
}

TEST(SimTest, simulation5){
    // test on simulation file 5, vehicle generator multiple roads
    TrafficSimulation testFile(SIM5);
    EXPECT_FALSE(testFile.getVehicleGenerators().empty());
    EXPECT_TRUE(testFile.getVehicles().empty());
    testFile.startSimUntilCount();
    EXPECT_NE((unsigned int)MAX_VEHICLES, testFile.getVehicles().size());
    EXPECT_EQ((unsigned int)MAX_VEHICLES * testFile.getVehicleGenerators().size(), testFile.getVehicles().size());
}

TEST(SimTest, simulation6){
    // test on simulation file 6, vehicle generator + normal vehicles
    TrafficSimulation testFile(SIM6);
    EXPECT_FALSE(testFile.getVehicleGenerators().empty());
    EXPECT_FALSE(testFile.getVehicles().empty());
    testFile.startSimUntilCount();
    EXPECT_FALSE(testFile.getVehicles().empty());
    EXPECT_TRUE(testFile.getRoads()[0]->getVehicleAmount() == 0);
    EXPECT_FALSE(testFile.getRoads()[1]->getVehicleAmount() == 0);
}

TEST(SimTest, simulationFail){
    //EXPECT_ANY_THROW(TrafficSimulation testFile(SIM7));
    //EXPECT_ANY_THROW(TrafficSimulation testFile(SIM8));
    //EXPECT_ANY_THROW(TrafficSimulation testFile(SIM9));
    EXPECT_ANY_THROW(TrafficSimulation testFile(SIM10));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}