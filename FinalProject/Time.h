/********************************************************************************************/
/* Time.h																				    */
/* This file contains information regarding times and dates                             	*/
/********************************************************************************************/

#ifndef TIME_H
#define TIME_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Definitions.h"
#include "Functions.h"

#define SPECIAL_CHAR1 '/'
#define SPECIAL_CHAR2 ':'
#define MIN_YEAR 2024

typedef struct
{
    structType type;
    int year;
    int month;
    int day;
    int hour;
    int minute;
} Time;

// Initializes travel time
int initTravelTime(Time* pTime);

// Prints travel time
void printTravelTime(const Time* pTime);

// Frees memory allocated for travel time
void freeTravelTime();

boolean getCorrectDate(Time* pTime);
boolean	checkDate(char* time, Time* pTime);
boolean getCorrectTime(Time* pTime);
boolean	checkTime(char* time, Time* pTime);

#endif
