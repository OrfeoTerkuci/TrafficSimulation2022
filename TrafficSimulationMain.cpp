#include "TrafficSimulation.h"
#include "DesignByContract.h"
#include "Standard_Values.h"
using namespace std;

int main(){
//* Task 1 *//

//==== Normal simulation files ====//
//TrafficSimulation ts(SIM0); // Single vehicle , long road
//TrafficSimulation ts(SIM1); // Basic Simulation
//TrafficSimulation ts(SIM2); // Empty road simulation
//TrafficSimulation ts(SIM3); // Multiple Roads simulation

//==== Vehicle generator files ====//
//TrafficSimulation ts(SIM4); // VehicleGenerator sim
//TrafficSimulation ts(SIM5); // VehicleGenerator sim with multiple roads
//TrafficSimulation ts(SIM6); // VehicleGenerator sim and with cars on different roads

//==== Files with errors ====//
//TrafficSimulation ts(SIM7); // Normal simulation, with invalid road length
//TrafficSimulation ts(SIM8); // Normal simulation, with invalid traffic-light position
//TrafficSimulation ts(SIM9); // Normal simulation, with invalid vehicle position
//TrafficSimulation ts(SIM10); // Vehicle generator simulation, with invalid vehicle generator frequencies
//TrafficSimulation testFile(SIM11); // Normal simulation, with empty parameter for road

//==== Crossroad files ====//
//TrafficSimulation ts(SIM12);

//==== Busstop ====//
//TrafficSimulation ts(SIM13);

//==== Vehicle Type ====//
//TrafficSimulation ts(SIM14);

//==== Different types of vehicles ====//
TrafficSimulation ts(SIM15);

//==== Crossroads ====//
//TrafficSimulation ts(SIM16);

//==== BusStop + Bus ====//
//TrafficSimulation ts(SIM17);

//==== Simulation functions ====//
//ts.printAll();
//ts.startSimulation(false, false, true); // Simulates until there is a maximum vehicle count reached --> Standard_Values --> MAX_VEHICLES
ts.startSimulation(); // Simulate current loaded file

return 0;
}