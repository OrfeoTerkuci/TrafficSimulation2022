// custom headers
#include "TrafficSimulation.h"
#include "TrafficLight.h"
#include "Road.h"
#include "Vehicle.h"
#include "VehicleGenerator.h"
#include "tinyxml/tinyxml.h"
#include "Standard_Values.h"
#include "DesignByContract.h"

// build in libs
#include <iostream>
#include <string>
#include <stdexcept>
#include <typeinfo>
#include <sstream>

using namespace std;

bool parseRoad(TiXmlElement* &root){
    return false;
}

bool parseVehicle(TiXmlElement* &root){
    return false;
}

bool parseTrafficLight(TiXmlElement* &root){
    return false;
}

bool parseVehicleGenerator(TiXmlElement* &root){
    return false;
}

void  parseTrafficSimulation(TrafficSimulation &trafficSimulation){
    TiXmlDocument doc;
    // File readable detection with error message
    try{
        if(!doc.LoadFile(trafficSimulation.getFilename().c_str())) {
            cerr << doc.ErrorDesc() << endl;
            throw 1;
        }
    }

    catch(int error){
        if(error == 1){
            cout << "File not readable" << endl;
        }
    }

    // Check if file has elements to parse
    TiXmlElement* root = doc.FirstChildElement();

    if(root == NULL) {
        cerr << "Failed to load file: No root element." << endl;
        doc.Clear();
    }

    // Parsing of data
    for(TiXmlElement* elem = root->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement()) {
        string elemName = elem->Value();
        if (elemName == BAANU) {
            if (!parseRoad(elem)) {
                cout << "Error: Could not make road" << endl;
            }
        } else if (elemName == VERKEERSLICHT) {
            if (!parseTrafficLight(elem)) {
                cout << "Error: Could not make traffic light" << endl;
            }
        } else if (elemName == VOERTUIG) {
            if (!parseVehicle(elem)) {
                cout << "Error: Could not make vehicle" << endl;
            }
        } else if (elemName == VOERTUIGGENERATOR) {
            if (!parseVehicleGenerator(elem)) {
                cout << "Error: Could not make vehicle generator" << endl;
            }
        }
    }
}