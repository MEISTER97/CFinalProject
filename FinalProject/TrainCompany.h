/********************************************************************************************/
/* TrainCompany.h																		    */
/* This file contains information regarding the train companies                         	*/
/********************************************************************************************/

#ifndef TRAINCOMPANY_H
#define TRAINCOMPANY_H
#define PRINT(str) printf(#str "\n");

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Definitions.h"
#include "City.h"
#include "Route.h"
#include "Driver.h"
#include "List.h"

typedef struct {
    structType type;
    char* companyName;
    Train* trainsArray;
    int numOfTrains;
    Driver* driversArray;
    int numOfDrivers;
    Inspector* inspectorsArray;
    int numOfInspectors;
    City** citiesArray;
    int numOfActiveCities;
    Route** routesArray;
    int numOfRoutes;
} TrainCompany;

// Company functions:
int initTrainCompany(TrainCompany* pTrainCompany);
int changeCompanyName(TrainCompany* pTrainCompany);
void printCompany(TrainCompany* pTrainCompany);

// Train functions:
int addTrain(TrainCompany* pTrainCompany);
void removeTrain(TrainCompany* pTrainCompany, int serialNumber, int location);
int checkTrainid(const TrainCompany* pTrainCompany, int trainSerial);
int selectTrainToAddToTrainStation(TrainCompany* pTrainCompany);
void printTrains(const TrainCompany* pTrainCompany);
int findTrain(const TrainCompany* pTrainCompany, int serialNumber);
void updateTrain(TrainCompany* pTrainCompany, int serialNumber, int choice);

// Workers - Driver and Inspector functions:
int addDriver(TrainCompany* pTrainCompany);
int removeDriver(TrainCompany* pTrainCompany, int id, int location);
int addInspector(TrainCompany* pTrainCompany);
int removeInspector(TrainCompany* pTrainCompany, int id, int location);
int removeWorker(TrainCompany* pTrainCompany, int id);
int findWorker(const TrainCompany* pTrainCompany, const int id, int* choice);
void printDriverArray(const TrainCompany* pTrainCompany);
void printInspectorArray(const TrainCompany* pTrainCompany);
void printWorkerArray(const TrainCompany* pTrainCompany);
void chagneDriverLicense(TrainCompany* pTrainCompany, const int id);
int checkIfRandomLicenseOk(TrainCompany* pTrainCompany, int licenseNum);

// City functions:
int addCityToCompany(TrainCompany* pTrainCompany);
void printCityChoice(TrainCompany* pTrainCompany, char* cityCodeFind);
void printCities(const TrainCompany* pTrainCompany);
void printExpectedPassengers(const TrainCompany* pTrainCompany);
int findCityByCode(TrainCompany* pTrainCompany, const char* cityCodeFind);
void updateCity(TrainCompany* pTrainCompany, char* cityCodeFind, int choice);
void updateCityTrainStation(TrainCompany* pTrainCompany, char* cityCodeFind, int choice);
void removeCity(TrainCompany* pTrainCompany, int location);
int compareCityPassenger(const void* a, const void* b);
void sortCitiesByPassengers(City** citiesArray, int numOfCities);
int compareCityTrainQuantity(const void* a, const void* b);
void sortCitiesByTrains(City** citiesArray, int numOfCities);

// Route functions:
int addRoute(TrainCompany* pTrainCompany);
Route* initTrainRoute(TrainCompany* pTrainCompany);
int copyTrainStationToCity(TrainCompany* pTrainCompany, TrainStation* ts);
int updateRouteDriver(TrainCompany* pTrainCompany);
int updateRouteInspector(TrainCompany* pTrainCompany);
TrainStation* findTrainserial(TrainCompany* pTrainCompany, int serial);
int addTrainStopToRoute(TrainCompany* pTrainCompany, Route* route);
int removeTrainStopFromRoute(TrainCompany* pTrainCompany, Route* route);
void printTrainRouteInCompany(TrainCompany* pTrainCompany);

// Select functions - returns a pointer:
Train* selectTrain(TrainCompany* pTrainCompany);
Driver* selectDriver(TrainCompany* pTrainCompany);
Inspector* selectInspector(TrainCompany* pTrainCompany);
City* selectACity(TrainCompany* pTrainCompany);
TrainStation* selectAStation(City* pCity);
TrainStation* selectAStationFromList(LIST* list);
Route* selectRoute(TrainCompany* pTrainCompany);

// Train station functions:
void printTrainStationArray(const TrainCompany* ptrainCompany);
int checkIfStationNumberOk(const TrainCompany* pTrainCompany, int licenseNum);
void updateTrainStationInCity(TrainCompany* pTrainCompany, char* cityCodeFind);
int findTrainStationBySerial(const City* city, const int serialNum);

// Function to free allocated memory:
void freeDriverArray(TrainCompany* pTrainCompany);
void freeInspectorArray(TrainCompany* pTrainCompany);
void freeTrains(TrainCompany* pTrainCompany);
void freeCities(TrainCompany* pTrainCompany);
void freeCompany(TrainCompany* pTrainCompany);

// Text file functions:
void writeDriverT(FILE* file, const Driver* driver);
int readDriverT(FILE* file, Driver* driver);
void writeInspectorT(FILE* file, const Inspector* inspector);
int readInspectorT(FILE* file, Inspector* inspector);
void writeTrainToT(FILE* file, const Train* train);
int readTrainT(FILE* file, Train* train);
void writeCityToT(FILE* file, const City* city);
int readCityT(FILE* file, City* city);
int saveInfoToFileT(const TrainCompany* pTrainCompany, const char* fileName);
void writeStationToT(FILE* file, const City* city);
void writeRouteToT(FILE* file, const Route* route);
int readListFromFileText(FILE* file, LIST* list);
int ReadInfoFromT(TrainCompany* pTrainCompany, const char* fileName);
void writeListToFileText(FILE* file, const LIST* list);

// Binary file functions
int writeDriverToFileB(FILE* file, const Driver* driver);
int readDriverFromFileBNested(FILE* file, Driver* driver);
int readDriverFromFileB(FILE* file, Driver* driver);
int writeInspectorToFileB(FILE* file, const Inspector* inspector);
int readInspectorFromFileB(FILE* file, Inspector* inspector);
int writeTrainToFileB(FILE* file, const Train* train);
int readTrainFromFileB(FILE* file, Train* train);
int writeTimeToFileB(FILE* file, const Time* time);
int readTimeToFileB(FILE* file, Time* time);
int writeListToFileB(FILE* file, const LIST* list);
int readListFromFileB(FILE* file, LIST* list);
int writeCityToFileB(FILE* file, const City* city);
int readCityFromFileB(FILE* file, City* city);
int readStationToB(FILE* file, TrainStation* station);
int saveInfoToFileB(const TrainCompany* pTrainCompany, const char* fileName);
int readInfoFromBinary(TrainCompany* pTrainCompany, const char* fileName);
int readListFromFileB(FILE* file, LIST* list);
int writeRouteToFileB(FILE* file, const Route* route);
int readRouteFromB(FILE* file, Route* route);
int writeStationToB(FILE* file, const TrainStation* station);

#endif