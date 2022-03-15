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

TrafficSimulation::~TrafficSimulation() {}

const vector<Road *> &TrafficSimulation::getRoads() const {
    return roads;
}

void TrafficSimulation::setRoads(const vector<Road *> &newRoads) {
    TrafficSimulation::roads = newRoads;
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

}
