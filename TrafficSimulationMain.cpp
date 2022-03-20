#include "TrafficSimulation.h"
#include "DesignByContract.h"
#include "Standard_Values.h"

using namespace std;

int main(){
// Task 1
//TrafficSimulation ts(SIM1); // Basic Simulation
//TrafficSimulation ts(SIM2); // Empty road simulation
//TrafficSimulation ts(SIM3); // Multiple Roads simulation
TrafficSimulation ts(SIM4); // VehicleGenerator sim
//ts.printAll();
ts.startSimulation();
return 0;
}