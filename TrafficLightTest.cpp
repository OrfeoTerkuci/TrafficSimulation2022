//
// Created by jason on 15/03/2022.
//


#include <iostream>
#include "gtest/gtest.h"

#include "TrafficSimulation.h"

using namespace std;

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
    TrafficSimulation ts_;
};

TEST_F(TrafficSimulationTest, DefaultConstructor){
    EXPECT_TRUE(ts_.properlyInitialized());
}



int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}