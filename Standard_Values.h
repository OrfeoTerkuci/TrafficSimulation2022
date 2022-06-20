#ifndef TRAFFICSIMULATION2022_STANDARD_VALUES_H
#define TRAFFICSIMULATION2022_STANDARD_VALUES_H

// General Values
#define SIMULATION_TIME                 0.0166
#define SLOWING_DISTANCE                50.0
#define STOPPING_DISTANCE               15.0
#define SLOWING_FACTOR                  0.4
// Vehicle type : AUTO
#define LENGTH                          4.0
#define MAX_SPEED                       16.6
#define MAX_ACCELERATION                1.44
#define MAX_BRAKE_FACTOR                4.61
#define MIN_FOLLOW_DISTANCE             4.0
#define DECELERATE                      SLOWING_FACTOR * MAX_SPEED
// Vehicle type: BUS
#define BUS_LENGTH                      12.0
#define BUS_MAX_SPEED                   11.4
#define BUS_MAX_ACCELERATION            1.22
#define BUS_MAX_BRAKE_FACTOR            4.29
#define BUS_MIN_FOLLOW_DISTANCE         12.0
#define BUS_DECELERATE                  SLOWING_FACTOR * BUS_MAX_SPEED
// Vehicle type: BRANDWEERWAGEN
#define FIRETRUCK_LENGTH                10.0
#define FIRETRUCK_MAX_SPEED             14.6
#define FIRETRUCK_MAX_ACCELERATION      1.33
#define FIRETRUCK_MAX_BRAKE_FACTOR      4.56
#define FIRETRUCK_MIN_FOLLOW_DISTANCE   10.0
#define FIRETRUCK_DECELERATE            SLOWING_FACTOR * FIRETRUCK_MAX_SPEED
// Vehicle type: ZIEKENWAGEN
#define AMBULANCE_LENGTH                8.0
#define AMBULANCE_MAX_SPEED             15.5
#define AMBULANCE_MAX_ACCELERATION      1.44
#define AMBULANCE_MAX_BRAKE_FACTOR      4.47
#define AMBULANCE_MIN_FOLLOW_DISTANCE   8.0
#define AMBULANCE_DECELERATE            SLOWING_FACTOR * AMBULANCE_MAX_SPEED
// Vehicle type: POLITIECOMBI
#define POLICE_LENGTH                   6.0
#define POLICE_MAX_SPEED                17.2
#define POLICE_MAX_ACCELERATION         1.55
#define POLICE_MAX_BRAKE_FACTOR         4.92
#define POLICE_MIN_FOLLOW_DISTANCE      6.0
#define POLICE_DECELERATE               SLOWING_FACTOR * POLICE_MAX_SPEED

// Enumerations

enum vehicleStatus{ accelerate , decelerate , stopping , idle };
enum busStatus{ slowingBus , stoppingBus , leavingBus , farBus , noBus };
enum fileFunctionType{ closing , create , update};
enum vehicleType{ T_AUTO , T_BUS , T_FIRETRUCK , T_AMBULANCE , T_POLICE , T_NULL};

// Strings
#define TYPE                    "type"
#define NAAM                    "naam"
#define BAANU                   "BAAN"
#define BAANL                   "baan"
#define LENGTE                  "lengte"
#define CYCLUS                  "cyclus"
#define POSITIE                 "positie"
#define VOERTUIG                "VOERTUIG"
#define BUSHALTE                "BUSHALTE"
#define WACHTTIJD               "wachttijd"
#define KRUISPUNT               "KRUISPUNT"
#define FREQUENTIE              "frequentie"
#define VERKEERSLICHT           "VERKEERSLICHT"
#define BAAN_POSITIE            "baan positie ="
#define VOERTUIGGENERATOR       "VOERTUIGGENERATOR"

// Vehicle type strings
#define AUTO                    "auto"
#define BUS                     "bus"
#define ZIEKENWAGEN             "ziekenwagen"
#define POLITIECOMBI            "politiecombi"
#define BRANDWEERWAGEN          "brandweerwagen"

// Vehiclegenerator test values
#define MAX_VEHICLES            5

// Crossroad "random" test valus
#define MODULO_RANDOM           13

// xml file names
#define SIM0                    "Simulation0.xml"
#define SIM1                    "Simulation1.xml"
#define SIM2                    "Simulation2.xml"
#define SIM3                    "Simulation3.xml"
#define SIM4                    "Simulation4.xml"
#define SIM5                    "Simulation5.xml"
#define SIM6                    "Simulation6.xml"
#define SIM7                    "Simulation7.xml"
#define SIM8                    "Simulation8.xml"
#define SIM9                    "Simulation9.xml"
#define SIM10                   "Simulation10.xml"
#define SIM11                   "Simulation11.xml"
#define SIM12                   "Simulation12.xml"
#define SIM13                   "Simulation13.xml"
#define SIM14                   "Simulation14.xml"
#define SIM15                   "Simulation15.xml"
#define SIM16                   "Simulation16.xml"
#define SIM17                   "Simulation17.xml"
#define SIM18                   "Simulation18.xml"

// file types
#define XMLL                    ".xml"
#define XMLU                    ".XML"
#define TXTL                    ".txt"
#define INIL                    ".ini"
#define HTMLL                   ".html"
#define JSONL                   ".json"
#define JSONU                   ".JSON"
#define TESTLOG                 "./TestLog/"
#define OUTPUT_DIRECTORY        "./OutputLog/"
#define INI_DIRECTORY           "../../Engine/"

// log files
#define BUSLOG                  "BusLog/busLog.txt"
#define ROADLOG                 "RoadLog/roadLog.txt"
#define VEHICLELOG              "VehicleLog/vehicleLog.txt"
#define CROSSROADLOG            "CrossRoadLog/crossroadLog.txt"
#define TRAFFICLIGHTLOG         "TrafficLightLog/trafficLightLog.txt"
#define VEHICLEGENERATORLOG     "VehicleGeneratorLog/vehicleGeneratorLog.txt"

#endif //TRAFFICSIMULATION2022_STANDARD_VALUES_H
