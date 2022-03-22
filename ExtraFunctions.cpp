//==== libs ====//
#include <iostream>
#include <sstream>

using namespace std;

//==== Extra Functions ====//
int convertStrToInt(string input){
    int tempi = 0;
    stringstream temps(input);
    temps >> tempi;
    return tempi;
}

