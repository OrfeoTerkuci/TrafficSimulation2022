// custom libs
#include "ParserXML.h"
#include "TrafficSimulation.h"

// c++ libs
#include <stdexcept>
#include <typeinfo>
#include <sstream>
#include <filesystem>

using namespace std;

//==== Constructors and Destructor ====//
TrafficSimulation::TrafficSimulation(const string &filename) : filename(filename), time(0), stopTime(0) {
    REQUIRE(*typeid(filename).name() == 'N' , "constructor was called with invalid filename");
    _initCheck = this;
    if (filename.find(XMLL) != string::npos or filename.find(XMLU) != string::npos){
        parseXML();
    }
    else if (filename.find(JSONU) != string::npos or filename.find(JSONL) != string::npos){
        parseJSON();
    }
    else {
        cout << "No compatible parser for this type of file" << endl;
    }
    ENSURE(TrafficSimulation::filename == filename , "filename was not properly initialized");
    ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
}

TrafficSimulation::TrafficSimulation(): time(0), stopTime(0) {
    _initCheck = this;
    ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
}

bool TrafficSimulation::properlyInitialized() const{
    return  _initCheck == this;
}

const vector<VehicleGenerator *> &TrafficSimulation::getVehicleGenerators() {
    REQUIRE(this->properlyInitialized(), "TrafficSimulation was not initialized when calling getVehicleGenerators");
    return vehicleGenerators;
}

const vector<Road *> & TrafficSimulation::getRoads() {
    REQUIRE(this->properlyInitialized(), "TrafficSimulation was not initialized when calling getRoads");
    return roads;
}

void TrafficSimulation::setRoads(const vector<Road *> &newRoads) {
    REQUIRE(this->properlyInitialized(), "TrafficSimulation was not initialized when calling setRoads");
    REQUIRE(*typeid(newRoads).name() == 'S' , "setRoads was called with invalid parameter");
    TrafficSimulation::roads = newRoads;
    ENSURE(TrafficSimulation::roads == newRoads , "setRoads failed");
}

const vector<TrafficLight *> &TrafficSimulation::getLights() {
    REQUIRE(this->properlyInitialized(), "TrafficSimulation wasn't properly initialized when calling getLights");
    return lights;
}

const vector<Vehicle *> &TrafficSimulation::getVehicles(){
    REQUIRE(this->properlyInitialized(), "TrafficSimulation wasn't properly initialized when calling getVehicles");
    return vehicles;
}

void TrafficSimulation::addTrafficLight(TrafficLight *&newLight) {
    REQUIRE(this->properlyInitialized(), "TrafficSimulation was not initialized when calling addTrafficLight");
    REQUIRE(*typeid(newLight).name() == 'P' , "addTrafficLight was called with invalid parameter");
    REQUIRE(newLight->properlyInitialized() , "addTrafficLight was called with uninitialized parameter");
    unsigned int* oldSize = new unsigned int;
    *oldSize = lights.size();
    this->lights.push_back(newLight);
    ENSURE(*oldSize == lights.size() - 1 , "addTrafficLight failed");
    delete oldSize;
}

void TrafficSimulation::addVehicle(Vehicle *&newVehicle) {
    REQUIRE(this->properlyInitialized(), "TrafficSimulation was not initialized when calling addVehicle");
    REQUIRE(*typeid(newVehicle).name() == 'P' , "addVehicle was called with invalid parameter");
    REQUIRE(newVehicle->properlyInitialized() , "addVehicle was called with uninitialized parameter");
    unsigned int* oldSize = new unsigned int;
    *oldSize = vehicles.size();
    this->vehicles.push_back(newVehicle);
    ENSURE(*oldSize == vehicles.size() - 1 , "addVehicle failed");
    delete oldSize;
}

bool TrafficSimulation::addRoad(Road *newRoad) {
    REQUIRE(this->properlyInitialized(), "TrafficSimulation was not initialized when calling addRoad");
    REQUIRE(*typeid(newRoad).name() == 'P' , "addRoad was called with invalid parameter");
    REQUIRE(newRoad->properlyInitialized() , "addRoad was called with uninitialized parameter");
    unsigned int* oldSize = new unsigned int;
    *oldSize = roads.size();
    for (unsigned int i = 0; i < this->roads.size(); ++i) {
        if(this->roads[i] == newRoad){
            ENSURE(*oldSize == roads.size() , "addRoad: vector modified when it shouldn't");
            return false;
        }
    }
    this->roads.push_back(newRoad);
    ENSURE(*oldSize == roads.size() - 1 , "addRoad failed");
    delete oldSize;
    return true;
}

bool TrafficSimulation::addVehicleGenerator(VehicleGenerator *newVehicleGenerator) {
    REQUIRE(this->properlyInitialized(), "TrafficSimulation was not initialized when calling addVehicleGenerator");
    REQUIRE (*typeid(newVehicleGenerator).name() == 'P' , "addVehicleGenerator was called with invalid parameter");
    REQUIRE (newVehicleGenerator->properlyInitialized() , "addVehicleGenerator was called with uninitialized parameter");
    unsigned int* oldSize = new unsigned int;
    *oldSize = vehicleGenerators.size();
    // Check if the vehicle generator is already present
    for (unsigned int i = 0; i < this->vehicleGenerators.size(); ++i) {
        if (this->vehicleGenerators[i]->getRoad() == newVehicleGenerator->getRoad()){
            ENSURE(*oldSize == vehicleGenerators.size() , "addVehicleGenerator : vector modified when it shouldn't");
            return false;
        }
    }
    this->vehicleGenerators.push_back(newVehicleGenerator);
    ENSURE(*oldSize == vehicleGenerators.size() - 1 , "addVehicleGenerator failed");
    return true;
}

void TrafficSimulation::printAll() {
    REQUIRE(this->properlyInitialized(), "TrafficSimulation was not initialized when calling printAll");
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

            if(this->vehicleGenerators.size() == 1){
                cout << "Consists of " << vehicleGenerators.size() << " Vehicle Generator: " << endl;
            }
            else if(this->vehicleGenerators.size() > 1){
                cout << "Consists of " << vehicleGenerators.size() << " Vehicle Generators: " << endl;
            }

            cout << endl;

            for (long unsigned int l = 0; l < this->vehicleGenerators.size(); ++l) {
                cout << "Vehicle Generator " << l << " : " << endl;
                cout << '\t' << "-> Road: " << this->vehicleGenerators[l]->getRoad()->getRoadName() << endl;
                cout << '\t' << "-> Frequency: " << this->vehicleGenerators[l]->getFrequentie() << endl;
                cout << endl;
            }
        }
    }
    else{
        cout << "There are no roads." << endl;
    }
}

void TrafficSimulation::print( int &count) {
    REQUIRE(this->properlyInitialized(), "TrafficSimulation was not initialized when calling print");
    if (!this->vehicles.empty() || !this->vehicleGenerators.empty()){
        cout << "Time: " << count << endl;
        for (long unsigned int i = 0; i < this->vehicles.size(); ++i) {
            cout << "Vehicle " << i+1 << ": " << endl;
            this->vehicles.at(i)->print();
            cout << endl;
        }
    }

}

void TrafficSimulation::startSimulation(bool printE, bool outputE, bool countE, bool timeE) {
    REQUIRE(this->properlyInitialized(), "TrafficSimulation was not initialized when calling startSimulation");
    int count = time;
    double vehiclePosition;
    int roadLength;
    Vehicle* currentVehicle;
    Road* currentRoad;

    if (printE){
        cout << "- Starting simulation" << endl;
    }

    if (outputE){
        outputFile(create);
    }

    while (!this->vehicles.empty() || !this->vehicleGenerators.empty()){
        for (unsigned int j = 0; j < this->lights.size(); ++j) {
            // Simulate traffic light
            currentRoad = lights.at(j)->getRoad();
            if(currentRoad->getVehicleAmount() > 0){
                this->lights.at(j)->simulate(count);
            }
        }
        for (unsigned int k = 0; k < this->busStops.size(); ++k) {
            this->busStops.at(k)->simulateBusStop();
        }
        for (unsigned int l = 0; l < this->vehicleGenerators.size(); l++){
            VehicleGenerator* currentGenerator;
            currentGenerator = this->vehicleGenerators.at(l);
            // Check if we can generate
            if (currentGenerator->simulate())
            {
                // Generate new vehicle
                Vehicle* newVehicle;
                newVehicle = new Vehicle();
                // Add road to vehicle
                newVehicle->setRoad(currentGenerator->getRoad());
                // Add vehicle to road
                newVehicle->setRoad(currentGenerator->getRoad());
                currentGenerator->getRoad()->addVehicle(newVehicle);
                // Add vehicle to our simulation
                this->addVehicle(newVehicle);
            }
        }
        for (unsigned int i = 0; i < this->vehicles.size(); ++i){
            // Get current vehicle
            currentVehicle = this->vehicles.at(i);
            // Get current road
            currentRoad = currentVehicle->getRoad();
            // Simulate vehicle
            currentVehicle->simulate();
            // Get vehicle position
            vehiclePosition = currentVehicle->getVehiclePosition();
            roadLength = currentRoad->getLength();
            // Check if vehicle had gone off the road
            if (vehiclePosition > roadLength){
                // Remove the vehicle from the simulation
                currentRoad->removeVehicle(currentVehicle);
                this->vehicles.erase(vehicles.begin() + i);
            }
        }
        if(printE){
            print(count);
        }
        if(outputE){
            outputFile(update, count);
        }
        if (countE and this->vehicles.size() == MAX_VEHICLES * this->getVehicleGenerators().size()){
            break;
        }
        if (timeE and count == stopTime){
            break;
        }
        count ++;
        time = count;
        /*if (count == 12000){
            break;
        }*/
    }
    if (printE){
        cout << "- There are no vehicles on the road network." << endl;
        cout << "- Ending simulation" << endl;
    }
    if (outputE){
        outputFile(closing);
    }
    if (!countE and !timeE){
        ENSURE(vehicles.empty() , "Simulation ended when it shouldn't");
    } else if (countE){
        ENSURE(vehicles.size() == MAX_VEHICLES * this->getVehicleGenerators().size(), "Amount of vehicles on road is not the same as what expected");
    }
}

const vector<CrossRoad *> &TrafficSimulation::getCrossRoads(){
    REQUIRE(this->properlyInitialized(), "TrafficSimulation wasn't properly initialized when calling getCrossRoads");
    return crossRoads;
}

const string &TrafficSimulation::getFilename(){
    REQUIRE(this->properlyInitialized(), "TrafficSimulation wasn't properly initialized when calling getFilename");
    return filename;
}

void TrafficSimulation::parseXML() {
    REQUIRE(this->properlyInitialized(), "Trafficsimulation is properly initialized when calling parseXML");
    parseTrafficSimulationX(*this);
}

void TrafficSimulation::parseJSON() {
    REQUIRE(this->properlyInitialized(), "Trafficsimulation is properly initialized when calling parseJSON");
    // parse JSON file
}

void TrafficSimulation::addCrossRoad(CrossRoad* crossRoad) {
    REQUIRE(this->properlyInitialized(), "TrafficSimulation wasn't properly initialized when calling addCrossRoad");
    REQUIRE(crossRoad->properlyInitialized(), "crossRoad wasn't properly initialized when calling addCrossRoad");
    crossRoads.push_back(crossRoad);
}
void TrafficSimulation::addBusStop(BusStop* busStop) {
    REQUIRE(this->properlyInitialized(), "TrafficSimulation wasn't properly initialized when calling addBusStop");
    REQUIRE(busStop->properlyInitialized(), "busstop wasn't properly initialized when calling addBusStop");
    busStops.push_back(busStop);
}

void addSpaces(fstream &file, int spaceAmount){
    for (int i = 0; i < spaceAmount; ++i) {
        file << " ";
    }
}

void TrafficSimulation::outputFile(fileFunctionType type, int timestamp) {
    REQUIRE(this->properlyInitialized(), "TrafficSimulation was not initialized when calling outpputFile");
    REQUIRE(type == create || type == update || type == closing, "type not matching with any of the file functions");

    // find file name
    string newFileName = OUTPUT_DIRECTORY + filename.substr(0, filename.find('.'));
    string newFileNameHTML = newFileName + HTMLL;
    newFileName += TXTL;

    if (type == create){
        // create file
        FILE* codefile;

        // TXT
        bool doesntExists = true;
        fstream outputNewFile;
        int i = 0;

        while (doesntExists){
            i++;
            codefile = fopen(newFileName.c_str(), "r");
            if (codefile){
                newFileName = OUTPUT_DIRECTORY + filename.substr(0, filename.size() - 4);
                stringstream intStr;
                intStr << i;
                newFileName += '(';
                newFileName += intStr.str();
                newFileName += ')';
                newFileName += TXTL;
            }
            else {
                outputNewFile.open(newFileName.c_str(), ios::app | ios::ate);
                outputFileName = newFileName;
                doesntExists = false;
            }
        }

        // HTML
        doesntExists = true;
        fstream outputNewFileHTML;
        i = 0;
        while (doesntExists){
            i++;
            codefile = fopen(newFileNameHTML.c_str(), "r");
            if (codefile){
                newFileNameHTML = OUTPUT_DIRECTORY + filename.substr(0, filename.size() - 4);
                stringstream intStr;
                intStr << i;
                newFileNameHTML += '(';
                newFileNameHTML += intStr.str();
                newFileNameHTML += ')';
                newFileNameHTML += HTMLL;
            }
            else {
                outputNewFileHTML.open(newFileNameHTML.c_str(), ios::app | ios::ate);
                outputFileNameHTML = newFileNameHTML;
                doesntExists = false;
            }
        }

        // write in file
        // TXT
        outputNewFile << "TrafficSimulation: " << filename << '\n' << '\n';
        // HTML
        outputNewFileHTML << "<!DOCTYPE html>\n"
                             "<html>\n"
                             "<head>\n"
                             "<title>";
        outputNewFileHTML << "TrafficSimulation: " << filename << "</title>\n" << '\n';
        outputNewFileHTML << "</head>\n"
                             "<body>\n";

        outputNewFileHTML << "<h1>";
        outputNewFileHTML << "TrafficSimulation: " << filename << "</h1>\n" << '\n';

        // close file
        outputNewFile.close();
        outputNewFileHTML.close();
        ENSURE(!outputNewFile.is_open(), "File is still open");
        ENSURE(!outputNewFileHTML.is_open(), "File is still open");

        codefile = fopen(outputFileName.c_str(), "r");
        ENSURE(codefile, "TXT outputfile doesn't exist");
        codefile = fopen(outputFileNameHTML.c_str(), "r");
        ENSURE(codefile, "HTML outputfile doesn't exist");
    }
    else if (type == update) {
        // open file
        fstream outputFile;
        fstream outputFileHTML;
        outputFile.open(outputFileName.c_str(),ios::app | ios::ate | ios::binary);
        outputFileHTML.open(outputFileNameHTML.c_str(), ios::app | ios::ate | ios::binary);

        FILE* codefile;

        codefile = fopen(outputFileName.c_str(), "r");
        REQUIRE(codefile, "TXT outputfile doesn't exist");
        codefile = fopen(outputFileNameHTML.c_str(), "r");
        REQUIRE(codefile, "HTML outputfile doesn't exist");

        if (outputFile.fail()) {
            cout << "TXT File doesn't exist" << endl;
        }
        if (outputFileHTML.fail()) {
            cout << "HTML File doesn't exist" << endl;
        }
        // write file
        if(roads.empty()){
            outputFile << "No roads in this simulation\n";
            outputFileHTML << "<p>No roads in this simulation</p>";
        }
        else {
            outputFile << "Time: ";
            outputFile << timestamp;
            outputFile << '\n';

            outputFileHTML << "<h2>";
            outputFileHTML << "Time: ";
            outputFileHTML << timestamp;
            outputFileHTML << "</h2>\n";
            for (unsigned int j = 0; j < roads.size(); ++j) {
                int nameLenghth = 26;
                int roadLenghth = roads[j]->getLength();
                nameLenghth -= roads[j]->getRoadName().size();
                string roadnm = roads[j]->getRoadName();
                outputFile << roads[j]->getRoadName();
                addSpaces(outputFile, nameLenghth);
                outputFile << "| ";

                outputFileHTML << "<h3>";
                outputFileHTML << roads[j]->getRoadName();
                addSpaces(outputFileHTML, nameLenghth);
                outputFileHTML << "| ";

                for (int k = 0; k < roadLenghth; ++k) {
                    int count = 0;
                    for (int l = 0; l < roads[j]->getVehicleAmount(); ++l) {
                        if (k >= (int) roads[j]->getVehicle(l)->getVehiclePosition() and
                            k < (int) roads[j]->getVehicle(l)->getVehiclePosition() + 8 and
                            roads[j]->getVehicle(l)->getType() == T_POLICE) {
                            outputFile << "P";
                            outputFileHTML << "<span style=\"color: #0000ff\">P</span>";
                        } else if (k >= (int) roads[j]->getVehicle(l)->getVehiclePosition() and
                                   k < (int) roads[j]->getVehicle(l)->getVehiclePosition() + 8 and
                                   roads[j]->getVehicle(l)->getType() == T_AMBULANCE) {
                            outputFile << "Z";
                            outputFileHTML << "<span style = \"color: #00ff00\">Z</span>";
                        } else if (k >= (int) roads[j]->getVehicle(l)->getVehiclePosition() and
                                   k < (int) roads[j]->getVehicle(l)->getVehiclePosition() + 4 and
                                   roads[j]->getVehicle(l)->getType() == T_AUTO) {
                            outputFile << "A";
                            outputFileHTML << "<span style = \" color: #fd7924\">A</span>";
                        } else if (k >= (int) roads[j]->getVehicle(l)->getVehiclePosition() and
                                   k < (int) roads[j]->getVehicle(l)->getVehiclePosition() + 12 and
                                   roads[j]->getVehicle(l)->getType() == T_BUS) {
                            outputFile << "B";
                            outputFileHTML << "<span style = \" color: #ffff00\">B</span>";
                        } else if (k >= (int) roads[j]->getVehicle(l)->getVehiclePosition() and
                                   k < (int) roads[j]->getVehicle(l)->getVehiclePosition() + 10 and
                                   roads[j]->getVehicle(l)->getType() == T_FIRETRUCK) {
                            outputFile << "F";
                            outputFileHTML << "<span style = \"color: #ff0000\">F</span>";
                        } else {
                            count++;
                        }
                    }
                    if (count == roads[j]->getVehicleAmount()) {
                        outputFile << "=";
                        outputFileHTML << "=";
                    }
                }
                outputFileHTML << "</h3>\n";
                outputFile << '\n';

                if (roads[j]->getTrafficLightsAmount() != 0) {
                    outputFile << '\t';
                    outputFile << "> verkeerslichten";
                    addSpaces(outputFile, 5);
                    outputFile << "| ";

                    outputFileHTML << "<h4>";
                    outputFileHTML << '\t';
                    outputFileHTML << "> verkeerslichten";
                    outputFileHTML << "| ";

                    for (int i = 0; i < roadLenghth; ++i) {
                        int lightsAmount = 0;
                        for (int k = 0; k < roads[j]->getTrafficLightsAmount(); ++k) {
                            if (roads[j]->getTrafficLights()[k]->getPosition() == (unsigned) i) {
                                if (roads[j]->getTrafficLight(k)->getCurrentColor() == green) {
                                    outputFile << "G";
                                    outputFileHTML << "<span style = \" color: #00ff00\">G</span>";
                                } else {
                                    outputFile << "R";
                                    outputFileHTML << "<span style = \" color: #ff0000\">R</span>";
                                }
                            } else if (roads[j]->getTrafficLight(k)->getPosition() - 15 == (unsigned) i) {
                                outputFile << '|';
                                outputFileHTML << '|';
                            } else {
                                lightsAmount++;
                            }
                        }
                        if (lightsAmount == roads[j]->getTrafficLightsAmount()) {
                            outputFile << ' ';
                            outputFileHTML << "<span style = \" color: #ffffff\">=</span>\n";
                        }
                    }
                    outputFileHTML << "</h4>\n";
                    outputFile << '\n';
                }

                if (!roads[j]->getBusStops().empty()) {
                    outputFile << '\t';
                    outputFile << "> bushaltes";
                    addSpaces(outputFile, 11);
                    outputFile << "| ";

                    outputFileHTML << "<h4>";
                    outputFileHTML << '\t';
                    outputFileHTML << "> bushaltes";
                    outputFileHTML << "| ";
                    for (int i = 0; i < roadLenghth; ++i) {
                        bool bushalteExist = false;
                        for (unsigned int k = 0; k < roads[j]->getBusStops().size(); ++k) {
                            if (roads[j]->getBusStops()[k]->getPosition() == i) {
                                outputFile << "B";
                                outputFileHTML
                                        << "<span style = \"color: #FFA500 ; background-color: #ffff00\">B</span>";
                                bushalteExist = true;
                            } else if (roads[j]->getBusStops()[k]->getPosition() - 15 == i) {
                                outputFile << "|";
                                outputFileHTML << "|";
                                bushalteExist = true;
                            }
                        }
                        if (!bushalteExist) {
                            outputFile << " ";
                            outputFileHTML << "<span style = \" color: #ffffff\">=</span>\n";
                        }
                    }
                    outputFileHTML << "</h4>\n";
                    outputFile << '\n';
                }

                if (!roads[j]->getCrossRaods().empty()) {
                    outputFile << '\t';
                    outputFile << "> kruispunten";
                    addSpaces(outputFile, 9);
                    outputFile << "| ";

                    outputFileHTML << "<h4>";
                    outputFileHTML << '\t';
                    outputFileHTML << "> kruispunten";
                    outputFileHTML << "| ";

                    for (int i = 0; i < roadLenghth; ++i) {
                        bool crossRoadExist = false;
                        for (unsigned int k = 0; k < roads[j]->getCrossRaods().size(); ++k) {
                            map<Road *, int>::iterator it = roads[j]->getCrossRaods().at(k)->getRoads().begin();
                            while (it != roads[j]->getCrossRaods().at(k)->getRoads().end()) {
                                if (it->first == roads[j] and i == it->second) {
                                    outputFile << "K";
                                    outputFileHTML << "K";
                                    crossRoadExist = true;
                                    break;
                                }
                                it++;
                            }
                        }
                        if (!crossRoadExist) {
                            outputFile << " ";
                            outputFileHTML << "<span style = \" color: #ffffff\">=</span>\n";
                        }
                    }
                    outputFileHTML << "</h4>\n";
                    outputFile << "\n";
                }
            }
        }

        // close file
        outputFile.close();
        ENSURE(!outputFile.is_open(), "TXT-file is closed");
        outputFileHTML.close();
        ENSURE(!outputFileHTML.is_open(), "HTML-file is closed");
    }
    else if (type == closing) {
        // open file
        fstream outputFile;
        outputFile.open(newFileNameHTML.c_str(), ios::app | ios::ate | ios::binary);

        FILE* codefile;
        codefile = fopen(outputFileNameHTML.c_str(), "r");
        REQUIRE(codefile, "HTML outputfile doesn't exist");

        // write file
        outputFile << "</body>\n"
                      "</html>";

        // close file
        outputFile.close();
        ENSURE(!outputFile.is_open(), "HTML-file is closed");
    }
}

void TrafficSimulation::outputStats() {
    REQUIRE(this->properlyInitialized(), "TrafficSimulation was not initialized when calling outputsStats");
    fstream file("Stats.txt");
    file.open("Stats/Stats.txt", fstream::out | fstream::in | ios::trunc);

    file << "Amount of vehicles: ";
    file << vehicles.size();
    file << '\n';

    file << "Amount of roads: ";
    file << roads.size();
    file << '\n';

    file << "Amount of bus stops: ";
    file << busStops.size();
    file << '\n';

    file << "Amount of crossroads: ";
    file << crossRoads.size();
    file << '\n';

    file << "Amount of VehicleGenerators: ";
    file << vehicleGenerators.size();
    file << '\n';

    file << "File is properly initialized: ";
    file << boolalpha << (_initCheck == this) << '\n';

    file.close();
    ENSURE(!file.is_open(), "file is still open when ending outputStats");
}

void TrafficSimulation::setStopTime(int newStopTime) {
    REQUIRE(this->properlyInitialized(), "TrafficSimulation was not initialized when calling setStopTime");
    TrafficSimulation::stopTime = newStopTime;
    ENSURE(newStopTime == stopTime, "stopTime was not assigned to newStopTime, when calling setStopTime");
}

TrafficSimulation::~TrafficSimulation() {
    REQUIRE(this->properlyInitialized(), "TrafficSimulation was not initialized when calling destructor");

    // Deleting every object, from memory
    for (unsigned int i = 0; i < roads.size(); ++i) {
        delete roads[i];
    }
    for (unsigned int i = 0; i < lights.size(); ++i) {
        delete lights[i];
    }
    for (unsigned int i = 0; i < busStops.size(); ++i) {
        delete busStops[i];
    }
    for (unsigned int i = 0; i < crossRoads.size(); ++i) {
        delete crossRoads[i];
    }
    for (unsigned int i = 0; i < vehicles.size(); ++i) {
        delete vehicles[i];
    }
    for (unsigned int i = 0; i < vehicleGenerators.size(); ++i) {
        delete vehicleGenerators[i];
    }

    // clearing lists
    roads.clear();
    lights.clear();
    busStops.clear();
    crossRoads.clear();
    vehicles.clear();
    vehicleGenerators.clear();

    // ensuring every list is empty
    ENSURE(roads.empty(), "Roads are not properly destructed");
    ENSURE(lights.empty(), "Lights are not properly destructed");
    ENSURE(busStops.empty(), "Bus stops are not properly destructed");
    ENSURE(crossRoads.empty(), "Crossroads are not properly destructed");
    ENSURE(vehicles.empty(), "Vehicles are not properly destructed");
    ENSURE(vehicleGenerators.empty(), "Vehicle generators are not properly destructed");
}

