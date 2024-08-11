/**************************************************************************/
/* Train.h                                                                */
/* This file contains information regarding the trains                    */
/**************************************************************************/

#ifndef __TRAIN__
#define __TRAIN__

#define _CRT_SECURE_NO_WARNINGS

#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#include "Definitions.h"
#include "Time.h"

#define MIN_CARS 0
#define MAX_CARS 50

typedef enum {
	eFastPassenger, eLightPassenger, eMetro, eCargo, eNoTrainType
} eTrainType;

static const char* TrainTypeStr[eNoTrainType]
= { "Fast-Passenger", "Light-Passenger", "Metro", "Cargo"};

typedef struct
{
	structType type;
	int serialNumber;
	eTrainType trainType;
	int numOfRailroadCars;
	Time trainValidityLicenseDate;
}Train;

int		initTrain(Train* pTrain, Train* trainArr, int trainCount);// Maybe needs to be updated later!!!!!!!
int		setNumberOfCars(Train* pTrain);
int		updateValidityLicense(Train* pTrain);
void	printTrain(const Train* pTrain);
void	freeTrain(Train* pTrain);

#endif
