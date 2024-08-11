#define _CRT_SECURE_NO_WARNINGS
#include "TrainCompany.h"
#include "Driver.h"
#include "Inspector.h"
#include "List.h"




// init train company
int initTrainCompany(TrainCompany* pTrainCompany)
{
	pTrainCompany->type = eTrainCompany;
	// Set the company's name:
	char tempString[MAX_STR_LEN] = "";
	printf("Please type the company's name: \n");
	myGets(tempString, MAX_STR_LEN);
	pTrainCompany->companyName = malloc(strlen(tempString) + 1);
	if (pTrainCompany->companyName == NULL) {
		printf("Error allocating memory for company name.\n");
		return 0; // Indicate failure
	}
	strncpy(pTrainCompany->companyName, tempString, strlen(tempString));
	pTrainCompany->companyName[strlen(tempString)] = '\0';

	pTrainCompany->trainsArray = NULL;
	pTrainCompany->numOfTrains = 0;
	// Set the drivers array:
	pTrainCompany->driversArray = NULL;
	pTrainCompany->numOfDrivers = 0;
	// Set the inspectors array:
	pTrainCompany->inspectorsArray = NULL;
	pTrainCompany->numOfInspectors = 0;
	// Set the cities array:
	pTrainCompany->citiesArray = NULL;
	pTrainCompany->numOfActiveCities = 0;
	// Set the routes array:
	pTrainCompany->routesArray = NULL;
	pTrainCompany->numOfRoutes = 0;
	
	return 1; // Success
}
// add train to the company
int addTrain(TrainCompany* pTrainCompany)
{
	Train* tempTrain = (Train*)malloc(sizeof(Train));
	if (tempTrain == NULL)
	{
		printf("Error allocating train memory.\n");
		return 0;
	}
	//init train
	initTrain(tempTrain, pTrainCompany->trainsArray, pTrainCompany->numOfTrains);
	// check serial number
	tempTrain->serialNumber= checkTrainid(pTrainCompany, tempTrain->serialNumber);
	if (tempTrain->serialNumber == -1)
	{
		printf("Error id check\n");
		free(tempTrain);
		return 0;
	}

	Train* tempTrainsArray = (Train*)realloc(pTrainCompany->trainsArray, (pTrainCompany->numOfTrains + 1) * sizeof(Train));
	if (tempTrainsArray == NULL)
	{
		printf("Error reallocating train array memory.\n");
		free(tempTrain);
		return 0;
	}

	pTrainCompany->trainsArray = tempTrainsArray;
	pTrainCompany->numOfTrains++;
	pTrainCompany->trainsArray[pTrainCompany->numOfTrains - 1] = *tempTrain;
	printf("Train %d have been added successfully\n", tempTrain->serialNumber);
	free(tempTrain);


	return 1;
}


void removeTrain(TrainCompany* pTrainCompany, int serialNumber, int location)
{
	// Shift the trains after the removed train one position to the left
	for (int i = location; i < pTrainCompany->numOfTrains - 1; i++)
	{
		pTrainCompany->trainsArray[i] = pTrainCompany->trainsArray[i + 1];
	}

	// Update the number of trains
	pTrainCompany->numOfTrains--;

	// Allocate memory for the new trains array
	Train* tempTrainsArray = malloc(pTrainCompany->numOfTrains * sizeof(Train));
	if (tempTrainsArray == NULL)
	{
		printf("Error allocating memory for trains array.\n");
		return;
	}
	
	// Copy existing elements to the new array
	for (int i = 0; i < pTrainCompany->numOfTrains; i++)
	{
		tempTrainsArray[i] = pTrainCompany->trainsArray[i];
	}

	// Free the old trains array
	free(pTrainCompany->trainsArray);

	// Update the trains array pointer
	pTrainCompany->trainsArray = tempTrainsArray;

	printf("Train with serial number %d has been removed.\n", serialNumber);
}

int checkTrainid(const TrainCompany* pTrainCompany, int trainSerial)
{
	boolean updated = True;
	while (updated) {
		updated = False; // Reset the flag for each iteration

		// Check if the license number exists in the drivers array
		for (int i = 0; i < pTrainCompany->numOfTrains; i++) {
			if (pTrainCompany->trainsArray[i].serialNumber == trainSerial) {
				trainSerial = rand() % 9999 + 1; // Generate a new random number
				updated = True;
				break; // Exit the loop once a match is found
			}
		}
		return trainSerial;
	}


	return -1;
}

int changeCompanyName(TrainCompany* pTrainCompany)
{
	printf("\nYou have selected to change the company's name.\n");
	printf("Enter the new name here:\n");
	char temp[MAX_STR_LEN];
	myGets(temp, MAX_STR_LEN);
	char* tempName = realloc(pTrainCompany->companyName, strlen(temp) + 1);
	if (tempName == NULL)
	{
		printf("Error reallocating name.\n");
		return 0;
	}
	pTrainCompany->companyName = tempName;
	if (pTrainCompany->companyName == NULL) {
		// Handle allocation failure
		printf("Memory allocation failed.\n");
		return 0; // Return 0 to indicate failure
	}
	strcpy(pTrainCompany->companyName, temp);
	printf("the company's name has been successfully changed to %s.\n", pTrainCompany->companyName);
	return 1;
}



int addDriver(TrainCompany* pTrainCompany)
{
	Driver* tempDriver = (Driver*)malloc(sizeof(Driver));
	if (tempDriver == NULL)
	{
		printf("Error allocating driver memory.\n");
		free(tempDriver);
		return 0;
	}
	initDriver(tempDriver);
	tempDriver->licenseNumber= checkIfRandomLicenseOk(pTrainCompany,tempDriver->licenseNumber);
	Driver* tempDriversArray = (Driver*)realloc(pTrainCompany->driversArray, (pTrainCompany->numOfDrivers + 1) * sizeof(Driver));
	if (tempDriversArray == NULL)
	{
		printf("Error allocating driver array memory.\n");
		free(tempDriversArray);
		return 0;
	}
	pTrainCompany->driversArray = tempDriversArray;
	pTrainCompany->numOfDrivers++;
	pTrainCompany->driversArray[pTrainCompany->numOfDrivers - 1] = *tempDriver;
	
	printf("driver licenseNumber %d have been added\n", tempDriver->licenseNumber);
	free(tempDriver);

	return 1;
}

int removeDriver(TrainCompany* pTrainCompany, int id, int location) {

	// Shift the drivers after the removed driver one position to the left
	for (int i = location; i < pTrainCompany->numOfDrivers - 1; i++) {
		pTrainCompany->driversArray[i] = pTrainCompany->driversArray[i + 1];
	}

	// Update the number of drivers
	pTrainCompany->numOfDrivers--;

	// Allocate memory for the new drivers array
	Driver* temp = malloc(pTrainCompany->numOfDrivers * sizeof(Driver));
	if (temp == NULL) {
		printf("Error reallocating memory.\n");
		return 0;
	}

	// Copy existing elements to the new array
	for (int i = 0; i < pTrainCompany->numOfDrivers; i++) {
		temp[i] = pTrainCompany->driversArray[i];
	}

	// Free the original array
	free(pTrainCompany->driversArray);

	// Update the drivers array pointer
	pTrainCompany->driversArray = temp;

	printf("Worker %d in driver array has been removed.\n", id);

	return 1;
}





int addInspector(TrainCompany* pTrainCompany)
{
	Inspector* tempInspector = (Inspector*)malloc(sizeof(Inspector));

	if (tempInspector == NULL)
	{
		printf("Error allocating inspector memory.\n");
		free(tempInspector);
		return 0;
	}
	initInspector(tempInspector);
	tempInspector->licenseNumber = checkIfRandomLicenseOk(pTrainCompany, tempInspector->licenseNumber);

	Inspector* tempInspectorsArray = (Inspector*)realloc(pTrainCompany->inspectorsArray, (pTrainCompany->numOfInspectors + 1) * sizeof(Inspector));

	if (tempInspectorsArray == NULL)
	{
		printf("Error allocating inspector array memory.\n");
		free(tempInspectorsArray);
		return 0;
	}


	pTrainCompany->inspectorsArray = tempInspectorsArray;
	pTrainCompany->numOfInspectors++;
	pTrainCompany->inspectorsArray[pTrainCompany->numOfInspectors - 1] = *tempInspector;

	printf("inspector licenseNumber %d have been added\n", tempInspector->licenseNumber);

	free(tempInspector);

	return 1;
}

int removeInspector(TrainCompany* pTrainCompany, int id, int location) {
	if (location < 0 || location >= pTrainCompany->numOfInspectors) {
		printf("Invalid location.\n");
		return 0;
	}

	// Allocate memory for the new array
	Inspector* temp = malloc((pTrainCompany->numOfInspectors - 1) * sizeof(Inspector));
	if (temp == NULL) {
		printf("Error allocating memory.\n");
		return 0;
	}

	// Copy elements before the removed one
	for (int i = 0; i < location; i++) {
		temp[i] = pTrainCompany->inspectorsArray[i];
	}

	// Copy elements after the removed one
	for (int i = location + 1; i < pTrainCompany->numOfInspectors; i++) {
		temp[i - 1] = pTrainCompany->inspectorsArray[i];
	}

	// Free the old array and update the inspector array and number of inspectors
	free(pTrainCompany->inspectorsArray);
	pTrainCompany->inspectorsArray = temp;
	pTrainCompany->numOfInspectors--;

	printf("Inspector with ID %d has been removed.\n", id);
	return 1;
}



int removeWorker(TrainCompany* pTrainCompany, int id)
{
	int choice = -1;
	int location;
	location = findWorker(pTrainCompany, id, &choice);
	if (location != -1)
	{
		if (choice == 0)
		{

			removeDriver(pTrainCompany, id, location);

		}
		else
		{

			removeInspector(pTrainCompany, id, location);


		}
	}
	else
	{
		printf("Worker is not found.\n");
		return 0;
	}
	return 1;
}



int findWorker(const TrainCompany* pTrainCompany, const int id,  int* choice)
{
	for (int i = 0; i < pTrainCompany->numOfDrivers; i++)
	{
		if (pTrainCompany->driversArray[i].licenseNumber == id)
		{
			printf("Found worker in driver array:\n");
			*choice = 0;
			return i;
		}

	}

	for (int i = 0; i < pTrainCompany->numOfInspectors; i++)
	{
		if (pTrainCompany->inspectorsArray[i].licenseNumber == id)
		{
			printf("Found worker in inspector array:\n");
			*choice = 1;
			return i;

		}

	}

	return -1;
}


int addCityToCompany(TrainCompany* pTrainCompany)
{
	City* tempCity = (City*)malloc(sizeof(City));
	if (tempCity == NULL)
	{
		printf("Error allocating city memory.\n");
		free(tempCity);
		return 0;
	}
	boolean flag = True;
	int check = 0;
	while (flag)
	{
		initCity(tempCity);
		flag = False;
		check = findCityByCode(pTrainCompany, tempCity->cityCode);
		if (check != -1) {
			flag = True;
			printf("City code is already in the array! try again\n");
		}
	}

	City** tempcitiesArray = (City**)realloc(pTrainCompany->citiesArray, (pTrainCompany->numOfActiveCities + 1) * sizeof(City*));
	if (tempcitiesArray == NULL)
	{
		printf("Error allocating city array memory.\n");
		return 0;
	}

	pTrainCompany->citiesArray = tempcitiesArray;
	pTrainCompany->numOfActiveCities++;
	pTrainCompany->citiesArray[pTrainCompany->numOfActiveCities - 1] = tempCity;

	return 1;
}


// Routes functions:
void printTrainRouteInCompany(TrainCompany* pTrainCompany)
{
	int choice;
	printf("Would you like to print a specific route or print all the available routes?\n");
	printf("Select 0 to choose a specific route, or 1 to print all routes\n");
	if (pTrainCompany->numOfRoutes == 0)
	{
		printf("there is no routes in the company\n");
		return;
	}
	if (scanf("%d", &choice) != 1)
	{
		printf("Bad input.\n");
		return;
	}
	if (choice == 0)
	{
		Route* tempRoute = selectRoute(pTrainCompany);
		printTrainRoute(tempRoute);
	}
	else if (choice == 1)
		for (int i = 0; i < pTrainCompany->numOfRoutes; i++)
			printTrainRoute(pTrainCompany->routesArray[i]);
	else
		printf("Bad input.\n");
}


int addRoute(TrainCompany* pTrainCompany) {
	// Initialize a new route
	Route* route = initTrainRoute(pTrainCompany);
	if (route == NULL) {
		return 0;
	}
	
	// If routesArray is not NULL, reallocate memory to accommodate the new route
	if (pTrainCompany->routesArray != NULL) {
		Route** tempRoute = (Route**)realloc(pTrainCompany->routesArray, (pTrainCompany->numOfRoutes + 1) * sizeof(Route*));
		if (tempRoute == NULL) {
			printf("Error reallocating memory for routes array.\n");
			free(route);
			return 0;
		}
		pTrainCompany->routesArray = tempRoute;
	}
	else {
		// If routesArray is NULL, allocate memory for the routes array
		pTrainCompany->routesArray = (Route**)malloc(sizeof(Route*));
		if (pTrainCompany->routesArray == NULL) {
			printf("Error allocating memory for routes array.\n");
			free(route);
			return 0;
		}
	}

	// Add the new route to the routesArray
	pTrainCompany->routesArray[pTrainCompany->numOfRoutes] = route;
	pTrainCompany->numOfRoutes++;
	printf("\nRoute has been successfully added.\n");
	return 1;
}

void cleanUpRoute(Route* route) {
	if (route->train != NULL) {
		freeTrain(route->train);
	}
	if (route->driver != NULL) {
		freeDriver(route->driver);
	}

	if (route->inspector != NULL) {
		freeInspector(route->inspector);
	}

	free(route->departureTime);



	L_free(route->trainStationsList);

	free(route);

}

Route* initTrainRoute(TrainCompany* pTrainCompany)
{
	Route* route = (Route*)malloc(sizeof(Route));
	if (route == NULL)
	{
		printf("Error allocating route memory.\n");
		free(route);
		return NULL;
	}

	route->type = eRoute;
	// Loop that sets the route's id:
	boolean badSerialNumber = True;
	int tempSerialNumber;
	while (badSerialNumber)
	{
		badSerialNumber = False;
		srand((unsigned int)time(NULL));
		// generate random number 1-9999
		tempSerialNumber = rand() % 9999 + 1;
		for (int i = 0; i < pTrainCompany->numOfRoutes; i++)// Checks if there is already a route with the same serial number
			if ((*pTrainCompany->routesArray[i]).routeId == tempSerialNumber)
				badSerialNumber = True;
	}

	route->routeId = tempSerialNumber;
	// Select the route's train:

	route->train = malloc(sizeof(Train));
	if (route->train == NULL) {
		free(route);
		return NULL;
	}

	Train* selectedTrain = selectTrain(pTrainCompany);
	if (selectedTrain == NULL)
	{
		free(route->train);
		free(route);
		return NULL;
	}

	// Copy the data from selectedTrain to route->train
	memcpy(route->train, selectedTrain, sizeof(Train));

	route->driver = malloc(sizeof(Driver));
	if (route->driver == NULL)
	{
		free(route->train);
		free(route);
		return NULL;
	}

	// Select the route's driver:
	Driver* selectedDriver = selectDriver(pTrainCompany);
	if (selectedDriver == NULL)
	{
		free(route->train);
		free(route);
		return NULL;
	}
	memcpy(route->driver, selectedDriver, sizeof(Driver));
	route->driver->DriverName = malloc(strlen(selectedDriver->DriverName) + 1);
	if (route->driver->DriverName == NULL)
	{
		free(route->driver);
		free(route->train);
		free(route);
		return NULL;
	}
	strcpy(route->driver->DriverName, selectedDriver->DriverName);
	route->driver->DriverName[strlen(selectedDriver->DriverName)] = '\0';
	
	if (route->driver->licenseType != route->train->trainType)
	{
		printf("the driver %s cannot drive train %s, try again\n", TrainTypeStr[route->driver->licenseType], TrainTypeStr[route->train->trainType]);
		free(route->driver->DriverName);
		free(route->driver);
		free(route->train);
		free(route);
		return NULL;
	}
	// Select the route's inspector:
	route->inspector = malloc(sizeof(Inspector));
	if (route->inspector == NULL)
	{
		free(route->driver->DriverName);
		free(route->driver);
		free(route->train);
		free(route);
		return NULL;
	}
	Inspector* tempInspector = selectInspector(pTrainCompany);
	if (tempInspector == NULL)
	{
		free(route->inspector);
		free(route->driver->DriverName);
		free(route->driver);
		free(route->train);
		free(route);
		return NULL;
	}
	memcpy(route->inspector, tempInspector, sizeof(Inspector));
	route->inspector->InspectorName = malloc(strlen(tempInspector->InspectorName) + 1);
	if (route->inspector->InspectorName == NULL)
	{
		free(route->inspector);
		free(route->driver->DriverName);
		free(route->driver);
		free(route->train);
		free(route);
		return NULL;
	}
	strcpy(route->inspector->InspectorName, tempInspector->InspectorName);



	// Set route's train station list:
	LIST* trainStationsList = (LIST*)malloc(sizeof(LIST));
	if (trainStationsList == NULL)
	{
		printf("Error allocating stations list memory.\n");
		free(route->inspector->InspectorName);
		free(route->inspector);
		free(route->driver->DriverName);
		free(route->driver);
		free(route->train);
		free(route);
		return NULL;
	}
	trainStationsList->head.next = NULL;
	// Select the route's source train station:
	NODE* sourceNode = (NODE*)malloc(sizeof(NODE));
	if (sourceNode == NULL) {
		printf("Error allocating station node memory.\n");
		free(trainStationsList);
		free(route->inspector->InspectorName);
		free(route->inspector);
		free(route->driver->DriverName);
		free(route->driver);
		free(route->train);
		free(route);
		return NULL;
	}

	trainStationsList->head.next = sourceNode;

	City* tempCity = selectACity(pTrainCompany);
	if (tempCity == NULL) {
		printf("Error selecting city.\n");
		free(sourceNode);
		free(trainStationsList);
		free(route->inspector->InspectorName);
		free(route->inspector);
		free(route->driver->DriverName);
		free(route->driver);
		free(route->train);
		free(route);
		return NULL;
	}
	TrainStation* tempStation = malloc(sizeof(TrainStation));
	if (tempStation == NULL) {
		printf("Error selecting station.\n");
		free(sourceNode);
		free(trainStationsList);
		free(route->inspector->InspectorName);
		free(route->inspector);
		free(route->driver->DriverName);
		free(route->driver);
		free(route->train);
		free(route);
		return NULL;
	}
	TrainStation* selectedStation = selectAStation(tempCity);
	if (tempStation == NULL) {
		printf("Error selecting station.\n");
		free(tempStation);
		free(sourceNode);
		free(trainStationsList);
		free(route->inspector->InspectorName);
		free(route->inspector);
		free(route->driver->DriverName);
		free(route->driver);
		free(route->train);
		free(route);
		return NULL;
	}
	tempStation->stationName = malloc(strlen(selectedStation->stationName) + 1);
	if (tempStation->stationName == NULL)
	{
		printf("Error allocating memory.\n");
		free(tempStation);
		free(sourceNode);
		free(trainStationsList);
		free(route->inspector->InspectorName);
		free(route->inspector);
		free(route->driver->DriverName);
		free(route->driver);
		free(route->train);
		free(route);
		return NULL;
	}

	strcpy(tempStation->stationName, selectedStation->stationName);
	tempStation->stationName[strlen(selectedStation->stationName)] = '\0';
	tempStation->locatedInCity = malloc(strlen(selectedStation->locatedInCity) + 1);
	if (tempStation->locatedInCity == NULL) {
		printf("Error allocating memory.\n");
		free(tempStation);
		free(trainStationsList);
		free(route->inspector->InspectorName);
		free(route->inspector);
		free(route->driver->DriverName);
		free(route->driver);
		free(route->train);
		free(route);
		free(sourceNode);
		return NULL;
	}
	strcpy(tempStation->locatedInCity, selectedStation->locatedInCity);
	tempStation->locatedInCity[strlen(selectedStation->locatedInCity)] = '\0';
	memcpy(tempStation, selectedStation, sizeof(TrainStation));


	if (route->train->trainType != tempStation->trainStationType) {
		printf("Error: Train type %s cannot use this station type %s.\n", TrainTypeStr[route->train->trainType], TrainTypeStation[tempStation->trainStationType]);
		free(tempStation);
		free(trainStationsList);
		free(route->inspector->InspectorName);
		free(route->inspector);
		free(route->driver->DriverName);
		free(route->driver);
		free(route->train);
		free(route);
		free(sourceNode);
		return NULL;
	}

	sourceNode->key = tempStation;

	printf("Now enter destination(next route)\n");

	// Select the route's destination train station:
	NODE* destNode = (NODE*)malloc(sizeof(NODE));
	if (destNode == NULL) {
		printf("Error allocating station node memory.\n");
		free(tempStation);
		free(sourceNode);
		free(trainStationsList);
		free(route->inspector->InspectorName);
		free(route->inspector);
		free(route->driver->DriverName);
		free(route->driver);
		free(route->train);
		free(route);
		return NULL;
	}

	City* tempCity2 = selectACity(pTrainCompany);
	if (tempCity2 == NULL) {
		printf("Error selecting city.\n");
		free(tempStation);
		free(trainStationsList);
		free(route->inspector->InspectorName);
		free(route->inspector);
		free(route->driver->DriverName);
		free(route->driver);
		free(route->train);
		free(route);
		free(sourceNode);
		free(destNode);
		return NULL;
	}

	TrainStation* tempStation2 = malloc(sizeof(TrainStation));
	if (tempStation2 == NULL) {
		printf("Error selecting station.\n");
		free(tempStation);
		free(trainStationsList);
		free(route->inspector->InspectorName);
		free(route->inspector);
		free(route->driver->DriverName);
		free(route->driver);
		free(route->train);
		free(route);
		free(sourceNode);
		free(destNode);
		return NULL;
	}
	selectedStation = selectAStation(tempCity2);
	if (selectedStation == NULL) {
		printf("Error selecting station.\n");
		free(tempStation2);
		free(tempStation);
		free(trainStationsList);
		free(route->inspector->InspectorName);
		free(route->inspector);
		free(route->driver->DriverName);
		free(route->driver);
		free(route->train);
		free(route);
		free(sourceNode);
		free(destNode);
		return NULL;
	}
	tempStation2->stationName = malloc(strlen(selectedStation->stationName) + 1);
	if (tempStation2->stationName == NULL)
	{
		printf("Error allocating memory.\n");
		free(tempStation2);
		free(tempStation);
		free(trainStationsList);
		free(route->inspector->InspectorName);
		free(route->inspector);
		free(route->driver->DriverName);
		free(route->driver);
		free(route->train);
		free(route);
		free(sourceNode);
		free(destNode);
		return NULL;
	}
	strcpy(tempStation2->stationName, selectedStation->stationName);
	tempStation2->stationName[strlen(selectedStation->stationName)] = '\0';
	tempStation2->locatedInCity = malloc(strlen(selectedStation->locatedInCity) + 1);
	if (tempStation2->locatedInCity == NULL)
	{
		printf("Error allocating memory.\n");
		free(tempStation2);
		free(tempStation);
		free(trainStationsList);
		free(route->inspector->InspectorName);
		free(route->inspector);
		free(route->driver->DriverName);
		free(route->driver);
		free(route->train);
		free(route);
		free(sourceNode);
		free(destNode);
		return NULL;
	}
	strcpy(tempStation2->locatedInCity, selectedStation->locatedInCity);
	tempStation2->locatedInCity[strlen(selectedStation->locatedInCity)] = '\0';
	memcpy(tempStation2, selectedStation, sizeof(TrainStation));


	// Check if the destination is the same as the source
	if (tempStation2->stationSerialNumber == tempStation->stationSerialNumber && strcmp(tempCity->cityCode, tempCity2->cityCode) == 0) {
		printf("Error: The destination is the same as the current station.\n");
		free(tempStation2);
		free(tempStation);
		free(trainStationsList);
		free(route->inspector->InspectorName);
		free(route->inspector);
		free(route->driver->DriverName);
		free(route->driver);
		free(route->train);
		free(route);
		free(sourceNode);
		free(destNode);
		return NULL;
	}

	destNode->key = tempStation2;
	sourceNode->next = destNode;
	destNode->next = NULL;

	route->trainStationsList = trainStationsList;
	route->numOfStation = 2;
	cleanbuffer();
	route->departureTime = malloc(sizeof(Time));
	printf("enter the departure time\n");
	initTravelTime(route->departureTime);

	return route;
}


int addTrainStopToRoute(TrainCompany* pTrainCompany, Route* route)
{
	NODE* tempNode = (NODE*)malloc(sizeof(NODE));
	if (!tempNode)
	{
		printf("Error allocating train stop node memory\n");
		return 0;
	}

	printf("\nPlease select a city you would like to add to the route.\n");
	City* tempCity = selectACity(pTrainCompany);// Select a city from the cities array


	printf("\nPlease select a train station in the chosen city you would like to add to the route.\n");
	TrainStation* tempTrainStation = selectAStation(tempCity);// Select a train station from the cities array

	tempNode->key = tempTrainStation;

	TrainStation* tempTrainStation2 = selectAStationFromList(route->trainStationsList);// Select a train station to add to the route

	if (tempTrainStation2 == NULL)
	{
		printf("Error selecting train station.\n");
		return 0;
	}
	if (tempTrainStation->stationSerialNumber == tempTrainStation2->stationSerialNumber)// If the user chose the same train station in the list to be added
	{
		printf("You chose the same train station you wished to add, canceling the train station addition.\n");
		return 0;
	}

	NODE* tempNode2;
	tempNode2 = L_find(&route->trainStationsList->head, tempTrainStation2);// Find the location of the selected station node

	L_insert(tempNode2, tempTrainStation);// Add the new station to the train stations list
	route->numOfStation++;
	printf("\nTrain station %s has been added to route number %d.\n", ((TrainStation*)(tempNode->key))->stationName, route->routeId);

	return 1;
}

int removeTrainStopFromRoute(TrainCompany* pTrainCompany, Route* route)
{
	int trainStationSerialNumber;
	NODE* tempNode = &route->trainStationsList->head;
	int flag = 1;

	printf("Please select which train stop you would like to remove from the route:\n");
	L_short_print(route->trainStationsList);
	printf("Please select a station by writing the train station serial number:\n");
	if (scanf("%d", &trainStationSerialNumber) != 1)
	{
		printf("Bad input.\n");
		return 0;
	}

	while (tempNode != NULL && flag)// Checks if the serial number the user entered exists in the train stations list
	{
		if (trainStationSerialNumber == ((TrainStation*)tempNode->next->key)->stationSerialNumber)// If found
			flag = 0;
		tempNode = tempNode->next;
	}
	if (flag == 1)// If the station was not found
	{
		printf("You have entered an invalid train station serial number.\n");
		return 0;
	}

	if (L_delete(tempNode) == 0)// Removes the train station node and check if successful
	{
		printf("Error removing train station node.\n");
		return 0;
	}

	printf("The train station has been successfully removed from the route's train station list.\n");

	return 1;
}

int checkIfStationNumberOk(const TrainCompany* pTrainCompany, int licenseNum)
{
	srand((int)time(NULL)); // Seed the random number generator
	boolean updated = True;
	while (updated)
	{
		updated = False;
		// Check if the license number exists in the drivers array
		for (int i = 0; i < pTrainCompany->numOfActiveCities; i++)
		{
			for(int j=0;j<pTrainCompany->citiesArray[i]->numOfStations;j++)
			if (pTrainCompany->citiesArray[i]->trainStations[j]->stationSerialNumber == licenseNum) {
				licenseNum = rand() % 9999 + 1; // Generate a new random number
				updated = True;
				break;
			}
		}
		// If the license number was found among drivers, no need to check inspectors
		if (!updated) {
			// Check if the license number exists in the inspectors array
			for (int i = 0; i < pTrainCompany->numOfInspectors; i++) {
				if (pTrainCompany->inspectorsArray[i].licenseNumber == licenseNum) {
					licenseNum = rand() % 9999 + 1; // Generate a new random number
					updated = True;
					break;
				}
			}


		}
	}
	return licenseNum; // Original license number is OK
}

//deep copy
int copyTrainStationToCity(TrainCompany* pTrainCompany, TrainStation* ts) 
{
	printf("Please select city to paste to:\n");

	City* destinationCity = selectACity(pTrainCompany);
	if (destinationCity == NULL) {
		printf("Invalid destination city.\n");
		return 0;
	}

	// Check if the train station is already in the destination city
	for (int i = 0; i < destinationCity->numOfStations; i++) {
		if (destinationCity->trainStations[i]->stationSerialNumber == ts->stationSerialNumber) {
			printf("The train station is already in the city.\n");
			return 0;
		}
	}

	// Allocate memory for the new TrainStation
	TrainStation* copiedStation = (TrainStation*)malloc(sizeof(TrainStation));
	if (copiedStation == NULL) {
		printf("Memory allocation failed.\n");
		return 0;
	}

	// Reallocate memory for the trainStations array to accommodate the new train station
	TrainStation** temp = (TrainStation**)realloc(destinationCity->trainStations, (destinationCity->numOfStations + 1) * sizeof(TrainStation*));
	if (temp == NULL) {
		printf("Memory allocation failed.\n");
		free(copiedStation->platforms); // Free memory allocated for the copied platforms
		free(copiedStation->stationName); // Free memory allocated for the copied stationName
		free(copiedStation); // Free memory allocated for the copied station
		return 0;
	}
	destinationCity->trainStations = temp;

	// Allocate memory for the new train station
	destinationCity->trainStations[destinationCity->numOfStations] = malloc(sizeof(TrainStation));
	if (destinationCity->trainStations[destinationCity->numOfStations] == NULL) {
		printf("Memory allocation failed.\n");
		free(copiedStation->platforms); // Free memory allocated for the copied platforms
		free(copiedStation->stationName); // Free memory allocated for the copied stationName
		free(copiedStation); // Free memory allocated for the copied station
		return 0;
	}

	// Copy each field of the TrainStation individually
	copiedStation->stationSerialNumber = ts->stationSerialNumber;
	//generate new serial numfer for station
	copiedStation->stationSerialNumber = checkIfStationNumberOk(pTrainCompany, copiedStation->stationSerialNumber);
	copiedStation->trainStationType = ts->trainStationType;
	
	// Allocate memory for stationName and copy the string
	copiedStation->stationName = (char*)malloc(strlen(ts->stationName) + 1);
	if (copiedStation->stationName == NULL) {
		printf("Memory allocation failed.\n");
		free(copiedStation); // Free memory allocated for the copied station
		return 0;
	}
	strcpy(copiedStation->stationName, ts->stationName);
	copiedStation->stationName[strlen(ts->stationName)] = '\0';

	copiedStation->numOfActiveTrains = ts->numOfActiveTrains;
	copiedStation->numOfPlatforms = ts->numOfPlatforms;
	copiedStation->expectedNumOfPassengers = ts->expectedNumOfPassengers;

	copiedStation->locatedInCity = (char*)malloc(strlen(destinationCity->name) + 1);
	if (copiedStation->locatedInCity == NULL) {
		printf("Memory allocation failed.\n");
		free(copiedStation); // Free memory allocated for the copied station
		return 0;
	}

	strcpy(copiedStation->locatedInCity, ts->locatedInCity);
	copiedStation->locatedInCity[strlen(ts->locatedInCity)] = '\0';

	copiedStation->type = ts->type;

	// Deep copy the platforms array
	copiedStation->platforms = (Train**)malloc(ts->numOfActiveTrains * sizeof(Train*));
	if (copiedStation->platforms == NULL) {
		printf("Memory allocation failed.\n");
		free(copiedStation); // Free memory allocated for the copied station
		return 0;
	}
	for (int i = 0; i < ts->numOfActiveTrains; i++) {
		copiedStation->platforms[i] = (Train*)malloc(sizeof(Train));
		if (copiedStation->platforms[i] == NULL) {
			printf("Memory allocation failed.\n");
			// Free memory allocated for previously copied platforms
			for (int j = 0; j < i; j++) {
				free(copiedStation->platforms[j]);
			}
			free(copiedStation->platforms);
			free(copiedStation);
			return 0;
		}
		// Copy each train data except serial number
		copiedStation->platforms[i]->serialNumber = ts->platforms[i]->serialNumber;
		copiedStation->platforms[i]->numOfRailroadCars = ts->platforms[i]->numOfRailroadCars;
		copiedStation->platforms[i]->trainType = ts->platforms[i]->trainType;
		
		copiedStation->platforms[i]->trainValidityLicenseDate.day = ts->platforms[i]->trainValidityLicenseDate.day;
		copiedStation->platforms[i]->trainValidityLicenseDate.hour = ts->platforms[i]->trainValidityLicenseDate.hour;
		copiedStation->platforms[i]->trainValidityLicenseDate.minute = ts->platforms[i]->trainValidityLicenseDate.minute;
		copiedStation->platforms[i]->trainValidityLicenseDate.month = ts->platforms[i]->trainValidityLicenseDate.month;
		copiedStation->platforms[i]->trainValidityLicenseDate.type = ts->platforms[i]->trainValidityLicenseDate.type;
		copiedStation->platforms[i]->trainValidityLicenseDate.year = ts->platforms[i]->trainValidityLicenseDate.year;
		
		copiedStation->platforms[i]->type = ts->platforms[i]->type;

	}

	// Add the copied station to the destination city
	if (destinationCity->rank == 0 && destinationCity->numOfStations >= MAX_STATIONSALPHAPLUS)
	{
		printf("Destination city already has the maximum number of stations.\n");
		free(copiedStation->platforms); // Free memory allocated for the copied platforms
		free(copiedStation); // Free memory allocated for the copied station
		return 0;
	}

	else if (destinationCity->rank == 1 && destinationCity->numOfStations >= MAX_STATIONSALPHA) {
		printf("Destination city already has the maximum number of stations.\n");
		free(copiedStation->platforms); // Free memory allocated for the copied platforms
		free(copiedStation); // Free memory allocated for the copied station
		return 0;
	}
	else if (destinationCity->rank == 2 && destinationCity->numOfStations >= MAX_STATIONSBETAPLUS) {
		printf("Destination city already has the maximum number of stations.\n");
		free(copiedStation->platforms); // Free memory allocated for the copied platforms
		free(copiedStation); // Free memory allocated for the copied station
		return 0;
	}
	else if (destinationCity->rank == 3 && destinationCity->numOfStations >= MAX_STATIONSBETA) {
		printf("Destination city already has the maximum number of stations.\n");
		free(copiedStation->platforms); // Free memory allocated for the copied platforms
		free(copiedStation); // Free memory allocated for the copied station
		return 0;
	}

	destinationCity->trainStations[destinationCity->numOfStations] = copiedStation;
	destinationCity->numOfStations++;

	printf("Train station copied successfully.\n");

	return 1;
}



Train* selectTrain(TrainCompany* pTrainCompany)
{
	if (pTrainCompany->numOfTrains == 0)
	{
		printf("There is no active trains \n");
		return NULL;
	}

	boolean badSerialNumber = True;
	int trainSerialNumber;
	while (badSerialNumber)
	{
		printf("Please select an available train from this list: \n\n");
		generalArrayFunction(pTrainCompany->trainsArray, pTrainCompany->numOfTrains, sizeof(Train), generalPrintArray);// Prints all the trains
		printf("\nEnter the train's serial number here: \n");
		if (scanf("%d", &trainSerialNumber) != 1)
		{
			printf("Bad input.\n");
			return 0;
		}
		if (trainSerialNumber == -1)
			break;
		for (int i = 0; i < pTrainCompany->numOfTrains; i++)
		{
			if (pTrainCompany->trainsArray[i].serialNumber == trainSerialNumber)
			{
				return &pTrainCompany->trainsArray[i];
			}
		}
		printf("You've entered an invalid serial number, please try again (enter -1 to cancel).\n");// If a wrong serial number is entered
	}
	return NULL;
}

Driver* selectDriver(TrainCompany* pTrainCompany)
{
	if (pTrainCompany->numOfDrivers == 0)
	{
		printf("There is no active drivers \n");
		return NULL;

	}
	boolean badSerialNumber = True;
	int driverLicenseNumber;
	while (badSerialNumber)
	{
		printf("Please select an available driver from this list: \n");
		generalArrayFunction(pTrainCompany->driversArray, pTrainCompany->numOfDrivers, sizeof(Driver), generalPrintArray);// Prints all the drivers
		printf("\nEnter the driver's license number here: \n");
		if (scanf("%d", &driverLicenseNumber) != 1)
		{
			printf("Bad input.\n");
			return 0;
		}
		if (driverLicenseNumber == -1)
			break;
		for (int i = 0; i < pTrainCompany->numOfDrivers; i++)
		{
			if (pTrainCompany->driversArray[i].licenseNumber == driverLicenseNumber)
			{
				return &pTrainCompany->driversArray[i];
			}
		}
		printf("You've entered an invalid license number, please try again (enter -1 to cancel).\n");// If a wrong license number is entered
	}
	return NULL;
}

Inspector* selectInspector(TrainCompany* pTrainCompany)
{
	if (pTrainCompany->numOfInspectors == 0)
	{
		printf("There is no active inspectors \n");
		return NULL;

	}
	boolean badSerialNumber = True;
	int inspectorLicenseNumber;
	while (badSerialNumber)
	{
		printf("Please select an available inspector from this list: \n");
		generalArrayFunction(pTrainCompany->inspectorsArray, pTrainCompany->numOfInspectors, sizeof(Inspector), generalPrintArray);// Prints all the inspectors
		printf("\nEnter the inspector's license number here: \n");
		if (scanf("%d", &inspectorLicenseNumber) != 1)
		{
			printf("Bad input.\n");
			return 0;
		}
		if (inspectorLicenseNumber == -1)
			break;
		for (int i = 0; i < pTrainCompany->numOfInspectors; i++)
		{
			if (pTrainCompany->inspectorsArray[i].licenseNumber == inspectorLicenseNumber)
			{
				return &pTrainCompany->inspectorsArray[i];
			}
		}
		printf("You've entered an invalid license number, please try again (enter -1 to cancel).\n");// If a wrong license number is entered
	}
	return NULL;
}

City* selectACity(TrainCompany* pTrainCompany)
{
	if (pTrainCompany->numOfActiveCities == 0)
	{
		printf("There is no active cities \n");
		return NULL;

	}

	boolean badSerialNumber = True;
	int inspectorlicenseNumber = 0;
	char tempString[MAX_STR_LEN];
	while (badSerialNumber)
	{
		printf("Please select an available city from this list: \n\n");
		for (int i = 0; i < pTrainCompany->numOfActiveCities; i++)
		{
			printf("City: %s, city code: %s\n", pTrainCompany->citiesArray[i]->name, pTrainCompany->citiesArray[i]->cityCode);
		}
		printf("\nEnter the city code here: \n");
		myGets(tempString, MAX_STR_LEN);
		for (int i = 0; i < pTrainCompany->numOfActiveCities; i++)
		{
			if (strcmp(tempString, pTrainCompany->citiesArray[i]->cityCode) == 0)
			{
				return pTrainCompany->citiesArray[i];
			}
		}
		printf("You've entered an invalid city code, please try again.\n");// If a wrong city code is entered
	}
	return NULL;
}

TrainStation* selectAStation(City* pCity)
{
	if (pCity->numOfStations == 0)
	{
		printf("There is no active train stations \n");
		return NULL;
	}
	boolean badSerialNumber = True;
	int trainStationSerialNumber;
	while (badSerialNumber)
	{
		printf("Please select a train station from this list: \n\n");
		for (int i = 0; i < pCity->numOfStations; i++)
		{
			printTrainStation(pCity->trainStations[i]);
		}
		printf("\nEnter the train station's serial number here: \n");
		if (scanf("%d", &trainStationSerialNumber) != 1)
		{
			printf("Bad input.\n");
			return 0;
		}
		if (trainStationSerialNumber == -1)
			break;
		for (int i = 0; i < pCity->numOfStations; i++)
		{
			if (pCity->trainStations[i]->stationSerialNumber == trainStationSerialNumber)
			{
				return pCity->trainStations[i];
			}
		}
		printf("You've entered an invalid serial number, please try again (enter -1 to cancel).\n");// If a wrong serial number is entered
	}
	return NULL;
}

TrainStation* selectAStationFromList(LIST* list)
{
	boolean badSerialNumber = True;
	int trainStationSerialNumber;
	TrainStation* tempStation;
	while (badSerialNumber)
	{
		printf("\nPlease select after which train stop in the route you would like to add the chosen train station:\n");
		L_short_print(list);
		printf("Enter the train station's serial number here: \n");
		if (scanf("%d", &trainStationSerialNumber) != 1)
		{
			printf("Bad input.\n");
			return 0;
		}

		tempStation = L_find_by_serial_number(list->head.next, trainStationSerialNumber);
		if (tempStation == NULL)// If a wrong serial number is entered
		{
			printf("You've entered an invalid serial number, please try again (enter -1 to cancel).\n");
			continue;
		}
		
		return tempStation;// Returns the selected train station
	}
	return NULL;
}

Route* selectRoute(TrainCompany* pTrainCompany)
{
	if (pTrainCompany->numOfRoutes == 0)
	{
		printf("There are no routes in the company.\n");
		return NULL;
	}

	boolean badSerialNumber = True;
	int routeIdNumber;
	while (badSerialNumber)
	{
		printf("Please select an available route from this list: \n\n");
		printTrainRouteInCompany(pTrainCompany);
		printf("\nEnter the route's serial number here: \n");
		if (scanf("%d", &routeIdNumber) != 1)
		{
			printf("Bad input.\n");
			return 0;
		}
		if (routeIdNumber == -1)
			break;
		for (int i = 0; i < pTrainCompany->numOfRoutes; i++)
		{
			if (pTrainCompany->routesArray[i]->routeId == routeIdNumber)
			{
				return pTrainCompany->routesArray[i];
			}
		}
		printf("You've entered an invalid serial number, please try again (enter -1 to cancel).\n");// If a wrong serial number is entered
	}
	return NULL;
}

int updateRouteDriver(TrainCompany* pTrainCompany)
{
	Route* tempRoute = selectRoute(pTrainCompany);
	boolean flag = True;
	Driver* tempDriver = { 0 };
	while (flag)
	{
		tempDriver = selectDriver(pTrainCompany);// Select an available driver
		if (strcmp(TrainTypeStr[tempDriver->licenseType], TrainTypeStr[tempRoute->train->trainType]) != 0)// Checks if the driver license matches the train
		{
			printf("The driver's license of the driver you have selected does not match the train license of this route.\nPlease try again.\n ");
			continue;
		}
		else
			flag = False;
	}

	tempRoute->driver = tempDriver;// Update the driver

	printf("The routes driver has been updated to %s\n", tempRoute->driver->DriverName);

	return 1;
}

int updateRouteInspector(TrainCompany* pTrainCompany)
{
	Route* tempRoute = selectRoute(pTrainCompany);
	Inspector* tempInspector = selectInspector(pTrainCompany);// Select an available inspector
	tempRoute->inspector = tempInspector;// Update the inspector

	printf("The routes inspector has been changed to %s", tempInspector->InspectorName);

	return 1;
}

TrainStation* findTrainserial(TrainCompany* pTrainCompany, int serial)
{
	for (int i = 0; i < pTrainCompany->numOfActiveCities; i++)
		for (int j = 0; j < pTrainCompany->citiesArray[i]->numOfStations; j++)
			for (int k = 0; k < pTrainCompany->citiesArray[i]->trainStations[j]->numOfActiveTrains; k++)
				if (pTrainCompany->citiesArray[i]->trainStations[j]->platforms[k]->serialNumber = serial)
					return pTrainCompany->citiesArray[i]->trainStations[j];
		

	return NULL;
}


void printCityChoice(TrainCompany* pTrainCompany,char* cityCodeFind)
{
	int index = -1;
	index = findCityByCode(pTrainCompany,  cityCodeFind);

	if (index == -1)
	{
		printf("City with code %s not found.\n", cityCodeFind);
		return;
	}
	if (pTrainCompany->citiesArray[index]->numOfStations == 0)
	{
		printf("There is no train station in the city!\n");
		return;

	}
	int cityIndex = -1;
	int serialNumSearch = 0;
	printCityDetail(pTrainCompany->citiesArray[index]);

}

void printCompany(TrainCompany* pTrainCompany)
{
	printf("Company Information:\n");
	printf("Company Name: %s\n", pTrainCompany->companyName);
	printf("Number of Trains: %d\n", pTrainCompany->numOfTrains);
	for (int i = 0; i < pTrainCompany->numOfTrains; i++)
		printTrain(&pTrainCompany->trainsArray[i]);
	// print driver array
	printf("Number of Drivers: %d\n", pTrainCompany->numOfDrivers);
	for (int i = 0; i < pTrainCompany->numOfDrivers; i++)
		printDriver(&pTrainCompany->driversArray[i]);
	// print inspector array
	printf("Number of Inspectors: %d\n", pTrainCompany->numOfInspectors);
	for (int i = 0; i < pTrainCompany->numOfInspectors; i++)
		printInspector(&pTrainCompany->inspectorsArray[i]);
		// print the cities array
		for (int i = 0; i < pTrainCompany->numOfActiveCities; i++)
		{
			printCity(pTrainCompany->citiesArray[i]);
			for(int j=0;j<pTrainCompany->citiesArray[i]->numOfStations;j++)
			printTrainStationWithTrains(pTrainCompany->citiesArray[i]->trainStations[j]);
		}

	printf("Number of Routes: %d\n", pTrainCompany->numOfRoutes);
	//print the routes array
	printTrainRouteInCompany(pTrainCompany);
}




void printDriverArray(const TrainCompany* pTrainCompany)
{
	printf("there are %d drivers in the company:\n", pTrainCompany->numOfDrivers);
	for (int i = 0; i < pTrainCompany->numOfDrivers; i++)
	{
		printDriver(&pTrainCompany->driversArray[i]);
	}
}

void printInspectorArray(const TrainCompany* pTrainCompany)
{
	printf("there are %d Inspectors in the company:\n", pTrainCompany->numOfInspectors);
	for (int i = 0; i < pTrainCompany->numOfInspectors; i++)
	{
		printInspector(&pTrainCompany->inspectorsArray[i]);
	}
}

void printWorkerArray(const TrainCompany* pTrainCompany)
{
	printDriverArray(pTrainCompany);
	printInspectorArray(pTrainCompany);
}

void printTrainStationArray(const TrainCompany* ptrainCompany)
{
	if (ptrainCompany->numOfActiveCities == 0)
	{
	printf("There is no cities for train station\n");
	return;
	}

	for (int i = 0; i < ptrainCompany->numOfActiveCities; i++)
	{
		for(int j=0;j<ptrainCompany->citiesArray[i]->numOfStations;j++)
		printTrainStation(ptrainCompany->citiesArray[i]->trainStations[j]);
	}
}

void printCities(const TrainCompany* pTrainCompany)
{
	printf("[There are %d cities]\n", pTrainCompany->numOfActiveCities);
	for (int i = 0; i < pTrainCompany->numOfActiveCities; i++)
	{
		printCity(pTrainCompany->citiesArray[i]);
	}

}


void printExpectedPassengers(const TrainCompany* pTrainCompany)
{
	if (pTrainCompany->numOfActiveCities == 0)
	{
		printf("There are no cities in the company\n");
	}
	int totalPassengers = 0;
	int totalPassengersInCity = 0;
	double ticketPrice = 0;

	printf("Please enter the train ticket price here:\n");
	if (scanf("%lf", &ticketPrice) != 1)
	{
		printf("Bad input.\n");
		return ;
	}

	for (int i = 0; i < pTrainCompany->numOfActiveCities; i++)
	{

		for (int j = 0; j < pTrainCompany->citiesArray[i]->numOfStations; j++)
		{
			totalPassengersInCity += pTrainCompany->citiesArray[i]->trainStations[j]->expectedNumOfPassengers;
		}

		printf("There are %d expected passengers in city %s.\n", totalPassengersInCity, pTrainCompany->citiesArray[i]->name);
		totalPassengers += totalPassengersInCity;
		totalPassengersInCity = 0;
	}
	long double ExpectedCompanyIncome = totalPassengers * ticketPrice;
	printf("There is a total of %d expected passengers in the company.\n", totalPassengers);
	printf("The estimated income of the company is: %lf.\n", ExpectedCompanyIncome);
}

void chagneDriverLicense(TrainCompany* pTrainCompany, const int id)
{
	int choice = -1;
	int location;
	location = findWorker(pTrainCompany, id, &choice);

	if (choice != 0)
	{
		printf("driver is not found.\n");
		return;
	}

	changeLicense(&pTrainCompany->driversArray[location]);
}



int findCityByCode(TrainCompany* pTrainCompany, const char* cityCodeFind)
{
	for (int i = 0; i < pTrainCompany->numOfActiveCities; i++)
	{
		if (strcmp(pTrainCompany->citiesArray[i]->cityCode, cityCodeFind) == 0)
		{
			// Found the city with the specified code
			printf("City found with code %s:\n", cityCodeFind);

			return i; // Exit the function since we found the city
		}
	}
	// If the loop completes without finding the city
	return -1;
}


void updateCity(TrainCompany* pTrainCompany, char* cityCodeFind, const int choice)
{
	int index = -1;

	index = findCityByCode(pTrainCompany, cityCodeFind);

	if (index == -1)
	{

		printf("City with code %s not found.\n", cityCodeFind);
		return;
	}
	
	if (choice == 1)
		changeCityRank(pTrainCompany->citiesArray[index]);
	else
		removeCity(pTrainCompany, index);

}

void updateCityTrainStation(TrainCompany* pTrainCompany, char* cityCodeFind, int choice)
{
	int index = -1;
	index = findCityByCode(pTrainCompany, cityCodeFind);

	if (index == -1)
	{
		printf("City with code %s not found.\n", cityCodeFind);
		return;
	}
	if (choice == 0)
		if (addTrainStation(pTrainCompany->citiesArray[index]) == 0)
		{
			printf("Cannot add train station to city %s\n", cityCodeFind);
			return;
		}
		else
			printf("\nThe train station has been successfully added.\n");
	else if (choice == 1)
	if (removeTrainStation(pTrainCompany->citiesArray[index]) == 0)
	{
		printf("Cannot Remove train station to city %s\n", cityCodeFind);
		return;
	}
	else
		printf("\nThe train station has been remove successfully .\n");


}




void updateTrainStationInCity(TrainCompany* pTrainCompany, char* cityCodeFind)
{
	int index = -1;
	index = findCityByCode(pTrainCompany, cityCodeFind);

	if (index == -1)
	{
		printf("City with code %s not found.\n", cityCodeFind);
		return;
	}
	if (pTrainCompany->citiesArray[index]->numOfStations == 0)
	{
		printf("There is no train station in the city!\n");
		return;

	}
	int cityIndex = -1;
	int serialNumSearch = 0;
	printTrainStationInCity(pTrainCompany->citiesArray[index]);
	printf("Enter station serial number to add platforms\n");
	if (scanf("%d", &serialNumSearch) != 1)
	{
		printf("Bad input.\n");
		return;
	}
	
	
	cityIndex = findTrainStationBySerial(pTrainCompany->citiesArray[index], serialNumSearch);
	if (cityIndex == -1)
	{
		return;
	}
	

	updateNumOfPlatforms(pTrainCompany->citiesArray[index]->trainStations[cityIndex]);
	
	printf("train station %s have been updated to %d platforms\n", pTrainCompany->citiesArray[index]->trainStations[cityIndex]->stationName, pTrainCompany->citiesArray[index]->trainStations[cityIndex]->numOfPlatforms);

}



int selectTrainToAddToTrainStation(TrainCompany* pTrainCompany)
{
	Train* train = NULL;
	train = selectTrain(pTrainCompany);
	cleanbuffer();
	printTrain(train);

	char cTemp[CITYCODE + 1];
	char* pchar = cTemp;
	printCities(pTrainCompany);
	printf("choose the city to add train \n");
	getCityCode(pchar);

	int index = -1;
	index = findCityByCode(pTrainCompany, pchar);

	if (index == -1)
	{
		printf("City with code %s not found.\n", pchar);
		return 0;
	}
	if (pTrainCompany->citiesArray[index]->numOfStations == 0)
	{
		printf("There is no train station in the city!\n");
		return 0;
		
	}
	int cityIndex = -1;
	int serialNumSearch = 0;
	printTrainStationInCity(pTrainCompany->citiesArray[index]);
	printf("Enter station serial number to add train\n");
	if (scanf("%d", &serialNumSearch) != 1)
	{
		printf("Bad input.\n");
		return 0;
	}
	cityIndex = findTrainStationBySerial(pTrainCompany->citiesArray[index], serialNumSearch);
	if (cityIndex == -1)
	{
		return 0;
	}
	if (pTrainCompany->citiesArray[index]->trainStations[cityIndex]->trainStationType != train->trainType)
	{
		printf("the type of station and train are not the same\n");
		return 0;
	}

	if (pTrainCompany->citiesArray[index]->trainStations[cityIndex]->numOfActiveTrains >= pTrainCompany->citiesArray[index]->trainStations[cityIndex]->numOfPlatforms)
	{
		printf("there is no space in the platforms for trains\n");
		return 0;
	}
	if (searchTrainInTrainStation(pTrainCompany->citiesArray[index]->trainStations[cityIndex], train->serialNumber) == 0)
	{
		return 0;
	}

	
	if (pTrainCompany->citiesArray[index]->trainStations[cityIndex]->trainStationType == train->trainType)
	{
	
	pTrainCompany->citiesArray[index]->trainStations[cityIndex]->platforms[pTrainCompany->citiesArray[index]->trainStations[cityIndex]->numOfActiveTrains] = train;
	printf("train %d have been added to the train station\n", train->serialNumber);
	pTrainCompany->citiesArray[index]->trainStations[cityIndex]->numOfActiveTrains++;
	}
	else
	{
		printf("train %d and the train station %d are not the same type", train->serialNumber, pTrainCompany->citiesArray[index]->trainStations[cityIndex]->stationSerialNumber);
		printf("train is %s and trains station is %s\n", TrainTypeStr[train->trainType], TrainTypeStation[pTrainCompany->citiesArray[index]->trainStations[cityIndex]->stationSerialNumber]);
		free(train);
	}


	return 1;
}

int findTrainStationBySerial(const City* city, const int serialNum)
{
	for (int i = 0; i < city->numOfStations; i++)
	{
		if (city->trainStations[i]->stationSerialNumber==serialNum)
		{
			// Found the city with the specified code
			printf("tranStation found with serial number %d\n\n", serialNum);

			return i; // Exit the function since we found the city
		}
	}
	// If the loop completes without finding the city
	printf("tranStation with serial number %d not found\n\n", serialNum);
	return -1;
}


void removeCity(TrainCompany* pTrainCompany, const int location)
{
	if (location < 0 || location >= pTrainCompany->numOfActiveCities)
	{
		printf("Invalid location for removing city.\n");
		return;
	}

	// Free the city at the specified location
	freeCity(pTrainCompany->citiesArray[location]);

	// Move the remaining cities in the array to close the gap
	for (int i = location; i < pTrainCompany->numOfActiveCities - 1; i++)
	{
		pTrainCompany->citiesArray[i] = pTrainCompany->citiesArray[i + 1];
	}

	// Update the number of active cities
	pTrainCompany->numOfActiveCities--;

	// Reallocate memory to shrink the cities array
	City** tempCitiesArray = realloc(pTrainCompany->citiesArray, pTrainCompany->numOfActiveCities * sizeof(City*));
	if (tempCitiesArray == NULL)
	{
		printf("Error reallocating memory for cities array.\n");
		return;
	}

	// Update the cities array pointer
	pTrainCompany->citiesArray = tempCitiesArray;

	printf("City has been removed.\n");
}



void printTrains(const TrainCompany* pTrainCompany)
{
	printf("there are %d trains in the company:\n", pTrainCompany->numOfTrains);
	for (int i = 0; i < pTrainCompany->numOfTrains; i++)
	{
		printTrain(&pTrainCompany->trainsArray[i]);
	}

}

int findTrain(const TrainCompany* pTrainCompany, int serialNumber)
{

	for (int i = 0; i < pTrainCompany->numOfTrains; i++)
	{
		if (pTrainCompany->trainsArray[i].serialNumber == serialNumber)
		{
			printf("Train found with serial Number %d:\n", serialNumber);
			return i;

		}

	}
	return -1;
}

void updateTrain(TrainCompany* pTrainCompany, int serialNumber, int choice)
{
	int index = findTrain(pTrainCompany, serialNumber);

	if (index == -1)
	{
		printf("Train with serial Number %d can not be found \n", serialNumber);
		return;
	}
	if (choice == 1)
	{

		updateValidityLicense(&pTrainCompany->trainsArray[index]);
		printf("The license validity date have been updated to:\n");
		printTravelTime(&pTrainCompany->trainsArray[index].trainValidityLicenseDate);
	}
	else
		removeTrain(pTrainCompany, serialNumber, index);


}

int compareCityPassenger(const void* a, const void* b) {

	const City* cityA = *(const City**)a;
	const City* cityB = *(const City**)b;
	if (a == NULL || b == NULL) {
		// Handle the case where one or both pointers are null
		return 0;
	}

	int sumA = 0;
	for (int i = 0; i < cityA->numOfStations; i++) {
		sumA += cityA->trainStations[i]->expectedNumOfPassengers;
	}

	int sumB = 0;
	for (int i = 0; i < cityB->numOfStations; i++) {
		sumB += cityB->trainStations[i]->expectedNumOfPassengers; 
	}

	if (sumA < sumB) {
		return 1; // a comes before b
	}
	else if (sumA > sumB) {
		return -1;  // a comes after b
	}
	else {
		return 0;  // Both cities have equal total expected passengers
	}
}


void sortCitiesByPassengers(City** citiesArray, int numOfCities)
{

	qsort(citiesArray, numOfCities, sizeof(City*), compareCityPassenger);
}


int compareCityTrainQuantity(const void* a, const void* b) 
{
	const City* cityA = *(const City**)a;
	const City* cityB = *(const City**)b;
	if (a == NULL || b == NULL) {
		// Handle the case where one or both pointers are null
		return 0;
	}

	
	int sumTrainA = 0;
	for (int i = 0; i < cityA->numOfStations; i++) {
		sumTrainA += cityA->trainStations[i]->numOfActiveTrains;
	}

	int sumTrainB = 0;
	for (int i = 0; i < cityB->numOfStations; i++) {
		sumTrainB += cityB->trainStations[i]->numOfActiveTrains;
	}
	
	if (sumTrainA < sumTrainB) {
		return 1; // cityA comes before cityB
	}
	else if (sumTrainA > sumTrainB) {
		return -1;  // cityA comes after cityB
	}
	else {
		return 0;  // Both cities have equal total number of active trains
	}
}

void sortCitiesByTrains(City** citiesArray, int numOfCities) 
{
	qsort(citiesArray, numOfCities, sizeof(City*), compareCityTrainQuantity);
}


int checkIfRandomLicenseOk(TrainCompany* pTrainCompany, int licenseNum)
{
	srand((int)time(NULL)); // Seed the random number generator
	boolean updated = True;
	while (updated)
	{
		updated = False;
		// Check if the license number exists in the drivers array
		for (int i = 0; i < pTrainCompany->numOfDrivers; i++) {
			if (pTrainCompany->driversArray[i].licenseNumber == licenseNum) {
				licenseNum = rand() % 9999 + 1; // Generate a new random number
				updated = True;
				break;
			}
		}
		// If the license number was found among drivers, no need to check inspectors
		if (!updated) {
			// Check if the license number exists in the inspectors array
			for (int i = 0; i < pTrainCompany->numOfInspectors; i++) {
				if (pTrainCompany->inspectorsArray[i].licenseNumber == licenseNum) {
					licenseNum = rand() % 9999 + 1; // Generate a new random number
					updated = True;
					break;
				}
			}


		}
	}
	return licenseNum; // Original license number is OK
}




void freeDriverArray(TrainCompany* pTrainCompany)
{
	for (int i = 0; i < pTrainCompany->numOfDrivers; i++)
	{
		freeDriver(&pTrainCompany->driversArray[i]);
	}

	free(pTrainCompany->driversArray);

}

void freeInspectorArray(TrainCompany* pTrainCompany)
{
	for (int i = 0; i < pTrainCompany->numOfInspectors; i++)
	{
		freeInspector(&pTrainCompany->inspectorsArray[i]);
	}
	free(pTrainCompany->inspectorsArray);

}

//this free might not be needed
void freeTrains(TrainCompany* pTrainCompany)
{
	
	for (int i = 0; i < pTrainCompany->numOfTrains; i++)
	{
		freeTrain(&pTrainCompany->trainsArray[i]);
	}
	
	free(pTrainCompany->trainsArray);

}

void freeCities(TrainCompany* pTrainCompany)
{
	for (int i = 0; i < pTrainCompany->numOfActiveCities; i++)
	{
		freeCity(pTrainCompany->citiesArray[i]);
		free(pTrainCompany->citiesArray[i]);
	}


}

void freeTrainRoutes(TrainCompany* pTrainCompany)
{
	for (int i = 0; i < pTrainCompany->numOfRoutes; i++)
	{
		freeTrainRoute(pTrainCompany->routesArray[i]);
		free(pTrainCompany->routesArray[i]);
	}


}

void freeTrainStations(City* city)
{

	for (int i = 0; i < city->numOfStations; i++)
	{
		freeTrain(city->trainStations[i]->platforms[i]);
		free(city->trainStations[i]->stationName);
		free(city->trainStations[i]->locatedInCity);
	}

	free(city->trainStations);
}


void freeCompany(TrainCompany* pTrainCompany)
{
	if (pTrainCompany == NULL) {
		return;
	}
	// Free name:
	free(pTrainCompany->companyName);

	// Free trains array:
	free(pTrainCompany->trainsArray);

	// Free drivers array:
	freeDriverArray(pTrainCompany);

	// Free inspectors array:
	freeInspectorArray(pTrainCompany);

	// Free cities array:
	freeCities(pTrainCompany);

	// Free routes array:
	if(pTrainCompany->numOfRoutes!=0)
		for(int i=0;i<pTrainCompany->numOfRoutes;i++)
	freeTrainRoute(pTrainCompany->routesArray[i]);

}


void writeDriverToFileBNested(FILE* file, Driver* driver) {
	BYTE data[4] = { 0 };

	int index = 0;

	int nameLength = (int)strlen(driver->DriverName);

	data[0] = nameLength & 0xFF; // 8 bits

	// Extract the upper 6 bits of the license number and store them in data[1]
	data[1] = (driver->licenseNumber >> 8) & 0xFF; // 8bits

	// Extract the lower 8 bits of the license number and store them in data[2]
	data[2] = driver->licenseNumber & 0xFF; // 8 bits = total of 16 bits although need only 14

	// Combine the remaining bits (licenseType and type) and store them in data[2] and data[3]

	data[3] |= (driver->licenseType) & 0x07; // 3 bits

	data[3] |= (driver->type << 4) & 0xF0; // Remaining 4 bits from type

	// Check return value of fwrite
	if (fwrite(&data, sizeof(BYTE), 4, file) != 4) {
		printf("error writing");
		return;
	}

	BYTE* dataName = (BYTE*)malloc(sizeof(BYTE) * nameLength);
	if (dataName == NULL)
		return;

	// Pack the name into tmp
	for (int i = 0; i < nameLength; i++) {
		dataName[i] = (driver->DriverName[i] & 0xFF);

	}

	// Check return value of fwrite
	if (fwrite(dataName, sizeof(BYTE), nameLength, file) != nameLength) {
		free(dataName);
		return;
	}

	free(dataName);
}



int readDriverFromFileBNested(FILE* file, Driver* driver)
{
	BYTE data[4] = { 0 };

	// Read the first 4 bytes from the file
	if (fread(data, sizeof(BYTE), 4, file) != 4) {
		// Error reading from file
		return 0;
	}

	// Extract information from the first 4 bytes
	int nameLength = data[0] & 0xFF;

	// Combine the upper and lower bits of the license number
	driver->licenseNumber = ((data[1] & 0xFF) << 8) | (data[2] & 0xFF);

	// Extract the license type from the lower 3 bits of data[3]
	driver->licenseType = data[3] & 0x07;

	// Extract the type from the upper 4 bits of data[3]
	driver->type = (data[3] >> 4) & 0x0F;

	// Allocate memory for the driver name
	driver->DriverName = (char*)malloc((nameLength + 1) * sizeof(char));
	if (driver->DriverName == NULL) {
		return 0;
	}

	// Read the name bytes from the file
	for (int i = 0; i < nameLength; i++) {
		BYTE byte;
		if (fread(&byte, sizeof(BYTE), 1, file) != 1) {
			// Error reading name byte from file
			free(driver->DriverName); // Free allocated memory before returning
			return 0;
		}
		driver->DriverName[i] = (char)byte; // Cast the byte to char
	}
	driver->DriverName[nameLength] = '\0'; // Null-terminate the name string
	// Return success
	return 1;
}


int writeDriverToFileB(FILE* file, const Driver* driver)
{
	// Write driver name length and name
	int nameLength = (int)strlen(driver->DriverName);
	fwrite(&nameLength, sizeof(int), 1, file); // Write name length
	fwrite(driver->DriverName, sizeof(char), nameLength, file); // Write name characters

	// Write other members
	fwrite(&driver->licenseNumber, sizeof(int), 1, file);
	fwrite(&driver->licenseType, sizeof(int), 1, file); 
	fwrite(&driver->type, sizeof(int), 1, file); 

	return 1;
}

int readDriverFromFileB(FILE* file, Driver* driver) {
	// Read driver name length and allocate memory
	int nameLength;
	fread(&nameLength, sizeof(int), 1, file);
	driver->DriverName = (char*)malloc(nameLength + 1); // Add 1 for null terminator
	if (driver->DriverName == NULL)
	{
		return 0;
	}

	fread(driver->DriverName, sizeof(char), nameLength, file); // Read name characters
	driver->DriverName[nameLength] = '\0'; // Null-terminate the string

	// Read other members
	fread(&driver->licenseNumber, sizeof(int), 1, file);
	fread(&driver->licenseType, sizeof(int), 1, file);
	fread(&driver->type, sizeof(int), 1, file);
	return 1;
}

int writeInspectorToFileB(FILE* file, const Inspector* inspector)
{
	// Write driver name length and name
	int nameLength = (int)strlen(inspector->InspectorName);
	fwrite(&nameLength, sizeof(int), 1, file); // Write name length
	fwrite(inspector->InspectorName, sizeof(char), nameLength, file); // Write name characters

	// Write other members
	fwrite(&inspector->licenseNumber, sizeof(int), 1, file);
	fwrite(&inspector->type, sizeof(int), 1, file);

	return 1;

}

int readInspectorFromFileB(FILE* file, Inspector* inspector)
{
	// Read driver name length and allocate memory
	int nameLength;
	fread(&nameLength, sizeof(int), 1, file);
	inspector->InspectorName = (char*)malloc(nameLength + 1); // Add 1 for null terminator
	if (inspector->InspectorName == NULL)
	{
		return 0;
	}
	fread(inspector->InspectorName, sizeof(char), nameLength, file); // Read name characters
	inspector->InspectorName[nameLength] = '\0'; // Null-terminate the string

	// Read other members
	fread(&inspector->licenseNumber, sizeof(int), 1, file);
	fread(&inspector->type, sizeof(int), 1, file);

	return 1;
}


int writeTrainToFileB(FILE* file, const Train* train) {
	if (fwrite(&train->serialNumber, sizeof(int), 1, file) != 1) {
		fclose(file);
		return 0;
	}

	if (fwrite(&train->numOfRailroadCars, sizeof(int), 1, file) != 1) {
		fclose(file);
		return 0;
	}

	if (fwrite(&train->trainType, sizeof(int), 1, file) != 1) {
		fclose(file);
		return 0;
	}

	if (fwrite(&train->trainValidityLicenseDate.year, sizeof(int), 1, file) != 1) {
		fclose(file);
		return 0;
	}

	if (fwrite(&train->trainValidityLicenseDate.month, sizeof(int), 1, file) != 1) {
		fclose(file);
		return 0;
	}

	if (fwrite(&train->trainValidityLicenseDate.day, sizeof(int), 1, file) != 1) {
		fclose(file);
		return 0;
	}

	if (fwrite(&train->trainValidityLicenseDate.hour, sizeof(int), 1, file) != 1) {
		fclose(file);
		return 0;
	}

	if (fwrite(&train->trainValidityLicenseDate.minute, sizeof(int), 1, file) != 1) {
		fclose(file);
		return 0;
	}

	if (fwrite(&train->type, sizeof(int), 1, file) != 1) {
		fclose(file);
		return 0;
	}

	return 1;
}

int readTrainFromFileB(FILE* file,  Train* train) {
	if (fread(&train->serialNumber, sizeof(int), 1, file) != 1) {
		fclose(file);
		return 0;
	}

	if (fread(&train->numOfRailroadCars, sizeof(int), 1, file) != 1) {
		fclose(file);
		return 0;
	}


	if (fread(&train->trainType, sizeof(int), 1, file) != 1) {
		fclose(file);
		return 0;
	}

	if (fread(&train->trainValidityLicenseDate.year, sizeof(int), 1, file) != 1) {
		fclose(file);
		return 0;
	}

	if (fread(&train->trainValidityLicenseDate.month, sizeof(int), 1, file) != 1) {
		fclose(file);
		return 0;
	}

	if (fread(&train->trainValidityLicenseDate.day, sizeof(int), 1, file) != 1) {
		fclose(file);
		return 0;
	}

	if (fread(&train->trainValidityLicenseDate.hour, sizeof(int), 1, file) != 1) {
		fclose(file);
		return 0;
	}


	if (fread(&train->trainValidityLicenseDate.minute, sizeof(int), 1, file) != 1) {
		fclose(file);
		return 0;
	}
	train->trainValidityLicenseDate.type = eTime;



	if (fread(&train->type, sizeof(int), 1, file) != 1) {
		fclose(file);
		return 0;
	}

	return 1;
}

int writeCityToFileB(FILE* file, const City* city)
{
	int cityLenTemp = (int)strlen(city->name);

	fwrite(&cityLenTemp, sizeof(int), 1, file);

	fwrite(city->name, sizeof(char), cityLenTemp, file);

	fwrite(city->cityCode, sizeof(char), CITYCODE, file);
	fwrite(&city->rank, sizeof(int), 1, file);
	fwrite(&city->numOfStations, sizeof(int), 1, file);

	for (int j = 0; j < city->numOfStations; j++)
	{
		int stationNameLen = (int)strlen(city->trainStations[j]->stationName);

		if (fwrite(&stationNameLen, sizeof(int), 1, file) != 1) { fclose(file); return 0; }

		if (fwrite(city->trainStations[j]->stationName, sizeof(char), stationNameLen, file) != stationNameLen) { fclose(file); return 0; }


		if (fwrite(&city->trainStations[j]->stationSerialNumber, sizeof(int), 1, file) != 1) { fclose(file); return 0; }

		if (fwrite(&city->trainStations[j]->trainStationType, sizeof(int), 1, file) != 1) { fclose(file); return 0; }

		if (fwrite(&city->trainStations[j]->numOfPlatforms, sizeof(int), 1, file) != 1) { fclose(file); return 0; }

		int cityLocatedTemp = (int)strlen(city->trainStations[j]->locatedInCity);

		if (fwrite(&cityLocatedTemp, sizeof(int), 1, file) != 1) { fclose(file); return 0; }

		if (fwrite(city->trainStations[j]->locatedInCity, sizeof(char), cityLocatedTemp, file) != cityLocatedTemp) { fclose(file); return 0; }

		if (fwrite(&city->trainStations[j]->expectedNumOfPassengers, sizeof(int), 1, file) != 1) { fclose(file); return 0; }

		if (fwrite(&city->trainStations[j]->numOfActiveTrains, sizeof(int), 1, file) != 1) { fclose(file); return 0; }


		for (int k = 0; k < city->trainStations[j]->numOfActiveTrains; k++)
		{

			if (writeTrainToFileB(file, city->trainStations[j]->platforms[k]) == 0)
			{
				fclose(file);
				return 0;
			}

		}



		if (fwrite(&city->trainStations[j]->type, sizeof(int), 1, file) != 1) { fclose(file); return 0; }

	}


	if (fwrite(&city->type, sizeof(int), 1, file) != 1) { fclose(file); return 0; }


	return 1;
}

int readCityFromFileB(FILE* file, City* city) {
	int cityLenTemp;

	// Read the length of the city name
	if (fread(&cityLenTemp, sizeof(int), 1, file) != 1) {
		return 0; // Error reading city name length
	}

	// Allocate memory for the city name
	city->name = (char*)malloc((cityLenTemp + 1) * sizeof(char));
	if (city->name == NULL) {
		return 0; // Memory allocation failed
	}

	// Read the city name
	if (fread(city->name, sizeof(char), cityLenTemp, file) != cityLenTemp) {
		free(city->name);
		return 0; // Error reading city name
	}
	city->name[cityLenTemp] = '\0'; // Null-terminate the city name

	// Read the city code
	if (fread(city->cityCode, sizeof(char), CITYCODE, file) != CITYCODE) {
		free(city->name);
		return 0; // Error reading city code
	}
	city->cityCode[CITYCODE] = '\0';

	// Read the city rank
	if (fread(&city->rank, sizeof(int), 1, file) != 1) {
		free(city->name);
		return 0; // Error reading city rank
	}

	// Read the number of stations
	if (fread(&city->numOfStations, sizeof(int), 1, file) != 1) {
		free(city->name);
		return 0; // Error reading number of stations
	}

	// Allocate memory for train stations
	city->trainStations = (TrainStation**)malloc(city->numOfStations * sizeof(TrainStation*));
	if (city->trainStations == NULL) {
		free(city->name);
		return 0; // Memory allocation failed
	}

	// Read train stations
	for (int j = 0; j < city->numOfStations; j++) {
		city->trainStations[j] = (TrainStation*)malloc(sizeof(TrainStation));
		if (city->trainStations[j] == NULL) {
			free(city->name);
			freeTrainStations(city); // Free previously allocated train stations
			return 0; // Memory allocation failed
		}

		int stationNameLen = 0;
		if (fread(&stationNameLen, sizeof(int), 1, file) != 1) {
			fclose(file);
			return 0;
		}
		city->trainStations[j]->stationName = malloc(sizeof(char) * (stationNameLen + 1));
		if (fread(city->trainStations[j]->stationName, sizeof(char), stationNameLen, file) != stationNameLen) {
			fclose(file);
			return 0;
		}
		city->trainStations[j]->stationName[stationNameLen] = '\0';
		if (fread(&city->trainStations[j]->stationSerialNumber, sizeof(int), 1, file) != 1) {
			fclose(file);
			return 0;
		}

		if (fread(&city->trainStations[j]->trainStationType, sizeof(int), 1, file) != 1) {
			fclose(file);
			return 0;
		}
		if (fread(&city->trainStations[j]->numOfPlatforms, sizeof(int), 1, file) != 1) {
			fclose(file);
			return 0;
		}
		int locatedInCityLen = 0;
		if (fread(&locatedInCityLen, sizeof(int), 1, file) != 1) {
			fclose(file);
			return 0;
		}
		city->trainStations[j]->locatedInCity = malloc(sizeof(char) * (locatedInCityLen + 1));
		if (fread(city->trainStations[j]->locatedInCity, sizeof(char), locatedInCityLen, file) != locatedInCityLen) {
			fclose(file);
			return 0;
		}
		city->trainStations[j]->locatedInCity[locatedInCityLen] = '\0';
		if (fread(&city->trainStations[j]->expectedNumOfPassengers, sizeof(int), 1, file) != 1) {
			fclose(file);
			return 0;
		}

		if (fread(&city->trainStations[j]->numOfActiveTrains, sizeof(int), 1, file) != 1) {
			fclose(file);
			return 0;
		}

		city->trainStations[j]->platforms = (Train**)malloc(city->trainStations[j]->numOfPlatforms * sizeof(Train*));
		if (city->trainStations[j]->platforms == NULL)
		{
			fclose(file);
			return 0;
		}


		for (int k = 0; k < city->trainStations[j]->numOfActiveTrains; k++)
		{
			city->trainStations[j]->platforms[k] = (Train*)malloc(sizeof(Train));
			if (city->trainStations[j]->platforms[k] == NULL)
			{
				fclose(file);
				return 0;
			}

			if (readTrainFromFileB(file, city->trainStations[j]->platforms[k]) == 0)
			{
				fclose(file);
				return 0;
			}

		}
		if (fread(&city->trainStations[j]->type, sizeof(int), 1, file) != 1) {
			fclose(file);
			return 0;
		}

	}

	// Read the city type
	if (fread(&city->type, sizeof(int), 1, file) != 1) {
		free(city->name);
		freeTrainStations(city);
		return 0; // Error reading city type
	}

	return 1; // Successfully read city data
}



int writeListToFileB(FILE* file, const LIST* list)
{
	if (list == NULL) {
		return 0; // Error: NULL pointer
	}

	NODE* current = list->head.next; // Start from the first node

	// Traverse the list and write each node's data
	while (current != NULL) {
		// Write the data of the current node to the file
		writeStationToB(file, (TrainStation*)current->key);
		// Move to the next node
		current = current->next;
	}

	return 1; // Success
}

int writeStationToB(FILE* file, const TrainStation* station)
{
	int stationNameLen = (int)strlen(station->stationName);

	if (fwrite(&stationNameLen, sizeof(int), 1, file) != 1) { fclose(file); return 0; }

	if (fwrite(station->stationName, sizeof(char), stationNameLen, file) != stationNameLen) { fclose(file); return 0; }

	if (fwrite(&station->stationSerialNumber, sizeof(int), 1, file) != 1) { fclose(file); return 0; }

	if (fwrite(&station->trainStationType, sizeof(int), 1, file) != 1) { fclose(file); return 0; }

	if (fwrite(&station->numOfPlatforms, sizeof(int), 1, file) != 1) { fclose(file); return 0; }

	int cityLocatedTemp = (int)strlen(station->locatedInCity);

	if (fwrite(&cityLocatedTemp, sizeof(int), 1, file) != 1) { fclose(file); return 0; }

	if (fwrite(station->locatedInCity, sizeof(char), cityLocatedTemp, file) != cityLocatedTemp) { fclose(file); return 0; }

	if (fwrite(&station->expectedNumOfPassengers, sizeof(int), 1, file) != 1) { fclose(file); return 0; }

	if (fwrite(&station->numOfActiveTrains, sizeof(int), 1, file) != 1) { fclose(file); return 0; }


	for (int k = 0; k < station->numOfActiveTrains; k++)
	{

		if (writeTrainToFileB(file, station->platforms[k]) == 0)
		{
			fclose(file);
			return 0;
		}

	}


	if (fwrite(&station->type, sizeof(int), 1, file) != 1) { fclose(file); return 0; }
	return 1;
}

int readStationToB(FILE* file, TrainStation* station)
{
	int stationNameLen = 0;

	if (fread(&stationNameLen, sizeof(int), 1, file) != 1) { fclose(file); return 0; }

	// Allocate memory for station name based on the length read
	station->stationName = malloc(sizeof(char) * (stationNameLen + 1));
	if (station->stationName == NULL) { fclose(file); return 0; }

	if (fread(station->stationName, sizeof(char), stationNameLen, file) != stationNameLen) { fclose(file); return 0; }
	station->stationName[stationNameLen] = '\0'; // Null-terminate the string

	if (fread(&station->stationSerialNumber, sizeof(int), 1, file) != 1) { fclose(file); return 0; }

	if (fread(&station->trainStationType, sizeof(int), 1, file) != 1) { fclose(file); return 0; }

	if (fread(&station->numOfPlatforms, sizeof(int), 1, file) != 1) { fclose(file); return 0; }

	int cityLocatedTemp = 0;

	if (fread(&cityLocatedTemp, sizeof(int), 1, file) != 1) { fclose(file); return 0; }

	station->locatedInCity = malloc(sizeof(char) * (cityLocatedTemp + 1));
	if (station->locatedInCity == NULL)
		return 0;

	if (fread(station->locatedInCity, sizeof(char), cityLocatedTemp, file) != cityLocatedTemp) { fclose(file); return 0; }

	station->locatedInCity[cityLocatedTemp] = '\0'; // Null-terminate the string

	if (fread(&station->expectedNumOfPassengers, sizeof(int), 1, file) != 1) { fclose(file); return 0; }

	if (fread(&station->numOfActiveTrains, sizeof(int), 1, file) != 1) { fclose(file); return 0; }


	for (int k = 0; k < station->numOfActiveTrains; k++)
	{
		if (readTrainFromFileB(file, station->platforms[k]) == 0)
		{
			fclose(file);
			return 0;
		}

	}


	if (fread(&station->type, sizeof(int), 1, file) != 1) { fclose(file); return 0; }
	return 1;
}


int readListFromFileB(FILE* file, LIST* list)
{
	if (list == NULL) {
		return 0; // Error: NULL pointer
	}

	// Read data from the file into the new node
	TrainStation* tempStation = malloc(sizeof(TrainStation));
	if (tempStation == NULL)
	{
		return 0;
	}


	if (readStationToB(file, tempStation) == 0)
	{
		// Insertion failed, free allocated memory
		freeTrainStation(tempStation);
		return 0; 	
	}

	if (!L_insert(&list->head, tempStation)) {
		// Insertion failed, free allocated memory
		freeTrainStation(tempStation);
		return 0;
	}


	return 1; // Success
}






int writeRouteToFileB(FILE* file, const Route* route)
{

	if (fwrite(&route->routeId, sizeof(int), 1, file) != 1) {
		return 0;
	}


	writeTrainToFileB(file, route->train);
	writeDriverToFileBNested(file, route->driver);
	writeInspectorToFileB(file, route->inspector);
	if (fwrite(&route->numOfStation, sizeof(int), 1, file) != 1) {
		return 0;
	}
	
	writeListToFileB(file, route->trainStationsList);

	writeTimeToFileB(file, route->departureTime);

	if (fwrite(&route->type, sizeof(structType), 1, file) != 1) {
		return 0;
	}

	return 1;
}




int readRouteFromB(FILE* file, Route* route)
{

	// Read each member of the Route structure from the file
	if (fread(&(route->routeId), sizeof(int), 1, file) != 1) {
		return 0; // Error: Failed to read routeId
	}

	// Read the train data
	route->train = (Train*)malloc(sizeof(Train));
	if (route->train == NULL) {
		return 0; // Error: Failed to allocate memory for train
	}
	if (!readTrainFromFileB(file, route->train)) {
		free(route->train);
		return 0; // Error: Failed to read train data
	}

	// Read the driver data
	route->driver = (Driver*)malloc(sizeof(Driver));
	if (route->driver == NULL) {
		free(route->train);
		return 0; // Error: Failed to allocate memory for driver
	}
	if (!readDriverFromFileBNested(file, route->driver)) {
		free(route->train);
		free(route->driver);
		return 0; // Error: Failed to read driver data
	}

	// Read the inspector data
	route->inspector = (Inspector*)malloc(sizeof(Inspector));
	if (route->inspector == NULL) {
		free(route->train);
		free(route->driver);
		return 0; // Error: Failed to allocate memory for inspector
	}
	if (!readInspectorFromFileB(file, route->inspector)) {
		free(route->train);
		free(route->driver);
		free(route->inspector);
		return 0; // Error: Failed to read inspector data
	}

	// Read the numOfStation
	if (fread(&(route->numOfStation), sizeof(int), 1, file) != 1) {
		free(route->train);
		free(route->driver);
		free(route->inspector);
		free(route->trainStationsList);
		return 0; // Error: Failed to read numOfStation
	}

	// Read the trainStationsList data
	route->trainStationsList = (LIST*)malloc(sizeof(LIST));
	if (route->trainStationsList == NULL) {
		free(route->train);
		free(route->driver);
		free(route->inspector);
		return 0; // Error: Failed to allocate memory for trainStationsList
	}

	L_init(route->trainStationsList);
	for (int i = 0; i < route->numOfStation; i++)
	{

		if (!readListFromFileB(file, route->trainStationsList)) {
			free(route->train);
			free(route->driver);
			free(route->inspector);
			free(route->trainStationsList);
			return 0; // Error: Failed to read trainStationsList data
		}

	}


	// Read the departureTime data
	route->departureTime = (Time*)malloc(sizeof(Time));
	if (route->departureTime == NULL) {
		free(route->train);
		free(route->driver);
		free(route->inspector);
		free(route->trainStationsList);
		return 0; // Error: Failed to allocate memory for departureTime
	}


	if (readTimeToFileB(file,route->departureTime) ==0) {
		free(route->train);
		free(route->driver);
		free(route->inspector);
		free(route->trainStationsList);
		free(route->departureTime);
		return 0; // Error: Failed to read departureTime data
	}

	// Read the type
	if (fread(&(route->type), sizeof(structType), 1, file) != 1) {
		free(route->train);
		free(route->driver);
		free(route->inspector);
		free(route->trainStationsList);
		free(route->departureTime);
		return 0; // Error: Failed to read type
	}

	return 1; // Success
}

int writeTimeToFileB(FILE* file, const Time* time) {

	if (fwrite(&time->year, sizeof(int), 1, file) != 1) {
		return 0;
	}
	if (fwrite(&time->month, sizeof(int), 1, file) != 1) {
		return 0;
	}
	if (fwrite(&time->day, sizeof(int), 1, file) != 1) {
		return 0;
	}
	if (fwrite(&time->hour, sizeof(int), 1, file) != 1) {
		return 0;
	}
	if (fwrite(&time->minute, sizeof(int), 1, file) != 1) {
		return 0;
	}
	if (fwrite(&time->type, sizeof(structType), 1, file) != 1) {
		return 0;
	}
	return 1; // Successfully wrote Time data
}

int readTimeToFileB(FILE* file, Time* time) {

	if (fread(&time->year, sizeof(int), 1, file) != 1) {
		return 0;
	}
	if (fread(&time->month, sizeof(int), 1, file) != 1) {
		return 0;
	}
	if (fread(&time->day, sizeof(int), 1, file) != 1) {
		return 0;
	}
	if (fread(&time->hour, sizeof(int), 1, file) != 1) {
		return 0;
	}
	if (fread(&time->minute, sizeof(int), 1, file) != 1) {
		return 0;
	}
	if (fread(&time->type, sizeof(structType), 1, file) != 1) {
		return 0;
	}
	return 1; // Successfully wrote Time data
}




void writeDriverT(FILE* file, const Driver* driver)
{
	int driverLen = 0;
	driverLen = (int)strlen(driver->DriverName);
	fprintf(file, "%d\n", driverLen);
	fprintf(file, "%s\n", driver->DriverName);
	fprintf(file, "%d\n", driver->licenseNumber);
	fprintf(file, "%d\n", driver->licenseType);
	fprintf(file, "%d\n", driver->type);

}

int readDriverT(FILE* file, Driver* driver)
{
	int driverNameLen = 0; // Added semicolon here

	if (fscanf(file, "%d\n", &driverNameLen) != 1)
		return 0;

	// Allocate memory for driver name

	driver->DriverName = malloc(sizeof(char) * (driverNameLen + 1)); // +1 for null terminator

	// Check if memory allocation succeeds
	if (driver->DriverName == NULL)
		return 0;

	// Read driver name as string
	if (fscanf(file, "%s\n", driver->DriverName) != 1) {
		free(driver->DriverName); // Free memory if reading fails
		return 0;
	}

	if (fscanf(file, "%d\n", &driver->licenseNumber) != 1) {
		free(driver->DriverName); // Free memory if reading fails
		return 0;
	}

	if (fscanf(file, "%d\n", &driver->licenseType) != 1) {
		free(driver->DriverName); // Free memory if reading fails
		return 0;
	}

	if (fscanf(file, "%d\n", &driver->type) != 1) {
		free(driver->DriverName); // Free memory if reading fails
		return 0;
	}

	return 1;
}

void writeInspectorT(FILE* file, const Inspector* inspector)
{
	int inspectorLen = 0;
	inspectorLen = (int)strlen(inspector->InspectorName);
	fprintf(file, "%d\n", inspectorLen);
	fprintf(file, "%s\n", inspector->InspectorName);
	fprintf(file, "%d\n", inspector->licenseNumber);
	fprintf(file, "%d\n", inspector->type);

}

int readInspectorT(FILE* file, Inspector* inspector) {
	int inspectorLen = 0; // Added semicolon here

	if (fscanf(file, "%d\n", &inspectorLen) != 1)
		return 0;

	// Allocate memory for driver name

	inspector->InspectorName = malloc(sizeof(char) * (inspectorLen + 1)); // +1 for null terminator

	// Check if memory allocation succeeds
	if (inspector->InspectorName == NULL)
		return 0;

	// Read driver name as string
	if (fscanf(file, "%s\n", inspector->InspectorName) != 1) {
		free(inspector->InspectorName); // Free memory if reading fails
		return 0;
	}

	if (fscanf(file, "%d\n", &inspector->licenseNumber) != 1) {
		free(inspector->InspectorName); // Free memory if reading fails
		return 0;
	}

	if (fscanf(file, "%d\n", &inspector->type) != 1) {
		free(inspector->InspectorName); // Free memory if reading fails
		return 0;
	}


	return 1;
}

void writeTrainToT(FILE* file, const Train* train)
{

	fprintf(file, "%d\n", train->serialNumber);
	fprintf(file, "%d\n", train->trainType);
	fprintf(file, "%d\n", train->numOfRailroadCars);

	fprintf(file, "%d\n%d\n%d\n%d\n%d\n%d\n",
		train->trainValidityLicenseDate.year,
		train->trainValidityLicenseDate.month,
		train->trainValidityLicenseDate.day,
		train->trainValidityLicenseDate.hour,
		train->trainValidityLicenseDate.minute,
		train->trainValidityLicenseDate.type);

	fprintf(file, "%d\n", train->type);
}

int readTrainT(FILE* file, Train* train)
{

	if (fscanf(file, "%d\n", &train->serialNumber) != 1)
		return 0;

	if (fscanf(file, "%d\n", &train->trainType) != 1)
		return 0;

	if (fscanf(file, "%d\n", &train->numOfRailroadCars) != 1)
		return 0;

	if (fscanf(file, "%d\n%d\n%d\n%d\n%d\n%d\n",
		&train->trainValidityLicenseDate.year,
		&train->trainValidityLicenseDate.month,
		&train->trainValidityLicenseDate.day,
		&train->trainValidityLicenseDate.hour,
		&train->trainValidityLicenseDate.minute,
		&train->trainValidityLicenseDate.type) != 6)
		return 0;

	if (fscanf(file, "%d\n", &train->type) != 1)
		return 0;

	return 1;
}

void writeStationToT(FILE* file, const City* city)
{
	for (int i = 0; i < city->numOfStations; i++)
	{
		int tempStaionNameLen = 0;
		tempStaionNameLen = (int)strlen(city->trainStations[i]->stationName);
		fprintf(file, "%d\n", tempStaionNameLen);
		fprintf(file, "\"%s\"\n", city->trainStations[i]->stationName);
		fprintf(file, "%d\n", city->trainStations[i]->stationSerialNumber);
		fprintf(file, "%d\n", city->trainStations[i]->trainStationType);
		fprintf(file, "%d\n", city->trainStations[i]->numOfPlatforms);
		tempStaionNameLen = (int)strlen(city->trainStations[i]->locatedInCity);
		fprintf(file, "%d\n", tempStaionNameLen);
		fprintf(file, "\"%s\"\n", city->trainStations[i]->locatedInCity);
		fprintf(file, "%d\n", city->trainStations[i]->expectedNumOfPassengers);
		fprintf(file, "%d\n", city->trainStations[i]->numOfActiveTrains);


		for (int j = 0; j < city->trainStations[i]->numOfActiveTrains; j++)
		{
			writeTrainToT(file, city->trainStations[i]->platforms[j]);
		}

		fprintf(file, "%d\n", city->trainStations[i]->type);
	}
}



void writeCityToT(FILE* file, const City* city)
{
	int cityNameLen = 0;
	cityNameLen = (int)strlen(city->name);
	fprintf(file, "%d\n", cityNameLen);
	fprintf(file, "\"%s\"\n", city->name);
	fprintf(file, "%s\n", city->cityCode);
	fprintf(file, "%d\n", city->rank);
	fprintf(file, "%d\n", city->numOfStations);
	//write station
	for (int i = 0; i < city->numOfStations; i++)
	{
		int tempStaionNameLen = 0;
		tempStaionNameLen = (int)strlen(city->trainStations[i]->stationName);
		fprintf(file, "%d\n", tempStaionNameLen);
		fprintf(file, "\"%s\"\n", city->trainStations[i]->stationName);
		fprintf(file, "%d\n", city->trainStations[i]->stationSerialNumber);
		fprintf(file, "%d\n", city->trainStations[i]->trainStationType);
		fprintf(file, "%d\n", city->trainStations[i]->numOfPlatforms);
		tempStaionNameLen = (int)strlen(city->trainStations[i]->locatedInCity);
		fprintf(file, "%d\n", tempStaionNameLen);
		fprintf(file, "\"%s\"\n", city->trainStations[i]->locatedInCity);
		fprintf(file, "%d\n", city->trainStations[i]->expectedNumOfPassengers);
		fprintf(file, "%d\n", city->trainStations[i]->numOfActiveTrains);


		for (int j = 0; j < city->trainStations[i]->numOfActiveTrains; j++)
		{
			writeTrainToT(file, city->trainStations[i]->platforms[j]);
		}

		fprintf(file, "%d\n", city->trainStations[i]->type);

	}

	fprintf(file, "%d\n", city->type);

}

int readCityT(FILE* file, City* city)
{
	int cityNameLen = 0;
	if (fscanf(file, "%d\n", &cityNameLen) != 1)
		return 0;
	city->name = malloc(sizeof(char) * (cityNameLen + 1));
	if (city->name == NULL)
		return 0;
	if (fscanf(file, "\"%[^\"]\"\n", city->name) != 1)
		return 0;
	city->name[cityNameLen] = '\0';

	if (fscanf(file, "%s\n", city->cityCode) != 1)
		return 0;
	city->cityCode[CITYCODE] = '\0';

	if (fscanf(file, "%d\n", &city->rank) != 1)
		return 0;

	if (fscanf(file, "%d\n", &city->numOfStations) != 1)
		return 0;

	city->trainStations = malloc(sizeof(TrainStation*) * city->numOfStations);
	if (city->trainStations == NULL)
		return 0;

	for (int i = 0; i < city->numOfStations; i++)
	{
		city->trainStations[i] = malloc(sizeof(TrainStation));
		if (city->trainStations[i] == NULL)
			return 0;

		int tempStaionNameLen = 0;
		if (fscanf(file, "%d\n", &tempStaionNameLen) != 1)
			return 0;
		city->trainStations[i]->stationName = malloc(sizeof(char) * (tempStaionNameLen + 1));
		if (city->trainStations[i]->stationName == NULL)
			return 0;

		if (fscanf(file, "\"%[^\"]\"\n", city->trainStations[i]->stationName) != 1)
			return 0;
		city->trainStations[i]->stationName[tempStaionNameLen] = '\0';

		if (fscanf(file, "%d\n", &city->trainStations[i]->stationSerialNumber) != 1)
			return 0;
		if (fscanf(file, "%d\n", &city->trainStations[i]->trainStationType) != 1)
			return 0;
		if (fscanf(file, "%d\n", &city->trainStations[i]->numOfPlatforms) != 1)
			return 0;
		if (fscanf(file, "%d\n", &tempStaionNameLen) != 1)
			return 0;
		city->trainStations[i]->locatedInCity = malloc(sizeof(char) * (tempStaionNameLen + 1));
		if (city->trainStations[i]->locatedInCity == NULL)
			return 0;

		if (fscanf(file, "\"%[^\"]\"\n", city->trainStations[i]->locatedInCity) != 1)
			return 0;

		city->trainStations[i]->locatedInCity[tempStaionNameLen] = '\0';

		if (fscanf(file, "%d\n", &city->trainStations[i]->expectedNumOfPassengers) != 1)
			return 0;

		if (fscanf(file, "%d\n", &city->trainStations[i]->numOfActiveTrains) != 1)
			return 0;

		city->trainStations[i]->platforms = (Train**)malloc(sizeof(Train*) * city->trainStations[i]->numOfPlatforms);
		if (city->trainStations[i]->platforms == NULL)
			return 0;

		for (int j = 0; j < city->trainStations[i]->numOfActiveTrains; j++)
		{
			city->trainStations[i]->platforms[j] = (Train*)malloc(sizeof(Train));
			if (city->trainStations[i]->platforms[j] == NULL)
			{
				printf("Cant allocate memory\n");
				return 0;
			}
			if (readTrainT(file, city->trainStations[i]->platforms[j]) == 0)
				return 0;


		}



		if (fscanf(file, "%d\n", &city->trainStations[i]->type) != 1)
			return 0;
	}



	if (fscanf(file, "%d\n", &city->type) != 1)
		return 0;

	return 1;
}

void writeRouteToT(FILE* file, const Route* route)
{

	fprintf(file, "%d\n", route->routeId);

	// write train
	if (&route->train != NULL)
		writeTrainToT(file, route->train);

	if (&route->driver != NULL)
		writeDriverT(file, route->driver);

	if (&route->inspector != NULL)
		writeInspectorT(file, route->inspector);

	fprintf(file, "%d\n", route->numOfStation);

	//write list trainstationlist
	writeListToFileText(file, route->trainStationsList);



	fprintf(file, "%d\n%d\n%d\n%d\n%d\n%d\n",
		route->departureTime->year,
		route->departureTime->month,
		route->departureTime->day,
		route->departureTime->hour,
		route->departureTime->minute,
		route->departureTime->type);

	fprintf(file, "%d\n", route->type);
}

int readRouteT(FILE* file, Route* route)
{
	if (fscanf(file, "%d\n", &route->routeId) != 1)
		return 0;

	route->train = (Train*)malloc(sizeof(Train));
	if (route->train == NULL)
		return 0;
	if (!readTrainT(file, route->train))
		return 0;

	route->driver = (Driver*)malloc(sizeof(Driver));
	if (route->driver == NULL)
		return 0;
	if (!readDriverT(file, route->driver))
		return 0;

	route->inspector = (Inspector*)malloc(sizeof(Inspector));
	if (route->inspector == NULL)
		return 0;
	if (!readInspectorT(file, route->inspector))
		return 0;

	if (fscanf(file, "%d\n", &route->numOfStation) != 1)
		return 0;

	route->trainStationsList = malloc(sizeof(LIST) * route->numOfStation);
	if (route->trainStationsList == NULL) {
		// Error handling
		return 0;
	}
	L_init(route->trainStationsList);
	for (int i = 0; i < route->numOfStation; i++) {
		// Initialize each list

		if (!readListFromFileText(file, route->trainStationsList)) {
			return 0;
		}


	}

	route->departureTime = (Time*)malloc(sizeof(Time));
	if (route->departureTime == NULL)
		return 0;
	if (fscanf(file, "%d\n%d\n%d\n%d\n%d\n%d\n",
		&route->departureTime->year,
		&route->departureTime->month,
		&route->departureTime->day,
		&route->departureTime->hour,
		&route->departureTime->minute,
		&route->departureTime->type) != 6)
		return 0;

	if (fscanf(file, "%d\n", &route->type) != 1)
		return 0;

	return 1;
}

void writeListToFileText(FILE* file, const LIST* list) 
{
	if (list == NULL) {
		return ; // Error: NULL pointer
	}

	NODE* current = list->head.next; // Start from the first node

	// Traverse the list and write each node's data
	while (current != NULL) {
		// Write the data of the current node to the file
		TrainStation* temp = (TrainStation*)current->key;
		int tempStaionNameLen = 0;
		tempStaionNameLen = (int)strlen(temp->stationName);
		fprintf(file, "%d\n", tempStaionNameLen);
		fprintf(file, "\"%s\"\n", temp->stationName);

		fprintf(file, "%d\n", temp->stationSerialNumber);
		fprintf(file, "%d\n", temp->trainStationType);
		fprintf(file, "%d\n", temp->numOfPlatforms);
		tempStaionNameLen = (int)strlen(temp->locatedInCity);
		fprintf(file, "%d\n", tempStaionNameLen);
		fprintf(file, "\"%s\"\n", temp->locatedInCity);
		fprintf(file, "%d\n", temp->expectedNumOfPassengers);
		fprintf(file, "%d\n", temp->numOfActiveTrains);

		
		for (int j = 0; j < temp->numOfActiveTrains; j++)
		{
			writeTrainToT(file, temp->platforms[j]);
		}

		fprintf(file, "%d\n", temp->type);
		// Move to the next node
		current = current->next;
	}

}

int readListFromFileText(FILE* file, LIST* list) {
	int tempStationNameLen = 0;
	if (fscanf(file, "%d\n", &tempStationNameLen) != 1)
		return 0;

	TrainStation* temp = malloc(sizeof(TrainStation));
	if (temp == NULL)
		return 0;

	temp->stationName = malloc(sizeof(char) * (tempStationNameLen + 1));
	if (temp->stationName == NULL) {
		free(temp);
		return 0;
	}
	
	if (fscanf(file, "\"%[^\"]\"\n", temp->stationName) != 1) {
		free(temp->stationName);
		free(temp);
		return 0;
	}

	temp->stationName[tempStationNameLen] = '\0';

	if (fscanf(file, "%d\n", &temp->stationSerialNumber) != 1) {
		free(temp->stationName);
		free(temp);
		return 0;
	}

	if (fscanf(file, "%d\n", &temp->trainStationType) != 1) {
		free(temp->stationName);
		free(temp);
		return 0;
	}

	if (fscanf(file, "%d\n", &temp->numOfPlatforms) != 1) {
		free(temp->stationName);
		free(temp);
		return 0;
	}

	if (fscanf(file, "%d\n", &tempStationNameLen) != 1) {
		free(temp->stationName);
		free(temp);
		return 0;
	}

	temp->locatedInCity = malloc(sizeof(char) * (tempStationNameLen + 1));
	if (temp->locatedInCity == NULL) {
		free(temp->stationName);
		free(temp);
		return 0;
	}

	if (fscanf(file, "\"%[^\"]\"\n", temp->locatedInCity) != 1) {
		free(temp->stationName);
		free(temp->locatedInCity);
		free(temp);
		return 0;
	}

	temp->locatedInCity[tempStationNameLen] = '\0';

	if (fscanf(file, "%d\n", &temp->expectedNumOfPassengers) != 1) {
		free(temp->stationName);
		free(temp->locatedInCity);
		free(temp);
		return 0;
	}

	if (fscanf(file, "%d\n", &temp->numOfActiveTrains) != 1) {
		free(temp->stationName);
		free(temp->locatedInCity);
		free(temp);
		return 0;
	}

	temp->platforms = (Train**)malloc(sizeof(Train*) * temp->numOfPlatforms);
	if (temp->platforms == NULL) {
		free(temp->stationName);
		free(temp->locatedInCity);
		free(temp);
		return 0;
	}

	for (int j = 0; j < temp->numOfActiveTrains; j++) {
		temp->platforms[j] = (Train*)malloc(sizeof(Train));
		if (temp->platforms[j] == NULL) {
			// Free allocated platforms before returning
			for (int k = 0; k < j; k++) {
				free(temp->platforms[k]);
			}
			free(temp->platforms);
			free(temp->stationName);
			free(temp->locatedInCity);
			free(temp);
			return 0;
		}
		if (!readTrainT(file, temp->platforms[j])) {
			// Free allocated platforms before returning
			for (int k = 0; k <= j; k++) {
				free(temp->platforms[k]);
			}
			free(temp->platforms);
			free(temp->stationName);
			free(temp->locatedInCity);
			free(temp);
			return 0;
		}
	}

	if (fscanf(file, "%d\n", &temp->type) != 1) {
		free(temp->stationName);
		free(temp->locatedInCity);
		free(temp->platforms);
		free(temp);
		return 0;
	}

	// Insert the node into the list at the beginning
	if (!L_insert(&list->head, temp)) {
		// Insertion failed, free allocated memory
		free(temp->stationName);
		free(temp->locatedInCity);
		free(temp->platforms);
		free(temp);
		return 0;
	}


	return 1; // Success
}




int saveInfoToFileB(const TrainCompany* pTrainCompany, const char* fileName)
{	
	
	FILE* file = fopen(fileName, "wb");
	if (file == NULL) {
		printf("Error opening file %s\n", fileName);
		return 0;
	}
	//write type
	fwrite(&pTrainCompany->type, sizeof(int), 1, file);
	
	// Write company name length and name
	int companyNameLen = (int)strlen(pTrainCompany->companyName);
	if (fwrite(&companyNameLen, sizeof(int), 1, file) != 1) { fclose(file); return 0; }

	fwrite(pTrainCompany->companyName, sizeof(char), companyNameLen, file);

	// Write number of drivers
	int numOfDrivers = pTrainCompany->numOfDrivers;
	if (fwrite(&numOfDrivers, sizeof(int), 1, file) != 1) { fclose(file); return 0; }

	for (int i = 0; i < pTrainCompany->numOfDrivers; i++)
	{
		writeDriverToFileBNested(file, &pTrainCompany->driversArray[i]);

	}

	// Write number of inspectors
	int numOfInspectors = pTrainCompany->numOfInspectors;
	if (fwrite(&numOfInspectors, sizeof(int), 1, file) != 1) { fclose(file); return 0; }

	for (int i = 0; i < pTrainCompany->numOfInspectors; i++)
	{

		writeInspectorToFileB(file, &pTrainCompany->inspectorsArray[i]);

	}


	if (fwrite(&pTrainCompany->numOfTrains, sizeof(int), 1, file) != 1) { fclose(file); return 0; }

	for (int i = 0; i < pTrainCompany->numOfTrains; i++)
	{
		writeTrainToFileB(file, &pTrainCompany->trainsArray[i]);

	}

	int numOfCities = pTrainCompany->numOfActiveCities;
	if (fwrite(&numOfCities, sizeof(int), 1, file) != 1) { fclose(file); return 0; }
	int cityLenTemp = 0;
	for (int i = 0; i < pTrainCompany->numOfActiveCities; i++)
	{
		writeCityToFileB(file, pTrainCompany->citiesArray[i]);
	}

	if ((fwrite(&pTrainCompany->numOfRoutes, sizeof(int), 1, file)) != 1)
	{
		fclose(file);
		return 0;
	}

	for (int i = 0; i < pTrainCompany->numOfRoutes; i++)
	{
		writeRouteToFileB(file, pTrainCompany->routesArray[i]);

	}

	
	fclose(file);
	return 1;
}

int readInfoFromBinary(TrainCompany* pTrainCompany, const char* fileName)
{
	int check;
	int numofElem = 1;
	FILE* file = fopen(fileName, "rb");
	if (file == NULL) {
		printf("Error opening file %s\n", fileName);
		return 0;
	}

	if (fread(&pTrainCompany->type, sizeof(int), numofElem, file) != numofElem) {
		fclose(file);
		return 0;
	}

	int companyNameLen = 0;
	// read the len of company name
	if (fread(&companyNameLen, sizeof(int), numofElem, file) != numofElem) {
		fclose(file);
		return 0;
	}
	// allocate memory for company name
	pTrainCompany->companyName = (char*)malloc(sizeof(char) * (companyNameLen + 1));
	if (pTrainCompany->companyName == NULL) {
		fclose(file);
		free(pTrainCompany->companyName);

		return 0;
	}

	//the read the company name
	if (fread(pTrainCompany->companyName, sizeof(char), companyNameLen, file) != companyNameLen) {
		fclose(file);
		free(pTrainCompany->companyName);
		return 0;
	}
	pTrainCompany->companyName[companyNameLen] = '\0';

	if (fread(&pTrainCompany->numOfDrivers, sizeof(int), numofElem, file) != numofElem) {
		fclose(file);
		free(pTrainCompany->companyName);
		return 0;
	}

	pTrainCompany->driversArray = malloc(pTrainCompany->numOfDrivers * sizeof(Driver));
	if (pTrainCompany->driversArray == NULL) {
		fclose(file);
		free(pTrainCompany->companyName);
		return 0;
	}
	//read driver
	for (int i = 0; i < pTrainCompany->numOfDrivers; i++)
	{
		check = readDriverFromFileBNested(file, &pTrainCompany->driversArray[i]);
		if (check == 0)
		{
			fclose(file);
			free(pTrainCompany->companyName);
			freeDriverArray(pTrainCompany);
			return 0;
		}

	}


	if (fread(&pTrainCompany->numOfInspectors, sizeof(int), numofElem, file) != numofElem) {
		fclose(file);
		free(pTrainCompany->companyName);
		freeDriverArray(pTrainCompany);
		return 0;
	}

	pTrainCompany->inspectorsArray = malloc(pTrainCompany->numOfInspectors * sizeof(Inspector));
	if (pTrainCompany->inspectorsArray == NULL) {
		fclose(file);
		free(pTrainCompany->companyName);
		return 0;
	}
	//read inspectors
	int InspectorNameLen=0;
	for (int i = 0; i < pTrainCompany->numOfInspectors; i++)
	{
		check = readInspectorFromFileB(file, &pTrainCompany->inspectorsArray[i]);
		if (check == 0)
		{
			fclose(file);
			free(pTrainCompany->companyName);
			freeDriverArray(pTrainCompany);
			freeInspectorArray(pTrainCompany);
			return 0;
		}

	}

	if (fread(&pTrainCompany->numOfTrains, sizeof(int), numofElem, file) != numofElem) {
		fclose(file);
		free(pTrainCompany->companyName);
		freeDriverArray(pTrainCompany);
		freeInspectorArray(pTrainCompany);
		return 0;
	}

	pTrainCompany->trainsArray = malloc(sizeof(Train) * pTrainCompany->numOfTrains);
	if (pTrainCompany->trainsArray == NULL) {
		fclose(file);
		free(pTrainCompany->companyName);
		freeDriverArray(pTrainCompany);
		freeInspectorArray(pTrainCompany);
		return 0;
	}
	//read train
	for (int i = 0; i < pTrainCompany->numOfTrains; i++)
	{
		if (readTrainFromFileB(file, &pTrainCompany->trainsArray[i]) == 0)
		{
			fclose(file);
			free(pTrainCompany->companyName);
			freeDriverArray(pTrainCompany);
			freeInspectorArray(pTrainCompany);
			freeTrains(pTrainCompany);
		}

	}

	if (fread(&pTrainCompany->numOfActiveCities, sizeof(int), numofElem, file) != numofElem) {
		fclose(file);
		free(pTrainCompany->companyName);
		freeDriverArray(pTrainCompany);
		freeInspectorArray(pTrainCompany);
		free(pTrainCompany->trainsArray);
		return 0;
	}


	pTrainCompany->citiesArray = (City**)malloc(sizeof(City*) * pTrainCompany->numOfActiveCities);
	if (pTrainCompany->citiesArray == NULL) {
		fclose(file);
		free(pTrainCompany->companyName);
		freeDriverArray(pTrainCompany);
		freeInspectorArray(pTrainCompany);
		return 0;
	}
	// read cities
	for (int i = 0; i < pTrainCompany->numOfActiveCities; i++)
	{
		pTrainCompany->citiesArray[i] = (City*)malloc(sizeof(City));
		if (pTrainCompany->citiesArray[i] == NULL)
		{
			fclose(file);
			free(pTrainCompany->companyName);
			freeDriverArray(pTrainCompany);
			freeInspectorArray(pTrainCompany);
			freeCities(pTrainCompany);
			free(pTrainCompany->trainsArray);
			return 0;
		}
		if (readCityFromFileB(file, pTrainCompany->citiesArray[i]) == 0)
		{
			fclose(file);
			free(pTrainCompany->companyName);
			freeDriverArray(pTrainCompany);
			freeInspectorArray(pTrainCompany);
			freeCities(pTrainCompany);
			free(pTrainCompany->trainsArray);
			return 0;
		}


	}

	// read routes
	if (fread(&pTrainCompany->numOfRoutes, sizeof(int), numofElem, file) != numofElem) {
		fclose(file);
		free(pTrainCompany->companyName);
		freeDriverArray(pTrainCompany);
		freeInspectorArray(pTrainCompany);
		freeCities(pTrainCompany);
		free(pTrainCompany->trainsArray);
		return 0;
	}

	if (pTrainCompany->numOfRoutes == 0)
	{
		pTrainCompany->routesArray = NULL;
	}
	else
	{
		pTrainCompany->routesArray = (Route**)malloc(pTrainCompany->numOfRoutes * sizeof(Route*));
		if (pTrainCompany->routesArray == NULL)
		{
			fclose(file);
			free(pTrainCompany->companyName);
			freeDriverArray(pTrainCompany);
			freeInspectorArray(pTrainCompany);
			freeCities(pTrainCompany);
			free(pTrainCompany->trainsArray);
			return 0;
		}

		for (int i = 0; i < pTrainCompany->numOfRoutes; i++)
		{
			pTrainCompany->routesArray[i] = (Route*)malloc(sizeof(Route));
			if (pTrainCompany->routesArray[i] == NULL)
			{
				fclose(file);
				free(pTrainCompany->companyName);
				freeDriverArray(pTrainCompany);
				freeInspectorArray(pTrainCompany);
				freeCities(pTrainCompany);
				free(pTrainCompany->trainsArray);
				return 0;
			}

			if (readRouteFromB(file, pTrainCompany->routesArray[i]) == 0)
			{
				fclose(file);
				free(pTrainCompany->companyName);
				freeDriverArray(pTrainCompany);
				freeInspectorArray(pTrainCompany);
				freeCities(pTrainCompany);
				free(pTrainCompany->trainsArray);
				return 0;
			}

		}

	}


	fclose(file);
	return 1;
}

int saveInfoToFileT(const TrainCompany* pTrainCompany, const char* fileName)
{

	FILE* file = fopen(fileName, "wt");
	if (file == NULL) {
		printf("Error opening file %s\n", fileName);
		return 0;
	}
	//write type
	fprintf(file, "%d\n", pTrainCompany->type);

	// Write company name and length
	int companyNamelen = (int)strlen(pTrainCompany->companyName);
	fprintf(file, "%d\n", companyNamelen);
	fprintf(file, "%s\n", pTrainCompany->companyName);

	// Write drivers
	fprintf(file, "%d\n", pTrainCompany->numOfDrivers);
	int driverLen = 0;

	for (int i = 0; i < pTrainCompany->numOfDrivers; i++)
	{
		writeDriverT(file, &pTrainCompany->driversArray[i]);
	}
	// Write inspectors
	fprintf(file, "%d\n", pTrainCompany->numOfInspectors);

	for (int i = 0; i < pTrainCompany->numOfInspectors; i++)
	{
		writeInspectorT(file, &pTrainCompany->inspectorsArray[i]);
	}

	fprintf(file, "%d\n", pTrainCompany->numOfTrains);
	//write Trains
	for (int i = 0; i < pTrainCompany->numOfTrains; i++)
	{
		writeTrainToT(file, &pTrainCompany->trainsArray[i]);

	}

	fprintf(file, "%d\n", pTrainCompany->numOfActiveCities);
	int citynamelen = 0;
	//write city
	for (int i = 0; i < pTrainCompany->numOfActiveCities; i++)
	{
		writeCityToT(file, pTrainCompany->citiesArray[i]);
	}

	//write routes
	fprintf(file, "%d\n", pTrainCompany->numOfRoutes);
	for (int i = 0; i < pTrainCompany->numOfRoutes; i++)
	{

		writeRouteToT(file, pTrainCompany->routesArray[i]);
	}

	fclose(file);
	return 1;
}

int ReadInfoFromT(TrainCompany* pTrainCompany, const char* fileName)
{
	FILE* file = fopen(fileName, "r");
	if (file == NULL) {
		printf("Error opening file %s\n", fileName);
		return 0;
	}
	//read type		
	if (fscanf(file, "%d\n", &pTrainCompany->type) != 1) {
		fclose(file);
		return 0;
	}
	
	// Read company name
	int companyNameLen = 0;
	if (fscanf(file, "%d\n", &companyNameLen) != 1) {
		fclose(file);
		return 0;
	}
	pTrainCompany->companyName = malloc(sizeof(char) * (companyNameLen + 1));
	if (pTrainCompany->companyName == NULL) {
		fclose(file);
		return 0;
	}
	char companyName[MAX_STR_LEN] = "";
	if (fscanf(file, "%s\n", companyName) != 1) {
		free(pTrainCompany->companyName);
		fclose(file);
		return 0;
	}
	companyName[companyNameLen] = '\0';

	strcpy(pTrainCompany->companyName, companyName);


	// Read number of drivers
	int numOfDrivers = 0;
	if (fscanf(file, "%d\n", &numOfDrivers) != 1)
	{
		free(pTrainCompany->companyName);
		fclose(file);
		return 0;
	}

	pTrainCompany->numOfDrivers = numOfDrivers;

	// Allocate memory for drivers
	pTrainCompany->driversArray = (Driver*)malloc(numOfDrivers * sizeof(Driver));
	if (pTrainCompany->driversArray == NULL) {
		free(pTrainCompany->companyName);
		freeDriverArray(pTrainCompany);
		fclose(file);
		return 0;
	}
	// Read drivers
	for (int i = 0; i < numOfDrivers; i++)
	{
		if (readDriverT(file, &pTrainCompany->driversArray[i]) == 0)
		{
			free(pTrainCompany->companyName);
			freeDriverArray(pTrainCompany);
			freeDriverArray(pTrainCompany);
			fclose(file);
			return 0;
		}
	}

	// Read number of inspectors
	int numOfInspectors = 0;
	if (fscanf(file, "%d\n", &numOfInspectors) != 1)
	{
		free(pTrainCompany->companyName);
		freeDriverArray(pTrainCompany);
		fclose(file);
		return 0;
	}

	pTrainCompany->numOfInspectors = numOfInspectors;

	pTrainCompany->inspectorsArray = (Inspector*)malloc(numOfInspectors * sizeof(Inspector));
	if (pTrainCompany->inspectorsArray == NULL) {
		free(pTrainCompany->companyName);
		freeDriverArray(pTrainCompany);
		freeInspectorArray(pTrainCompany);
		fclose(file);
		return 0;
	}

	// Read inspectors
	for (int i = 0; i < numOfInspectors; i++)
	{
		if (readInspectorT(file, &pTrainCompany->inspectorsArray[i]) == 0)
		{
			free(pTrainCompany->companyName);
			freeDriverArray(pTrainCompany);
			freeInspectorArray(pTrainCompany);
			fclose(file);
			return 0;
		}

	}


	int numOfTrains = 0;
	if (fscanf(file, "%d\n", &numOfTrains) != 1)
	{
		free(pTrainCompany->companyName);
		freeDriverArray(pTrainCompany);
		freeInspectorArray(pTrainCompany);
		fclose(file);
		return 0;
	}
	pTrainCompany->numOfTrains = numOfTrains;

	pTrainCompany->trainsArray = (Train*)malloc(numOfTrains * sizeof(Train));

	// read train
	for (int i = 0; i < numOfTrains; i++)
	{
		if (readTrainT(file, &pTrainCompany->trainsArray[i]) == 0)
		{
			free(pTrainCompany->companyName);
			freeDriverArray(pTrainCompany);
			freeInspectorArray(pTrainCompany);
			fclose(file);
			return 0;
		}

	}

	int numOfCities = 0;
	if (fscanf(file, "%d\n", &numOfCities) != 1)
	{
		free(pTrainCompany->companyName);
		freeDriverArray(pTrainCompany);
		freeInspectorArray(pTrainCompany);
		free(pTrainCompany->trainsArray);
		fclose(file);
		return 0;
	}
	pTrainCompany->numOfActiveCities = numOfCities;
	pTrainCompany->citiesArray = (City**)malloc(numOfCities * sizeof(City*));
	// read city
	for (int i = 0; i < numOfCities; i++)
	{
		pTrainCompany->citiesArray[i] = (City*)malloc(sizeof(City));
		if (pTrainCompany->citiesArray[i] == NULL)
		{
			free(pTrainCompany->companyName);
			freeDriverArray(pTrainCompany);
			freeInspectorArray(pTrainCompany);
			freeTrains(pTrainCompany);
			fclose(file);
			return 0;
		}
		if (readCityT(file, pTrainCompany->citiesArray[i]) == 0)
		{
			free(pTrainCompany->companyName);
			freeDriverArray(pTrainCompany);
			freeInspectorArray(pTrainCompany);
			freeTrains(pTrainCompany);
			fclose(file);
			return 0;
		}


	}


	int numOfRoutes = 0;
	if (fscanf(file, "%d\n", &numOfRoutes) != 1)
	{
		free(pTrainCompany->companyName);
		freeDriverArray(pTrainCompany);
		freeInspectorArray(pTrainCompany);
		freeTrains(pTrainCompany);
		freeCities(pTrainCompany);
		fclose(file);
		return 0;
	}

	pTrainCompany->numOfRoutes = numOfRoutes;
	if (numOfRoutes == 0)
	{
		pTrainCompany->routesArray = NULL;
	}
	//read route
	else
	{
		pTrainCompany->routesArray = (Route**)malloc(numOfRoutes * sizeof(Route*));
		for (int i = 0; i < numOfRoutes; i++)
		{
			pTrainCompany->routesArray[i] = (Route*)malloc(sizeof(Route));
			if (pTrainCompany->routesArray[i] == NULL)
			{
				free(pTrainCompany->companyName);
				freeDriverArray(pTrainCompany);
				freeInspectorArray(pTrainCompany);
				freeTrains(pTrainCompany);
				freeCities(pTrainCompany);
				freeTrainRoutes(pTrainCompany);
				fclose(file);
				return 0;
			}
			if (!readRouteT(file, pTrainCompany->routesArray[i]))
			{
				free(pTrainCompany->companyName);
				freeDriverArray(pTrainCompany);
				freeInspectorArray(pTrainCompany);
				freeTrains(pTrainCompany);
				freeCities(pTrainCompany);
				freeTrainRoutes(pTrainCompany);
				fclose(file);
				return 0;
			}
		}
	}
	fclose(file);
	return 1;

}
