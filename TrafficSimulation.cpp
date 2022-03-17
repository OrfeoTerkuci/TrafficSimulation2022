// custom libs
#include "TrafficSimulation.h"
#include "Road.h"
#include "TrafficLight.h"
#include "Vehicle.h"
#include "Standard_Values.h"

// c++ libs
#include <stdexcept>

//==== Parsing FUnctions ====//
bool TrafficSimulation::parseRoad(TiXmlElement* &root){
    // create road object
    Road *newRoad = new Road();

    // temp values
    string tempn;
    unsigned int tempi;

    // Parsing
    for(TiXmlElement* elem = root->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement()) {
        string elemName = elem->Value();
        if(elemName == NAAM){
            tempn = elem->GetText();
            if(tempn.empty()){
                delete newRoad;
                return false;
            }
            else{
                newRoad->setRoadName(tempn);
            }
        }
        else if(elemName == LENGTE){
            tempi = atoi(elem->GetText());
            if(tempi == 0){
                delete newRoad;
                return false;
            }
            else{
                newRoad->setLength(tempi);
            }
        }
    }

    // Check if road already exists + add road
    if(newRoad->getLength() > 0 and !newRoad->getRoadName().empty()){
        if(!this->addRoad(newRoad)){
            delete newRoad;
            return false;
        }
        else{
            return true;
        }
    }
    return false;
}

bool TrafficSimulation::parseTrafficLight(TiXmlElement* &root){
    // Create object
    TrafficLight* trafficLight = new TrafficLight();

    // Create temp values
    string tempn;
    unsigned int tempi;

    // Parsing
    for(TiXmlElement* elem = root->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement()) {
        string elemName = elem->Value();
        tempn = elem->GetText();

        // if elem is empty, end parsing and return false
        if(tempn.empty()){
            delete trafficLight;
            return false;
        }

        if(elemName == BAANL){
            for (unsigned int i = 0; i < this->roads.size(); ++i) {
                if (tempn == this->roads[i]->getRoadName()) {
                    trafficLight->setRoad(this->roads[i]);
                    break;
                }
            }
        }
        else if(elemName == POSITIE){
            tempi = atoi(elem->GetText());
            trafficLight->setPosition(tempi);
        }
        else if(elemName == CYCLUS){
            tempi = atoi(elem->GetText());
            trafficLight->setCyclus(tempi);
        }
    }

    // add traffic light to road
    for (unsigned int i = 0; i < this->roads.size(); ++i) {
        if (this->roads[i] == trafficLight->getRoad()){
            this->roads[i]->addLight(trafficLight);
            this->addTrafficLight(trafficLight);
            break;
        }
    }

    return true;
}

bool TrafficSimulation::parseVehicle(TiXmlElement* &root){
    Vehicle* vehicle = new Vehicle();

    string tempn;
    unsigned int tempi;

    for(TiXmlElement* elem = root->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement()) {
        string elemName = elem->Value();
        tempn = elem->GetText();

        // if elem is empty, end parsing and return false
        if(tempn.empty()){
            delete vehicle;
            return false;
        }

        if(elemName == BAANL){
            for (unsigned int i = 0; i < this->roads.size(); ++i) {
                if (tempn == this->roads[i]->getRoadName()) {
                    vehicle->setRoad(this->roads[i]);
                    this->roads[i]->addVehicle(vehicle);
                    this->addVehicle(vehicle);
                    break;
                }
            }
        }
        else if(elemName == POSITIE){
            tempi = atoi(elem->GetText());
            vehicle->setPosition(tempi);
        }
    }

    return true;
}

//==== Constructors and Destructor ====//
TrafficSimulation::TrafficSimulation(const string &filename) : filename(filename) {
    TiXmlDocument doc;

    // File readable detection with error message
    try{
        if(!doc.LoadFile(this->filename.c_str())) {
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
        if(elemName == BAANU){
            if(!this->parseRoad(elem)){
                cout << "Error: Could not make road" << endl;
            }
        }
        else if(elemName == VERKEERSLICHT){
            if(!this->parseTrafficLight(elem)){
                cout << "Error: Could not make traffic light" << endl;
            }
        }
        else if(elemName == VOERTUIG){
            if(!this->parseVehicle(elem)){
                cout << "Error: Could not make vehicle" << endl;
            }
        }
    }
}

TrafficSimulation::TrafficSimulation() {}

const vector<Road *> &TrafficSimulation::getRoads() const {
    return roads;
}

void TrafficSimulation::setRoads(const vector<Road *> &newRoads) {
    TrafficSimulation::roads = newRoads;
}

void TrafficSimulation::addTrafficLight(TrafficLight *&newLight) {
    this->lights.push_back(newLight);
}

void TrafficSimulation::addVehicle(Vehicle *&newVehicle) {
    this->vehicles.push_back(newVehicle);
}

bool TrafficSimulation::addRoad(Road *newRoad) {
    for (unsigned int i = 0; i < this->roads.size(); ++i) {
        if(this->roads[i] == newRoad){
            return false;
        }
    }
    this->roads.push_back(newRoad);
    return true;
}

void TrafficSimulation::print() {
    if (!this->roads.empty()){

        if(this->roads.size() == 1){
            cout <<"Consists of " << this->roads.size() << " road: " << endl;
        }
        else{
            cout <<"Consists of " << this->roads.size() << " roads: " << endl;
        }

        for(unsigned int i = 0; i < this->roads.size(); i++){
            cout << endl << "--------------------";

            cout << endl;

            this->roads[i]->print();

            cout << endl;

            if(this->roads[i]->getTrafficLightsAmount() == 1){
                cout << "Consist of " << this->roads[i]->getTrafficLightsAmount() << " traffic light." << endl;
            }
            else{
                cout << "Consist of " << this->roads[i]->getTrafficLightsAmount() << " traffic lights." << endl;
            }

            cout << endl;

            for (int j = 0; j < this->roads[i]->getTrafficLightsAmount(); ++j) {
                cout << "Traffic light " << j + 1 << ":" << endl;
                this->roads[i]->getTrafficLight(j)->print();
            }

            cout << endl;

            if(this->roads[i]->getVehicleAmount() == 1){
                cout << "Consist of " << this->roads[i]->getVehicleAmount() << " vehicle." << endl;
            }
            else{
                cout << "Consist of " << this->roads[i]->getVehicleAmount() << " vehicles." << endl;
            }

            cout << endl;

            for (int k = 0; k < this->roads[i]->getVehicleAmount(); ++k) {
                cout << "Vehicle " << k + 1 << ":" << endl;
                this->roads[i]->getVehicle(k)->print();
                cout << endl;
            }
        }
    }
    else{
        cout << "There are no roads." << endl;
    }
}

void TrafficSimulation::startSimulation() {
    /*int count = 0;
    while (this->vehicles.size() > 0){
        for (int i = 0; i < this->vehicles.size(); ++i){
            // Simulate vehicle

        }
        for (int j = 0; j < this->lights.size(); ++j) {
            // Simulate traffic light
        }
        count++;
    }*/
}

TrafficSimulation::~TrafficSimulation() {}
