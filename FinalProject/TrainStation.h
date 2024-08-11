/**************************************************************************/
/* TrainStation.h                                                         */
/* This file contains information regarding the train stations			  */
/**************************************************************************/

#ifndef __TRAINSTATION__
#define __TRAINSTATION__

#include <stdio.h>
#include <time.h>

#include "Definitions.h"
#include "Functions.h"
#include "Train.h"

#define MIN_PLATFORMS 0
#define MAX_PLATFORMS 20


typedef enum {
	eFastPassengerStation, eLightPassengerStation, eMetroStation, eCargoStation, eNoTrainTypeStation
} eTrainStationType;

static const char* TrainTypeStation[eNoTrainTypeStation]
= { "Fast-Passenger Station", "Light-Passenger Station", "Metro Station", "Cargo Station" };


typedef struct
{
	structType type;
	char* stationName;
	int stationSerialNumber;
	eTrainStationType trainStationType;
	int numOfPlatforms;
	int numOfActiveTrains; // recentrly added
	char* locatedInCity;
	int expectedNumOfPassengers;
	Train** platforms;

}TrainStation;

int		updateNumOfPlatforms(TrainStation* pTrainStation);
int		updatePlatformsArraySize(TrainStation* pTrainStation);
void printTrainStation(const TrainStation* pTrainStation);
void printTrainStationWithTrains(const TrainStation* pTrainStation);
int compareTrainSerial(const void* a, const void* b);
void sortCityTrainStation(TrainStation* station);
int searchTrainInCity(TrainStation** trainStations, const int trainSerial, int numTrainStation);
void printTrainStationInList(const TrainStation* pTrainStation);
int searchTrainInTrainStation(const TrainStation* pTrainStation, const int serialNum);
void	freeTrainStation(TrainStation* pTrainStation);
#endif
