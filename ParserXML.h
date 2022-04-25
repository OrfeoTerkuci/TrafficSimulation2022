#ifndef TRAFFICSIMULATION2022_PARSERXML_H
#define TRAFFICSIMULATION2022_PARSERXML_H

// custom headers
#include "TrafficSimulation.h"
#include "TrafficLight.h"
#include "Road.h"
#include "Vehicle.h"
#include "VehicleGenerator.h"
#include "CrossRoad.h"
#include "BusStop.h"

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

int convertStrToInt(string input){
    int tempi = 0;
    stringstream temps(input);
    temps >> tempi;
    return tempi;
}

bool parseBusStop(TiXmlElement* &root, TrafficSimulation &trafficSimulation){
    REQUIRE(trafficSimulation.properlyInitialized(), "TrafficSimulation was not initialized when calling parseBusStop");
    // create new object
    BusStop* busStop = new BusStop();

    // temp values
    string tempn;
    int tempi;

    // parsing
    for(TiXmlElement* elem = root->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement()) {
        string elemname = elem->Value();

        if(elem->NoChildren()){
            delete busStop;
            ENSURE(!elem->NoChildren(), "One of the parameters was empty");
            return false;
        }

        tempn = elem->GetText();

        if (elemname == BAANL){
            for (unsigned int i = 0; i < trafficSimulation.getRoads().size(); i++){
                if (trafficSimulation.getRoads()[i]->getRoadName() == tempn){
                    busStop->setRoad(trafficSimulation.getRoads()[i]);
                    trafficSimulation.getRoads()[i]->addBusStop(busStop);
                }
            }
        } else if (elemname == WACHTTIJD) {
            tempi = convertStrToInt(tempn);
            busStop->setWaitTime(tempi);
        } else if (elemname == POSITIE) {
            tempi = convertStrToInt(tempn);
            busStop->setPosition(tempi);
        }
        else{
            cout << "Not recognized parameter" << endl;
            return false;
        }
    }
    trafficSimulation.addBusStop(busStop);
    return true;
}

bool parseCrossRoad(TiXmlElement* &root, TrafficSimulation &trafficSimulation){
    REQUIRE(trafficSimulation.properlyInitialized(), "TrafficSimulation was not initialized when calling parseCrossRoad");
    // create new object
    CrossRoad* crossRoad = new CrossRoad();

    // temp values
    string tempn;
    int tempi;

    // parsing
    for(TiXmlElement* elem = root->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement()) {
        string elemname = elem->Value();

        if(elem->NoChildren()){
            delete crossRoad;
            ENSURE(!elem->NoChildren(), "One of the parameters was empty");
            return false;
        }
        tempn = elem->GetText();
        if (elemname == BAANL){
            TiXmlAttribute* atr = elem->FirstAttribute();
            string pos;
            if (atr != NULL){
                pos = atr->Value();
            }
            tempi = convertStrToInt(pos);
            for (unsigned int i = 0; i < trafficSimulation.getRoads().size(); ++i) {
                if (trafficSimulation.getRoads()[i]->getRoadName() == tempn){
                    crossRoad->addRoad(trafficSimulation.getRoads()[i], tempi);
                    trafficSimulation.getRoads()[i]->addCrossRoad(crossRoad);
                    break;
                }
            }
        }
    }
    if (crossRoad->getRoads().size() > 1){
        trafficSimulation.addCrossRoad(crossRoad);
        return true;
    }
    delete crossRoad;
    return false;
}


/**
     * REQUIRE(this->properlyInitialized(), "TrafficSimulation wasn't properly initialized when calling parseRoad");
     * REQUIRE(*typeid(root).name() == 'P' , "parseRoad was called with invalid parameter");
     * REQUIRE(!elem->NoChildren(), "One of the parameters was empty");
     * REQUIRE(tempi >= 0, "Road length is not valid");

     * @param root A pointer to a TiXmlElement
     * @return True if parsing was successful
    */
bool parseRoad(TiXmlElement* &root, TrafficSimulation &trafficSimulation){
    REQUIRE(trafficSimulation.properlyInitialized(), "TrafficSimulation was not initialized when calling parseRoad");
    REQUIRE(*typeid(root).name() == 'P' , "parseRoad was called with invalid parameter");
    // create road object
    Road *newRoad = new Road();

    // temp values
    string tempn;
    int tempi;

    // Parsing
    for(TiXmlElement* elem = root->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement()) {
        string elemName = elem->Value();

        if(elem->NoChildren()){
            delete newRoad;
            ENSURE(!elem->NoChildren(), "One of the parameters was empty");
            return false;
        }

        tempn = elem->GetText();


        if(elemName == NAAM){
            newRoad->setRoadName(tempn);
        }
        else if(elemName == LENGTE){
            tempi = convertStrToInt(tempn);
            if(tempi <= 0){
                delete newRoad;
                REQUIRE(tempi >= 0, "Road length is not valid");
                return false;
            }
            else{
                newRoad->setLength(tempi);
            }
        }
    }

    // Check if road already exists + add road
    if(newRoad->getLength() > 0 and !newRoad->getRoadName().empty()){
        if(!trafficSimulation.addRoad(newRoad)){
            delete newRoad;
            return false;
        }
        else{
            return true;
        }
    }
    return false;
}

bool setTypeParser(const string &tempn, Vehicle* &vehicle){
    if (tempn == AUTO){
        vehicle->setType(T_AUTO);
    }
    else if ( tempn == BUS ){
        vehicle->setType(T_BUS);
    }
    else if ( tempn == BRANDWEERWAGEN ){
        vehicle->setType(T_FIRETRUCK);
    }
    else if ( tempn == ZIEKENWAGEN ){
        vehicle->setType(T_AMBULANCE);
    }
    else if ( tempn == POLITIECOMBI ){
        vehicle->setType(T_POLICE);
    }
    else{
        return false;
    }
    vehicle->setStandardValues();
    return true;
}


/**
     * REQUIRE(this->properlyInitialized(), "TrafficSimulation wasn't properly initialized when calling parseVehicle");
     * REQUIRE(*typeid(root).name() == 'P' , "parseVehicle was called with invalid parameter");
     * REQUIRE(!elem->NoChildren(), "One of the parameters was empty");
     * REQUIRE(tempi > 0, "Position is not valid");

     * @param root A pointer to a TiXmlElement
     * @return True if parsing was successful
    */
bool parseVehicle(TiXmlElement* &root, TrafficSimulation &trafficSimulation){
    REQUIRE(trafficSimulation.properlyInitialized(), "TrafficSimulation was not initialized when calling parseVehicle");
    REQUIRE(*typeid(root).name() == 'P' , "parseVehicle was called with invalid parameter");
    Vehicle* vehicle = new Vehicle();

    string tempn;
    int tempi;

    for(TiXmlElement* elem = root->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement()) {
        string elemName = elem->Value();

        // if elem is empty, end parsing and return false
        if(elem->NoChildren()){
            delete vehicle;
            ENSURE(!elem->NoChildren(), "One of the parameters was empty");
            return false;
        }

        tempn = elem->GetText();

        if (elemName == TYPE){
            if(!setTypeParser(tempn, vehicle)){
                delete vehicle;
                return false;
            }
        }
        else if(elemName == BAANL){
            for (unsigned int i = 0; i < trafficSimulation.getRoads().size(); ++i) {
                if (tempn == trafficSimulation.getRoads()[i]->getRoadName()) {
                    vehicle->setRoad(trafficSimulation.getRoads()[i]);
                    trafficSimulation.getRoads()[i]->addVehicle(vehicle);
                    trafficSimulation.addVehicle(vehicle);
                    break;
                }
            }
        }
        else if(elemName == POSITIE){
            tempi = convertStrToInt(tempn);
            if (tempi < 0){
                delete vehicle;
                ENSURE(tempi > 0, "Position is not valid");
                return false;
            }
            vehicle->setPosition(tempi);
        }
    }

    return true;
}


/**
     * REQUIRE(this->properlyInitialized(), "TrafficSimulation wasn't properly initialized when calling parseTrafficLight");
     * REQUIRE(*typeid(root).name() == 'P' , "parseTrafficLight was called with invali parameter");
     * REQUIRE(!elem->NoChildren(), "One of the parameters was empty");
     * REQUIRE(tempi >= 0, "Cycle is not valid");
     * REQUIRE(tempi > 0, "Position is not valid");

     * @param root A pointer to a TiXmlElement
     * @return True if parsing was successful
    */
bool parseTrafficLight(TiXmlElement* &root, TrafficSimulation &trafficSimulation){
    REQUIRE(trafficSimulation.properlyInitialized(), "TrafficSimulation was not initialized when calling parseTrafficLight");
    REQUIRE(*typeid(root).name() == 'P' , "parseTrafficLight was called with invali parameter");
    // Create object
    TrafficLight* trafficLight = new TrafficLight();

    // Create temp values
    string tempn;
    int tempi;

    // Parsing
    for(TiXmlElement* elem = root->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement()) {
        string elemName = elem->Value();

        // if elem is empty, end parsing and return false
        if(elem->NoChildren()){
            delete trafficLight;
            ENSURE(!elem->NoChildren(), "One of the parameters was empty");
            return false;
        }

        tempn = elem->GetText();


        if(elemName == BAANL){
            for (unsigned int i = 0; i < trafficSimulation.getRoads().size(); ++i) {
                if (tempn == trafficSimulation.getRoads()[i]->getRoadName()) {
                    trafficLight->setRoad(trafficSimulation.getRoads()[i]);
                    break;
                }
            }
        }
        else if(elemName == POSITIE){
            tempi = convertStrToInt(elem->GetText());
            if (tempi < 0 || tempi > int(trafficLight->getRoad()->getLength()) ){
                delete trafficLight;
                ENSURE(false, "Position is not valid");
            }
            trafficLight->setPosition(tempi);
        }
        else if(elemName == CYCLUS){
            tempi = convertStrToInt(elem->GetText());
            if (tempi <= 0){
                delete trafficLight;
                ENSURE(tempi >= 0, "Cycle is not valid");
                return false;
            }
            trafficLight->setCyclus(tempi);
        }
    }

    // add traffic light to road
    for (unsigned int i = 0; i < trafficSimulation.getRoads().size(); ++i) {
        if (trafficSimulation.getRoads()[i] == trafficLight->getRoad()){
            trafficSimulation.getRoads()[i]->addLight(trafficLight);
            trafficSimulation.addTrafficLight(trafficLight);
            break;
        }
    }

    return true;
}


/**
     * REQUIRE(this->properlyInitialized(), "TrafficSimulation wasn't properly initialized when calling parseVehicleGenerator");
     * REQUIRE(*typeid(root).name() == 'P' , "parseVehicleGenerator was called with invalid parameter");
     * REQUIRE(!elem->NoChildren(), "One of the parameters was empty");
     * REQUIRE(tempf > 0, "Frequency is not valid");

     * @param root A pointer to a TiXmlElement
     * @return True if parsing was successful
    */
bool parseVehicleGenerator(TiXmlElement* &root, TrafficSimulation &trafficSimulation){
    REQUIRE(trafficSimulation.properlyInitialized(), "TrafficSimulation was not initialized when calling parseVehicleGenerator");
    REQUIRE(*typeid(root).name() == 'P' , "parseVehicleGenerator was called with invalid parameter");
    VehicleGenerator* vehicleGenerator = new VehicleGenerator();

    string tempn;
    int tempf;

    for(TiXmlElement* elem = root->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement()) {
        string elemName = elem->Value();

        // if elem is empty, end parsing and return false
        if(elem->NoChildren()){
            delete vehicleGenerator;
            ENSURE(!elem->NoChildren(), "One of the parameters was empty");
            return false;
        }

        tempn = elem->GetText();

        if (elemName == BAANL) {
            for (unsigned int i = 0; i < trafficSimulation.getRoads().size(); ++i) {
                if (tempn == trafficSimulation.getRoads()[i]->getRoadName()) {
                    vehicleGenerator->setRoad(trafficSimulation.getRoads()[i]);
                    if (!trafficSimulation.addVehicleGenerator(vehicleGenerator)){
                        delete vehicleGenerator;
                        return false;
                    }
                    break;
                }
            }
        }
        else if (elemName == FREQUENTIE) {
            tempf = convertStrToInt(elem->GetText());
            if (tempf < 0){
                delete vehicleGenerator;
                ENSURE(tempf > 0, "Frequency is not valid");
                return false;
            }
            vehicleGenerator->setFrequentie(tempf);
            // Set cooldown : 0 for instant generation upon simulation start
            vehicleGenerator->setCooldown(tempf);
        }
        if (tempn == AUTO){
                vehicleGenerator->setType(T_AUTO);
            }
            else if ( tempn == BUS ){
                vehicleGenerator->setType(T_BUS);
            }
            else if ( tempn == BRANDWEERWAGEN ){
                vehicleGenerator->setType(T_FIRETRUCK);
            }
            else if ( tempn == ZIEKENWAGEN ){
                vehicleGenerator->setType(T_AMBULANCE);
            }
            else if ( tempn == POLITIECOMBI ){
                vehicleGenerator->setType(T_POLICE);
            }
            else{
                // Set default type
                vehicleGenerator->setType(T_AUTO);
            }
    }
    return true;
}

void parseTrafficSimulationX(TrafficSimulation &trafficSimulation){
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
            if (!parseRoad(elem, trafficSimulation)) {
                cout << "Error: Could not make road" << endl;
            }
        } else if (elemName == VERKEERSLICHT) {
            if (!parseTrafficLight(elem, trafficSimulation)) {
                cout << "Error: Could not make traffic light" << endl;
            }
        } else if (elemName == VOERTUIG) {
            if (!parseVehicle(elem, trafficSimulation)) {
                cout << "Error: Could not make vehicle" << endl;
            }
        } else if (elemName == VOERTUIGGENERATOR) {
            if (!parseVehicleGenerator(elem, trafficSimulation)) {
                cout << "Error: Could not make vehicle generator" << endl;
            }
        } else if (elemName == KRUISPUNT) {
            if (!parseCrossRoad(elem, trafficSimulation)){
                cout << "Error: Could not make crossroad" << endl;
            }
        } else if (elemName == BUSHALTE) {
            if (!parseBusStop(elem, trafficSimulation)) {
                cout << "Error: Could not make bus stop" << endl;
            }
        }
    }
}

#endif //TRAFFICSIMULATION2022_PARSERXML_H
