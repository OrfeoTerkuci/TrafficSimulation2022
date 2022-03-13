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
    unsigned int templ;

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
            templ = atoi(elem->GetText());
            if(templ == 0){
                delete newRoad;
                return false;
            }
            else{
                newRoad->setLength(templ);
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

bool TrafficSimulation::parseTrafficLight(TiXmlElement* &root, TrafficSimulation* TF){return false;}

bool TrafficSimulation::parseVehicle(TiXmlElement* &root, TrafficSimulation* TF){return false;}

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
                break;
            }
        }
        else if(elemName == VERKEERSLICHT){

        }
        else if(elemName == VOERTUIG){

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
    for (int i = 0; i < this->roads.size(); ++i) {
        if(this->roads[i] == newRoad){
            return false;
        }
    }

    this->roads.push_back(newRoad);
    return true;
}