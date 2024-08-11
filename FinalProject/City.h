/********************************************************************************************/
/* City.h																				    */
/* This file contains information regarding the cities linked to the companies            	*/
/********************************************************************************************/
#pragma once


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "TrainStation.h"
#include "Definitions.h"
#include "Functions.h"

#define CITYCODE 3
#define MAX_ALPHAPLUS 1000000
#define MIN_ALPHAPLUS 750000
#define MAX_ALPHA 750000
#define MIN_ALPHA 500000
#define MAX_BETAPLUS 500000
#define MIN_BETAPLUS 200000
#define MAX_BETA 200000
#define MIN_BETA 50000

typedef enum {
    AlphaPlus,
    Alpha,
    BetaPlus,
    Beta,
    eNoOfCityRank
} cityRank;

static const char* CityRankType[eNoOfCityRank]
= { "AlphaPlus", "Alpha", "BetaPlus", "Beta" };

typedef struct {
    char* name;
    structType type;
    char cityCode[CITYCODE + 1];
    cityRank rank;
    TrainStation** trainStations;
    int numOfStations;
} City;

// Function to initialize a city
int initCity(City* city);

// Function to change the rank of a city
int changeCityRank(City* city);

void initTrainStations(City* city, TrainStation* trainStations, int numOfStations);

// Function to add a train station to a city
int addTrainStation(City* city);

// Function to remove a train station from a city
int removeTrainStation(City* city);

int compareCityCode(const void* a, const void* b);

City* searchCityByCode(City** cityArray, const char* cityCode, int numOfCities);


// Function to print city details
void printCity(const City* city);
void printTrainStationInCity(const City* city);
void printCityDetail(const City* city);
// Function to free memory allocated for a city
void freeCity(City* city);

void getCityCode(char* cityCode);

TrainStation* searchTrainIntrainstation(City* pCity, int serial);
