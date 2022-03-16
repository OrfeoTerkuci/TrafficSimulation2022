#include "TrafficSimulation.h"
#include "Exceptions.h"
#include "DesignByContract.h"
#include "Standard_Values.h"

using namespace std;

int main(){
TrafficSimulation ts("Simulation3.xml");
ts.print();
return 0;
}