#include "TrafficSimulation.h"
#include "Exceptions.h"
#include "DesignByContract.h"
#include "Standard_Values.h"

using namespace std;

int main(){
//TrafficSimulation ts(SIM1);
//TrafficSimulation ts(SIM2);
//TrafficSimulation ts(SIM3);
TrafficSimulation ts(SIM4);
//ts.printAll();
ts.startSimUntilCount();
return 0;
}