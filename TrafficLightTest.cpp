//
// Created by jason on 15/03/2022.
//

#include "TrafficSimulation.h"
#include "gtest/gtest.h"

#include <iostream>

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

TEST(TrafficSimulationTest DefaultConstructor){
    EXPECT_TRUE(ts_.)
}