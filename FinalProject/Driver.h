/**************************************************************************/
/* Driver.h                                                               */
/* This file contains information regarding the train drivers             */
/**************************************************************************/

#ifndef __DRIVER__
#define __DRIVER__

#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "Train.h"
#include "Definitions.h"
#include "Functions.h"


typedef struct
{
	structType type;
	char* DriverName;
	int licenseNumber;
	eTrainType licenseType;
}Driver;

int	initDriver(Driver* driver);
int	changeLicense(Driver* driver);
void printDriver(const Driver* driver);
void freeDriver(Driver* driver);
int compareLicense(const void* a, const void* b);
int compareDriverBylicenseNumber(const void* key, const void* element);
void sortDriversByLicenseType(Driver* driversArray, int numOfDrivers);
Driver* searchDriverBylicenseNumber(int licenseNumber, Driver* driversArray, int numOfDrivers);
int compareDriverByLicenseNumber(const void* a, const void* b);
void sortDriversByLicenseNumber(Driver* driversArray, int numOfDrivers);

#endif