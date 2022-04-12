#include "gtest/gtest.h"
#include <iostream>
#include <fstream>

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

TEST(SimTest, simulationSucces){
    // test on files that does suppose to work
    EXPECT_NO_THROW(TrafficSimulation testFile(SIM1));
    EXPECT_NO_THROW(TrafficSimulation testFile2(SIM2));
    EXPECT_NO_THROW(TrafficSimulation testFile3(SIM3));
    EXPECT_NO_THROW(TrafficSimulation testFile4(SIM4));
    EXPECT_NO_THROW(TrafficSimulation testFile5(SIM5));
    EXPECT_NO_THROW(TrafficSimulation testFile6(SIM6));
}

TEST(SimTest, simulationFail){
    // log file
    ofstream logOutput;

    // write in a file
    logOutput.open("TestLog/newLog.txt");

    ASSERT_EXIT(TrafficSimulation testFile(SIM7) , testing::KilledBySignal(SIGABRT) , "Road length is not valid");
    //EXPECT_ANY_THROW(TrafficSimulation testFile(SIM8));
    ASSERT_EXIT(TrafficSimulation testFile(SIM8) , testing::KilledBySignal(SIGABRT) , "Position is not valid");
    //EXPECT_ANY_THROW(TrafficSimulation testFile(SIM9));
    ASSERT_EXIT(TrafficSimulation testFile(SIM9) , testing::KilledBySignal(SIGABRT) , "Position is not valid");
    //EXPECT_ANY_THROW(TrafficSimulation testFile(SIM10));
    ASSERT_EXIT(TrafficSimulation testFile(SIM10) , testing::KilledBySignal(SIGABRT) , "Frequency is not valid");
    //EXPECT_ANY_THROW(TrafficSimulation testFile(SIM11));
    ASSERT_EXIT(TrafficSimulation testFile(SIM11) , testing::KilledBySignal(SIGABRT) , "One of the parameters was empty");
}

TEST(FunctionsTest , Vehicle_Test){
    Road* testRoad = new Road(500 , "TestRoad");
    Vehicle testVehicle(50 , 100);
    const unsigned int testPosition1 = 100;
    const unsigned int testPosition2 = 6;

    EXPECT_TRUE( testVehicle.properlyInitialized() );
    // Position getter and setter test
    EXPECT_EQ( testVehicle.getVehiclePosition() , testPosition1 );
    testVehicle.setPosition(testPosition2);
    EXPECT_EQ( testVehicle.getVehiclePosition() , testPosition2);
    // Road getter and setter test
    EXPECT_NE(testVehicle.getRoad() , testRoad );
    testVehicle.setRoad(testRoad);
    EXPECT_EQ(testVehicle.getRoad() , testRoad );
    EXPECT_EQ( testVehicle.getAcceleration() , 0.0 );
    testVehicle.setAcceleration(4.7);
    EXPECT_EQ( testVehicle.getAcceleration() , 4.7 );
    EXPECT_EQ( testVehicle.getSpeed() , 50 );
    testVehicle.setSpeed(4);
    EXPECT_EQ( testVehicle.getSpeed() , 4 );
    EXPECT_EQ( testVehicle.getCurrentMaxSpeed() , MAX_SPEED);
    testVehicle.setCurrentMaxSpeed(5);
    EXPECT_EQ( testVehicle.getCurrentMaxSpeed() , 5);
    EXPECT_NE( testVehicle.getStatus() , idle );
     testVehicle.setStatus(idle);
    EXPECT_EQ( testVehicle.getStatus() , idle );
    EXPECT_EQ( testVehicle.getStatusString() , "Stopped / Idle" );
}

TEST(FunctionsTest , Road_Test){
    Road* testRoad = new Road();
    Vehicle* testVehicle = new Vehicle();
    vector<Vehicle*> vehiclesVector;
    vehiclesVector.push_back(testVehicle);
    TrafficLight* testLight = new TrafficLight(20 , testRoad);
    vector<TrafficLight*> lightsVector;
    lightsVector.push_back(testLight);
    vector<TrafficLight*> emptyLightsVector;

    EXPECT_TRUE( testRoad->properlyInitialized() );
    // Length getter and setter test
    const unsigned int testLength1 = 0;
    const unsigned int testLength2 = 5;
    EXPECT_EQ( testRoad->getLength() , testLength1 );
    testRoad->setLength(5);

    EXPECT_EQ(testRoad->getLength() , testLength2);
    // Name getter and setter test
    EXPECT_EQ( testRoad->getRoadName() , "" );
    testRoad->setRoadName("Middelheimlaan" );
    EXPECT_EQ( testRoad->getRoadName() , "Middelheimlaan" );
    // Vehicle addition test
    EXPECT_EQ( testRoad->getVehicleAmount() , 0 );
    EXPECT_NE( testRoad->getVehicles() , vehiclesVector );
    testRoad->addVehicle(testVehicle);
    EXPECT_EQ( testRoad->getVehicleAmount() , 1 );
    EXPECT_EQ( testRoad->getVehicles() , vehiclesVector );
    EXPECT_EQ( testRoad->getVehicle(0) , testVehicle );
    // Vehicle removal test
    testRoad->removeVehicle(testVehicle);
    EXPECT_EQ( testRoad->getVehicleAmount() , 0);
    EXPECT_NE( testRoad->getVehicles() , vehiclesVector );
    // Vehicles setter test
    testRoad->setVehicles(vehiclesVector);
    EXPECT_EQ( testRoad->getVehicleAmount() , 1 );
    EXPECT_EQ( testRoad->getVehicles() , vehiclesVector );
    // TrafficLights addition test
    EXPECT_EQ( testRoad->getTrafficLightsAmount() , 0);
    EXPECT_NE( testRoad->getTrafficLights() , lightsVector );
    testRoad->addLight(testLight);
    EXPECT_EQ( testRoad->getTrafficLightsAmount() , 1);
    EXPECT_EQ( testRoad->getTrafficLight(0) , testLight );
    EXPECT_EQ( testRoad->getTrafficLights() , lightsVector );
    // TrafficLights setter test
    testRoad->setTrafficLights(emptyLightsVector);
    EXPECT_EQ( testRoad->getTrafficLightsAmount() , 0);
    EXPECT_NE( testRoad->getTrafficLights() , lightsVector );
    testRoad->setTrafficLights(lightsVector);
    EXPECT_EQ( testRoad->getTrafficLightsAmount() , 1);
    EXPECT_EQ( testRoad->getTrafficLight(0) , testLight );
    EXPECT_EQ( testRoad->getTrafficLights() , lightsVector );

}

TEST(FunctionsTest , TrafficLight_Test){
    Road* testRoad = new Road(60 , "TestRoad");
    Road* testRoad2 = new Road(500 , "TestRoad2");
    Vehicle* testVehicle = new Vehicle(10 , 50);
    testRoad2->addVehicle(testVehicle);
    TrafficLight testLight(20 , testRoad);
    EXPECT_TRUE( testLight.properlyInitialized() );
    // Color getter and setter test
    EXPECT_EQ( testLight.getCurrentColor() , red );
    testLight.setCurrentColor(green);
    EXPECT_EQ( testLight.getCurrentColor() , green );
    // Position getter and setter test
    const unsigned int testPosition = 30;
    EXPECT_NE( testLight.getPosition() , testPosition );
    testLight.setPosition(30);
    EXPECT_EQ( testLight.getPosition() , testPosition );
    // Cyclus getter and setter test
    EXPECT_EQ( testLight.getCyclus() , 20 );
    testLight.setCyclus(100);
    EXPECT_EQ( testLight.getCyclus() , 100 );
    // Road getter and setter test
    EXPECT_EQ( testLight.getRoad() , testRoad );
    testLight.setRoad(testRoad2);
    EXPECT_NE( testLight.getRoad() , testRoad );
    // Nearest vehicle getter test
    testRoad->addVehicle(testVehicle);
    EXPECT_EQ( testLight.getNearestVehicle() , testVehicle);
}

TEST(FunctionsTest , VehicleGenerator_Test){
    VehicleGenerator testGenerator;
    Road* testRoad = new Road(500 , "Unnamed");
    EXPECT_TRUE( testGenerator.properlyInitialized() );
    // Test cooldown getter and setter
    EXPECT_EQ( testGenerator.getCooldown() , 0);
    testGenerator.setCooldown(3);
    EXPECT_EQ( testGenerator.getCooldown() , 3 );
    // Test frequency getter and setter
    EXPECT_EQ( testGenerator.getFrequentie() , 0 );
    testGenerator.setFrequentie(5);
    EXPECT_EQ( testGenerator.getFrequentie() , 5 );
    // Test road getter and setter
    EXPECT_NE( testGenerator.getRoad() , testRoad );
    testGenerator.setRoad(testRoad);
    EXPECT_EQ( testGenerator.getRoad() , testRoad );
    // Test simulation function
    for (int i = 0; i < 3; ++i) {
        EXPECT_FALSE( testGenerator.simulate() );
    }
    EXPECT_TRUE( testGenerator.simulate() );
    EXPECT_FALSE( testGenerator.simulate() );

}

TEST(SimTest, TypeTest){
    TrafficSimulation ts(SIM14);
    for (int i = 0; i < ts.getVehicles(); ++i) {
        if (ts.getVehicles()[i]->getType() )
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}