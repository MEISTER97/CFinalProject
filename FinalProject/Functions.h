/********************************************************************************************/
/* Functions.h																				*/
/* This file contains general functions used in several places in the code	*/
/********************************************************************************************/

#ifndef __FUNCTIONS__
#define __FUNCTIONS__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define PRINT_INFORMATION_TRAIN_STATION() \
    do { \
        printf("train station can be connected to a city and for the following condition:\n"); \
        printf("1)Alpha Plus - [only 5 stations]\n"); \
        printf("2)Alpha - [only 3 stations]\n"); \
        printf("3)Beta Plus- [only 2 stations]\n"); \
        printf("4)Beta- [only 1 station]\n"); \
    } while(0)
#define PRINT_INFORMATION_SORT() \
    do { \
        printf("1)Sort the drivers array by License type(Fast-Passenger 1,Light-Passenger 2,Metro 3,Cargo 4)  \n"); \
        printf("2)Sort the cities array to which will have the most predicted passengers from station\n"); \
        printf("3)sort the cities by trains quantity in city\n"); \
    } while(0)
#define PRINT_INFORMATION_BSEARCH() \
    do { \
        printf("1)search the driver license in the array of drivers if exist \n"); \
        printf("2)search the city code in the array cities if exist \n"); \
        printf("3)search the train serial number in the array of train staions(check if train is active)\n"); \
    } while(0)
#define PRINT_MAIN_MENU() do { \
    printf("\nPlease choose one of the following options:\n"); \
    printf("0 - Change the company's name.\n"); \
    printf("1 - Update a train in the train company - add a new train, update an existing train details or remove a train from the company.\n"); \
    printf("2 - Update an employee in the train company - add a new driver or inspector, update an existing employee details or remove an employee from the system.\n"); \
    printf("3 - Update a city in the system - add a new city to the system, update an existing city details or remove the city from the system.\n"); \
    printf("4 - Update a train station - add a new train station to a city, update an existing station details or remove it from a city.\n"); \
    printf("5 - Add a new train route - choose an available train, driver, inspector and route.\n"); \
    printf("6 - Update an existing route - update or remove an existing train route.\n"); \
    printf("7 - Print system information - select which information the user would like to print.\n"); \
    printf("8 - Sort or search in an existing array - select which array the user would like to sort or search.\n"); \
    printf("9 - Use a special method.\n"); \
    printf("-1 - for exit.\n"); \
} while(0)

// Functions:
char* myGets(char* buffer, int size);
void cleanbuffer();

// General print and free functions:
void printElement(const void* element);
void freeElement(void* element);
void generalPrintArray(void* elementsArray, int numOfElements, size_t elementSize);
void generalFreeArray(void* elementsArray, int numOfElements, size_t elementSize);
void generalArrayFunction(void* elementsArray, int numOfElements, size_t elementSize, void (*function)(void*, int, size_t));

// Menu printing functions:
void printMenuCase1();
void printMenuCase2();
void printMenuCase3();
void printMenuCase4();
void printMenuCase5();
void printMenuCase6();
void printMenuCase6_1();
void printMenuCase7();
void printMenuCase8();
void printMenuCase9();
void printAsciiTrain();



#endif
