#include "TrafficSimulation.h"
#include "Road.h"
#include "TrafficLight.h"
#include "Vehicle.h"
#include "tinyxml/tinyxml.h"
#include <stdexcept>

TrafficSimulation::TrafficSimulation(const string &filename) : filename(filename) {
    TiXmlDocument doc;

    // File readable detection
    try{
        if(!doc.LoadFile(this->filename.c_str())) {
            std::cerr << doc.ErrorDesc() << std::endl;
            throw 1;
        }
    }

    catch(int error){
        if(error == 1){
            std::cout << "File not readable" << std::endl;
        }
    }

    // Check if file has elements to parse
    TiXmlElement* root = doc.FirstChildElement();

    if(root == NULL) {
        std::cerr << "Failed to load file: No root element." << std::endl;
        doc.Clear();
    }


}

TrafficSimulation::TrafficSimulation() {}

TrafficSimulation::~TrafficSimulation() {}