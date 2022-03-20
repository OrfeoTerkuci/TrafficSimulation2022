#include "TrafficSimulation.h"
#include "DesignByContract.h"
#include "Standard_Values.h"

using namespace std;

int main(){
// Task 1
//TrafficSimulation ts(SIM1); // Basic Simulation
//TrafficSimulation ts(SIM2); // Empty road simulation
//TrafficSimulation ts(SIM3); // Multiple Roads simulation
//TrafficSimulation ts(SIM4); // VehicleGenerator sim
//TrafficSimulation ts(SIM5); // VehicleGenerator sim with multiple roads
TrafficSimulation ts(SIM6); // VehicleGenerator sim and with cars on differebt roads

//ts.printAll();
ts.startSimUntilCount();
//ts.startSimulation();
return 0;
}