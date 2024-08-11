/********************************************************************************************/
/* Definitions.h																				*/
/* This file contains general definitions used in several places in the code	*/
/********************************************************************************************/

// New types:

#ifndef DEFINATIONS_H
#define DEFINATIONS_H
#define MAX_STATIONSALPHAPLUS 5
#define MAX_STATIONSALPHA 3
#define MAX_STATIONSBETAPLUS 2
#define MAX_STATIONSBETA 1



#define MAX_STR_LEN 255

typedef unsigned char BYTE;
typedef void* Data;					// a type for data (easy to change)
typedef enum { False, True } boolean;	// a boolean type

// Linked lists node:
typedef struct Node {
	Data			key;
	struct Node* next;
}NODE;

// Type definitions
typedef enum {
	eCity, eDriver, eInspector, eRoute, eTime, eTrain, eTrainCompany, eTrainStation
} structType;



#endif