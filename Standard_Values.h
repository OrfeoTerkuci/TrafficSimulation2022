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
enum vehicleType{ T_AUTO , T_BUS , T_FIRETRUCK , T_AMBULANCE , T_POLICE , T_NULL};
enum fileFunctionType{ closing , create , update};

// Strings
#define NAAM                    "naam"
#define BAANU                   "BAAN"
#define BAANL                   "baan"
#define LENGTE                  "lengte"
#define VERKEERSLICHT           "VERKEERSLICHT"
#define VOERTUIG                "VOERTUIG"
#define POSITIE                 "positie"
#define CYCLUS                  "cyclus"
#define VOERTUIGGENERATOR       "VOERTUIGGENERATOR"
#define FREQUENTIE              "frequentie"
#define BUSHALTE                "BUSHALTE"
#define WACHTTIJD               "wachttijd"
#define KRUISPUNT               "KRUISPUNT"
#define TYPE                    "type"
#define BAAN_POSITIE            "baan positie ="

// Vehicle type strings
#define AUTO                    "auto"
#define BUS                     "bus"
#define BRANDWEERWAGEN          "brandweerwagen"
#define ZIEKENWAGEN             "ziekenwagen"
#define POLITIECOMBI            "politiecombi"

// Vehiclegenerator test values
#define MAX_VEHICLES            20

// Crossroad "random" test valus
#define MODULO_RANDOM                  10

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

// file types
#define XMLL                    ".xml"
#define XMLU                    ".XML"
#define JSONL                   ".json"
#define JSONU                   ".JSON"
#define OUTPUT_DIRECTORY        "./OutputLog/"
#define TXTL                    ".txt"
#define HTMLL                   ".html"

#endif //TRAFFICSIMULATION2022_STANDARD_VALUES_H
