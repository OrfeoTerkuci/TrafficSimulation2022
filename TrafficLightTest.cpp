//
// Created by jason on 15/03/2022.
//


#include "gtest/gtest.h"
#include <iostream>

using namespace std;

#include "TrafficSimulation.h"
#include "Road.h"
#include "TrafficLight.h"
#include "Vehicle.h"

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
    EXPECT_TRUE(ts.properlyInitialized());
}

TEST(ParserTest, Parser){
    TrafficSimulation testFile("Simulation1.xml");
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
    TrafficSimulation testFile("Simulation1.xml");
    EXPECT_TRUE(testFile.getRoads()[0]->getVehicle(0)->getNextVehicle() == NULL);
    EXPECT_TRUE(testFile.getRoads()[0]->getVehicle(0) == testFile.getRoads()[0]->getVehicle(1)->getNextVehicle());
}

TEST(FailTest, fails){
    TrafficSimulation testFile("Simulation3.xml");
    EXPECT_NE((unsigned int)1, testFile.getRoads().size());
    EXPECT_FALSE(testFile.getRoads()[0]->getVehicle(0)->getVehiclePosition() == 0);
    EXPECT_NE(testFile.getRoads()[0]->getVehicle(0)->getRoad()->getRoadName(), "Groeneborgenlaan");
}

TEST(SimTest, simulation){
    TrafficSimulation testFile("Simulation1.xml");
    EXPECT_FALSE(testFile.getRoads()[0]->getVehicleAmount() == 0);
    testFile.startSimNoPrint();
    EXPECT_TRUE(testFile.getRoads()[0]->getVehicleAmount() == 0);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}