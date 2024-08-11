#include "Definitions.h"
#include "Functions.h"
#include "Train.h"
#include "City.h"
#include "Driver.h"
#include "Inspector.h"
#include "TrainStation.h"
#include "TrainCompany.h"
#include "Time.h"
#include "Route.h"

// Functions:
char* myGets(char* buffer, int size)
{
	char* ok;
	if (buffer != NULL && size > 0)
	{
		do { //skip only '\n' strings
			ok = fgets(buffer, size, stdin);
		} while (ok && ((strlen(buffer) <= 1) && (isspace(buffer[0]))));
		if (ok)
		{
			char* back = buffer + strlen(buffer);
			//trim end spaces
			while ((buffer < back) && (isspace(*--back)));
			*(back + 1) = '\0';
			return buffer;
		}
		buffer[0] = '\0';
	}
	return NULL;
}


void cleanbuffer()
{
	int c;
	while ((c = getchar()) != '\n' && c != EOF);
}

// General print and free functions:
void printElement(void* element)
{
	structType* type = (structType*)element;
	switch (*type) {
	case eCity:
		printCity(element);
		break;
	case eDriver:
		printDriver(element);
		break;
	case eInspector:
		printInspector(element);
		break;
	case eRoute:
		printTrainRoute(element);
		break;
	case eTime:
		printTravelTime(element);
		break;
	case eTrain:
		printTrain(element);
		break;
	case eTrainCompany:
		printCompany(element);
		break;
	case eTrainStation:
		printTrainStation(element);
		break;
	}
}

void freeElement(void* element)
{
	structType* type = (structType*)element;
	switch (*type) {
	case eCity:
		freeCity(element);
		break;
	case eDriver:
		freeDriver(element);
		break;
	case eInspector:
		freeInspector(element);
		break;
	case eRoute:
		freeTrainRoute(element);
		break;
	case eTime:
		freeTravelTime(element);
		break;
	case eTrain:
		freeTrain(element);
		break;
	case eTrainCompany:
		freeCompany(element);
		break;
	case eTrainStation:
		freeTrainStation(element);
		break;
	}
}

void generalPrintArray(const void* elementsArray, const int numOfElements, const size_t elementSize)
{
	char* base = (char*)elementsArray;
	for (int i = 0; i < numOfElements; i++) {
		void* element = (void*)(base + i * elementSize);
		printElement(element);
	}
}

void generalFreeArray(const void* elementsArray, const int numOfElements, const size_t elementSize)
{
	char* base = (char*)elementsArray;
	for (int i = 0; i < numOfElements; i++) {
		void* element = (void*)(base + i * elementSize);
		freeElement(element);
	}
}

void generalArrayFunction(const void* elementsArray, const int numOfElements, const size_t elementSize, void (*function)(void*, int, size_t))
{
	if (function == generalPrintArray)
		generalPrintArray(elementsArray, numOfElements, elementSize);
	else if (function == generalFreeArray)
		generalFreeArray(elementsArray, numOfElements, elementSize);
}

void printMenuCase1()
{
	printf("\nYou've selected to update a train in the train company.\n");
	printf("Please choose one of the following options:\n");
	printf("1 - Add a new train to a company.\n");
	printf("2 - Update an existing train details.\n");
	printf("3 - Remove a train from the company.\n");
	printf("-1 - Return to the main menu.\n");
}

void printMenuCase2()
{
	printf("\nYou've selected to update an employee details in the train company.\n");
	printf("Please choose one of the following options:\n");
	printf("1 - Add a new driver.\n");
	printf("2 - Add a new inspector.\n");
	printf("3 - Change Driver license \n");
	printf("4 - Remove an employee from the system.\n");
	printf("-1 - Return to the main menu.\n");
}

void printMenuCase3()
{
	printf("\nYou've selected to update a city in the system.\n");
	printf("Please choose one of the following options:\n");
	printf("1 - Add a new city to the system.\n");
	printf("2 - Update an existing city details.\n");
	printf("3 - Remove a city from the system.\n");
	printf("-1 - Return to the main menu.\n");
}

void printMenuCase4()
{
	printf("\nYou've selected to update a train station.\n");
	printf("Please choose one of the following options:\n");
	printf("1 - Add a new train station to a city.\n");
	printf("2 - Update an existing station details.\n");
	printf("3 - Add a train to the train station.\n");
	printf("4 - Remove a station from a city.\n");
	printf("-1 - Return to the main menu.\n");
}

void printMenuCase5()
{
	printf("\nYou've selected to add a new train route.\n");
}

void printMenuCase6()
{
	printf("\nYou've selected to update an existing train route.\n");
	printf("Please choose one of the following options:\n");
	printf("1 - Update a train route.\n");
	printf("2 - Remove a train route.\n");
	printf("-1 - Return to the main menu.\n");
}

void printMenuCase6_1()
{
	printf("1 - Add a train station to the route.\n");
	printf("2 - Remove a train station from the route.\n");
	printf("3 - Change the routes driver.\n");
	printf("4 - Change the routes inspector.\n");
	printf("-1 - Return to the main menu.\n");
}

void printMenuCase7()
{
	printf("\nYou've selected to Print system information.\n");
	printf("Please choose one of the following options:\n");
	printf("1 - Print a company details.\n");
	printf("2 - Print a route details.\n");
	printf("3 - Print a city details.\n");
	printf("4 - Print all train station details.\n");
	printf("5 - Print all trains details.\n");
	printf("6 - Print all drivers details.\n");
	printf("7 - Print all inspectors trains. \n");
	printf("-1 - Return to the main menu.\n");
}

void printMenuCase8()
{
	printf("\nYou've selected to sort an array or search for information in an array.\n");
	printf("Please choose one of the following options:\n");
	printf("1 - Sort an existing array.\n");
	printf("2 - Search information in an existing array.\n");
	printf("-1 - Return to the main menu.\n");
}

void printMenuCase9()
{
	printf("\nYou've selected to use a special method.\n");
	printf("Please choose one of the following options:\n");
	printf("1 - Print the sum of all expected passengers in the company and the estimated company income.\n");
	printf("2 - copy an entire train station with trains to another city.\n");
	printf("-1 - Return to the main menu.\n");
}

void printAsciiTrain()
{
	printf("\n  oooOOOOOOOOOOO\"\n");
	printf("   o   ____          :::::::::::::::::: :::::::::::::::::: __|-----|__\n");
	printf("   Y_,_|[]| --++++++ |[][][][][][][][]| |[][][][][][][][]| |  [] []  |\n");
	printf("  {|_|_|__|;|______|;|________________|;|________________|;|_________|;\n");
	printf("   /oo--OO   oo  oo   oo oo      oo oo   oo oo      oo oo   oo     oo\n");
	printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+\n");
}

