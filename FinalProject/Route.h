/********************************************************************************************/
/* Route.h																				    */
/* This file contains information regarding the train routes in companies                	*/
/********************************************************************************************/

#ifndef ROUTE_H
#define ROUTE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Definitions.h"
#include "Time.h" 
#include "Inspector.h" 
#include "Train.h"
#include "Driver.h"
#include "List.h"
#include "TrainStation.h"

typedef enum {
    startingPoint,
    intermediateStation,
    finalStop,
    eNoOfStation
} stationType;


typedef struct {
    structType type;
    int routeId;
    Train* train;
    Driver* driver;
    Inspector* inspector;
    LIST* trainStationsList;
    int numOfStation;
    Time* departureTime;
} Route;

// Function to initialize a train route

// Function to print train route details
void printTrainRoute(const Route* route);

// Function to free memory allocated for a train route
void freeTrainRoute(Route* route);

#endif