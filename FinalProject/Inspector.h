/**************************************************************************/
/* Inspector.h                                                            */
/* This file contains information regarding the train inspectors          */
/**************************************************************************/

#ifndef __INSPECTOR__
#define __INSPECTOR__

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

#include "Definitions.h"
#include "Functions.h"

typedef struct
{
	structType type;
	char* InspectorName;
	int licenseNumber;
}Inspector;

int initInspector(Inspector* inspector);
void printInspector(const Inspector* inspector);
void freeInspector(Inspector* Inspector);

#endif
