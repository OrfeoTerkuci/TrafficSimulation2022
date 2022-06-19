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

    string filename;
    filename = TESTLOG;
    filename += BUSLOG;

    fstream log;
    log.open(filename.c_str(), ios::out| ios::trunc);

    // create new object
    BusStop* busStop = new BusStop();

    // temp values
    string tempn;
    int tempi;
    bool failed = true;
    bool exists = false;

    // parsing
    for(TiXmlElement* elem = root->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement()) {
        string elemname = elem->Value();

        if(elem->NoChildren()){
            busStop->setRoad(trafficSimulation.getDummyRoad());
            busStop->setPosition(0);
            busStop->setWaitTime(0);
            failed = false;
            log.close();
            log.open(filename.c_str(), ios::out | ios::trunc);
            log << "One of the elements had no value assigned\n";
            log.close();
            return false;
        }

        tempn = elem->GetText();
        if (elemname == BAANL){
            for (unsigned int i = 0; i < trafficSimulation.getRoads().size(); i++){
                if (trafficSimulation.getRoads()[i]->getRoadName() == tempn){
                    busStop->setRoad(trafficSimulation.getRoads()[i]);
                    trafficSimulation.getRoads()[i]->addBusStop(busStop);
                    log << "road found\n";
                    exists = true;
                }
            }
            if (!exists){
                log << "road not found\n";
                failed = false;
            }
        } else if (elemname == WACHTTIJD) {
            tempi = convertStrToInt(tempn);
            if (tempi < 1){
                failed = false;
                log << "Cycle time was lower than 1\n";
            }
            else {
                busStop->setWaitTime(tempi);
                busStop->setCooldown(tempi);
                log << "Cycle time was higher than 0\n";
            }
        } else if (elemname == POSITIE) {
            tempi = convertStrToInt(tempn);
            if (tempi < 1){
                failed = false;
                log << "Position was lower than 1\n";
            }
            else {
                busStop->setPosition(tempi);
                log << "Position was higher than 0\n";
            }
        }
        else{
            cout << "Not recognized parameter" << endl;
            log << "Not reconizable parameter\n";
            failed = false;
        }
    }
    if (failed){
        trafficSimulation.addBusStop(busStop);
    }
    log.close();
    return failed;
}

bool parseCrossRoad(TiXmlElement* &root, TrafficSimulation &trafficSimulation){
    REQUIRE(trafficSimulation.properlyInitialized(), "TrafficSimulation was not initialized when calling parseCrossRoad");

    string filename;
    filename = TESTLOG;
    filename += CROSSROADLOG;

    fstream log;
    log.open(filename.c_str(), ios::out| ios::trunc);

    // create new object
    CrossRoad* crossRoad = new CrossRoad();

    // temp values
    string tempn;
    int tempi;
    bool failed = true;

    // parsing
    for(TiXmlElement* elem = root->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement()) {
        string elemname = elem->Value();

        if(elem->NoChildren()){
            delete crossRoad;
            log.open(filename.c_str(), ios::out | ios::trunc);
            log << "One of the elements had no value assigned\n";
            log.close();
            return false;
        }
        tempn = elem->GetText();
        if (elemname == BAANL){
            TiXmlAttribute* atr = elem->FirstAttribute();
            string pos;
            if (atr != NULL){
                log << "Position was assigned\n";
                pos = atr->Value();
            }
            else{
                pos = "0";
                log << "Position was not assigned\n";
                failed = false;
            }
            tempi = convertStrToInt(pos);
            if (tempi > 1){
                log << "Position value is higher than 1\n";
            }
            else {
                log << "Position was lower than 1\n";
                failed = false;
            }
            bool roadFound = false;
            for (unsigned int i = 0; i < trafficSimulation.getRoads().size(); ++i) {
                if (trafficSimulation.getRoads()[i]->getRoadName() == tempn){
                    crossRoad->addRoad(trafficSimulation.getRoads()[i], tempi);
                    trafficSimulation.getRoads()[i]->addCrossRoad(crossRoad);
                    roadFound = true;
                    break;
                }
            }
            if (roadFound){
                log << "Road is found\n";
            }
            else {
                log << "Road not found\n";
                failed = false;
            }
        }
    }
    bool end = false;
    if (crossRoad->getRoads().size() > 1 and failed){
        trafficSimulation.addCrossRoad(crossRoad);
        end = true;
    }

    log.close();
    return end;
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

    string filename;
    filename = TESTLOG;
    filename += ROADLOG;

    fstream log;
    log.open(filename.c_str(), ios::out| ios::trunc);


    // create road object
    Road *newRoad = new Road();

    // temp values
    string tempn;
    int tempi;

    // Parsing
    for(TiXmlElement* elem = root->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement()) {
        string elemName = elem->Value();

        if(elem->NoChildren()){
            log.close();
            log.open(filename.c_str(), ios::out | ios::trunc);
            log << "One of the elements had no value assigned\n";
            log.close();
            return false;
        }

        tempn = elem->GetText();

        if(elemName == NAAM){
            newRoad->setRoadName(tempn);
        }
        else if(elemName == LENGTE){
            tempi = convertStrToInt(tempn);
            if(tempi <= 0){
                newRoad->setLength(0);
                log << "Road length was assigned lower than 1\n";
            }
            else{
                newRoad->setLength(tempi);
                log << "Road length was assigned higher than 1\n";
            }
        }
    }

    // Check if road already exists + add road
    if(newRoad->getLength() > 0 and !newRoad->getRoadName().empty()){
        if(!trafficSimulation.addRoad(newRoad)){
            log << "Road was not unique\n";
            log.close();
            return false;
        }
        else{
            log << "Road is unique\n";
            log.close();
            return true;
        }
    }
    log.close();
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

    string filename;
    filename = TESTLOG;
    filename += VEHICLELOG;

    fstream log;
    log.open(filename.c_str(), ios::out| ios::trunc);

    Vehicle* vehicle = new Vehicle();

    string tempn;
    int tempi;
    bool failed = true;
    bool roadExist = false;

    for(TiXmlElement* elem = root->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement()) {
        string elemName = elem->Value();

        // if elem is empty, end parsing and return false
        if(elem->NoChildren()){
            vehicle->setType(T_NULL);
            vehicle->setPosition(0);
            if (roadExist){
                vehicle->getRoad()->removeVehicle(vehicle);
            }
            vector<Vehicle*> tempVec = trafficSimulation.getVehicles();
            if (!trafficSimulation.getVehicles().empty() and trafficSimulation.getVehicles()[trafficSimulation.getVehicles().size()-1] == vehicle){
                tempVec.pop_back();
                trafficSimulation.setVehicles(tempVec);
            }
            vehicle->setRoad(trafficSimulation.getDummyRoad());
            log.close();
            log.open(filename.c_str(), ios::out | ios::trunc);
            log << "One of the elements had no value assigned\n";
            log.close();
            return false;
        }

        tempn = elem->GetText();

        if (elemName == TYPE){
            if(!setTypeParser(tempn, vehicle)){
                vehicle->setType(T_NULL);
                log << "Type not found\n";
                failed = false;
            }
            else {
                log << "Type was found\n";
            }
        }
        else if(elemName == BAANL){
            for (unsigned int i = 0; i < trafficSimulation.getRoads().size(); ++i) {
                if (tempn == trafficSimulation.getRoads()[i]->getRoadName()) {
                    vehicle->setRoad(trafficSimulation.getRoads()[i]);
                    trafficSimulation.getRoads()[i]->addVehicle(vehicle);
                    trafficSimulation.addVehicle(vehicle);
                    roadExist = true;
                    break;
                }
            }
            if (roadExist){
                log << "Road was found\n";
            }
            else {
                log << "Road was not found\n";
                failed = false;
            }
        }
        else if(elemName == POSITIE){
            tempi = convertStrToInt(tempn);
            if (tempi < 0){
                vehicle->setPosition(0);
                log << "Posistion was assigned lower than 0\n";
                failed = false;
            }
            else if ((unsigned) tempi > vehicle->getRoad()->getLength()){
                vehicle->setPosition(vehicle->getRoad()->getLength());
                log << "Position was assigned higher than road length\n";
                failed = false;
            }
            else {
                vehicle->setPosition(tempi);
                log << "Position was assigned higher than 0\n";
            }
        }
    }
    if (!failed){
        vehicle->setType(T_NULL);
        vehicle->setPosition(0);
        if (roadExist){
            vehicle->getRoad()->removeVehicle(vehicle);
        }
        vector<Vehicle*> tempVec = trafficSimulation.getVehicles();
        if (!trafficSimulation.getVehicles().empty() and trafficSimulation.getVehicles()[trafficSimulation.getVehicles().size()-1] == vehicle){
            tempVec.pop_back();
            trafficSimulation.setVehicles(tempVec);
        }
        vehicle->setRoad(trafficSimulation.getDummyRoad());
    }
    log.close();
    return failed;
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

    string filename;
    filename = TESTLOG;
    filename += TRAFFICLIGHTLOG;

    fstream log;
    log.open(filename.c_str(), ios::out| ios::trunc);

    // Create object
    TrafficLight* trafficLight = new TrafficLight();

    // Create temp values
    string tempn;
    int tempi;
    bool failed = true;

    // Parsing
    for(TiXmlElement* elem = root->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement()) {
        string elemName = elem->Value();

        // if elem is empty, end parsing and return false
        if(elem->NoChildren()){
            trafficLight->setPosition(0);
            trafficLight->setRoad(trafficSimulation.getDummyRoad());
            trafficLight->setCyclus(0);
            log.close();
            log.open(filename.c_str(), ios::out | ios::trunc);
            log << "One of the elements had no value assigned\n";
            log.close();
            return false;
        }

        tempn = elem->GetText();

        bool roadExist = false;
        if(elemName == BAANL){
            for (unsigned int i = 0; i < trafficSimulation.getRoads().size(); ++i) {
                if (tempn == trafficSimulation.getRoads()[i]->getRoadName()) {
                    trafficLight->setRoad(trafficSimulation.getRoads()[i]);
                    roadExist = true;
                    break;
                }
            }
            if (roadExist){
                log << "Road found\n";
            }
            else {
                log << "Road not found\n";
                failed = false;
            }
        }
        else if(elemName == POSITIE){
            tempi = convertStrToInt(elem->GetText());
            if (tempi < 0 || tempi > int(trafficLight->getRoad()->getLength()) ){
                trafficLight->setPosition(0);
                log << "Position was assigned higher than road length or lower than 0\n";
                failed = false;
            }
            else {
                log << "Position is valid\n";
                trafficLight->setPosition(tempi);
            }
        }
        else if(elemName == CYCLUS){
            tempi = convertStrToInt(elem->GetText());
            if (tempi <= 0){
                trafficLight->setCyclus(0);
                log << "Cycle time was assigned lower than 1\n";
                failed = false;
            }
            else {
                log << "Cycle time is valid\n";
                trafficLight->setCyclus(tempi);
            }
        }
    }

    // add traffic light to road
    if (failed){
        for (unsigned int i = 0; i < trafficSimulation.getRoads().size(); ++i) {
            if (trafficSimulation.getRoads()[i] == trafficLight->getRoad()){
                trafficSimulation.getRoads()[i]->addLight(trafficLight);
                trafficSimulation.addTrafficLight(trafficLight);
                break;
            }
        }
    }
    log.close();
    return failed;
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

    string filename;
    filename = TESTLOG;
    filename += VEHICLEGENERATORLOG;

    fstream log;
    log.open(filename.c_str(), ios::out| ios::trunc);

    VehicleGenerator* vehicleGenerator = new VehicleGenerator();

    string tempn;
    int tempf;
    bool failed = true;
    bool exist = false;

    for(TiXmlElement* elem = root->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement()) {
        string elemName = elem->Value();

        // if elem is empty, end parsing and return false
        if(elem->NoChildren()){
            vehicleGenerator->setType(T_NULL);
            vehicleGenerator->setRoad(trafficSimulation.getDummyRoad());
            vehicleGenerator->setFrequentie(0);
            vehicleGenerator->setCooldown(0);
            log.close();
            log.open(filename.c_str(), ios::out | ios::trunc);
            log << "One of the elements had no value assigned\n";
            log.close();
            return false;
        }

        tempn = elem->GetText();

        if (elemName == BAANL) {
            for (unsigned int i = 0; i < trafficSimulation.getRoads().size(); ++i) {
                if (tempn == trafficSimulation.getRoads()[i]->getRoadName()) {
                    vehicleGenerator->setRoad(trafficSimulation.getRoads()[i]);
                    exist = true;
                    /*if (!trafficSimulation.addVehicleGenerator(vehicleGenerator)){
                        vehicleGenerator->setRoad(NULL);
                        return false;
                    }*/
                    break;
                }
            }
            if (exist){
                log << "Road was found\n";
            }
            else {
                log << "Road was nit found\n";
                failed = false;
            }
        }
        else if (elemName == FREQUENTIE) {
            tempf = convertStrToInt(elem->GetText());
            if (tempf <= 0){
                vehicleGenerator->setFrequentie(0);
                log << "Frequency was assigned lower than 1\n";
                failed = false;
            }
            else {
                vehicleGenerator->setFrequentie(tempf);
                // Set cooldown : 0 for instant generation upon simulation start
                vehicleGenerator->setCooldown(tempf);
                log << "Frequency was assigned higher than 1\n";
            }
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
    if (failed){
        trafficSimulation.addVehicleGenerator(vehicleGenerator);
    }
    log.close();
    return failed;
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

    // log file
    ofstream logOutput;

    // write in a file
    logOutput.open("TestLog/newLog.txt");

    // Parsing of data
    for(TiXmlElement* elem = root->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement()) {
        string elemName = elem->Value();
        if (elemName == BAANU) {
            if (!parseRoad(elem, trafficSimulation)) {
                //cout << "Error: Could not make road" << endl;
                logOutput << false << '\n';
            } else {
                logOutput << true << '\n';
            }
        } else if (elemName == VERKEERSLICHT) {
            if (!parseTrafficLight(elem, trafficSimulation)) {
                //cout << "Error: Could not make traffic light" << endl;
                logOutput << false << '\n';
            } else {
                logOutput << true << '\n';
            }
        } else if (elemName == VOERTUIG) {
            if (!parseVehicle(elem, trafficSimulation)) {
                //cout << "Error: Could not make vehicle" << endl;
                logOutput << false << '\n';
            } else {
                logOutput << true << '\n';
            }
        } else if (elemName == VOERTUIGGENERATOR) {
            if (!parseVehicleGenerator(elem, trafficSimulation)) {
                //cout << "Error: Could not make vehicle generator" << endl;
                logOutput << false << '\n';
            } else {
                logOutput << true << '\n';
            }
        } else if (elemName == KRUISPUNT) {
            if (!parseCrossRoad(elem, trafficSimulation)){
                //cout << "Error: Could not make crossroad" << endl;
                logOutput << false << '\n';
            } else {
                logOutput << true << '\n';
            }
        } else if (elemName == BUSHALTE) {
            if (!parseBusStop(elem, trafficSimulation)) {
                //cout << "Error: Could not make bus stop" << endl;
                logOutput << false << '\n';
            } else {
                logOutput << true << '\n';
            }
        }
    }
}

#endif //TRAFFICSIMULATION2022_PARSERXML_H
