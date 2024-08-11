#define _CRT_SECURE_NO_WARNINGS

#include "City.h"



int	updateNumOfPlatforms(TrainStation* pTrainStation)
{
	printf("You wish to update the number of platforms in the station, the current number of platforms is: %d\n", pTrainStation->numOfPlatforms);
	boolean flag = True;
	int numberOfPlatforms = -1;
	while (flag) {
		printf("Please choose the new number of platforms in the station:\n");
		if (scanf("%d", &numberOfPlatforms) != 1)
		{
			printf("Bad input.\n");
			return 0;
		}
		if (numberOfPlatforms < MIN_PLATFORMS || numberOfPlatforms > MAX_PLATFORMS)
		{
			printf("You have entered an invalid number, try again.\n");
			continue;
		}
		else
			flag = False;
	}

	if (pTrainStation->numOfActiveTrains >=numberOfPlatforms)
	{
		printf("You cannot lower the platform more than active trains in station.\n");
		return 0;
	}

	pTrainStation->numOfPlatforms = numberOfPlatforms;

	if (updatePlatformsArraySize(pTrainStation) == 0)
	{
		// Free memory for platforms before returning
		for (int i = 0; i < numberOfPlatforms; i++)
		{
			free(pTrainStation->platforms[i]);
		}
		return 0;
	}

	for (int i = 0; i < pTrainStation->numOfPlatforms; i++)
	{
		pTrainStation->platforms[i] = (Train*)malloc(sizeof(Train));
		if (pTrainStation->platforms[i] == NULL)
		{
			// Free memory for platforms before returning
			for (int j = 0; j < i; j++)
			{
				free(pTrainStation->platforms[j]);
			}
			printf("Cannot allocate memory.\n");
			return 0;
		}
	}


	return 1;
}

int updatePlatformsArraySize(TrainStation* pTrainStation)
{
	Train** tempPlatforms = (Train**)realloc(pTrainStation->platforms, sizeof(Train*) * pTrainStation->numOfPlatforms);
	if (tempPlatforms == NULL)
	{
		printf("Error allocating memory for platforms.");
		return 0; // Memory allocation failed, return 0 to indicate failure
	}

	// Memory reallocation successful, update platforms pointer
	pTrainStation->platforms = tempPlatforms;

	return 1; // Return 1 to indicate success
}






void printTrainStation(const TrainStation* pTrainStation)
{
	printf("Train station name: %s ,", pTrainStation->stationName);
	printf("serial number: %d, ", pTrainStation->stationSerialNumber);
	printf("station type: %s, ", TrainTypeStation[pTrainStation->trainStationType]);
	printf("available station platforms %d and there are %d active trains ,", pTrainStation->numOfPlatforms, pTrainStation->numOfActiveTrains);
	printf("number of daily passengers %d\n", pTrainStation->expectedNumOfPassengers);
}

void printTrainStationInList(const TrainStation* pTrainStation)
{
	printf("Train station name: %s, ", pTrainStation->stationName);
	printf("Serial number: %d\n", pTrainStation->stationSerialNumber);
}

void printTrainStationWithTrains(const TrainStation* pTrainStation)
{
	
		printf("[Train station name: %s] ,", pTrainStation->stationName);
		printf("[Serial number: %d and type %s], ", pTrainStation->stationSerialNumber, TrainTypeStation[pTrainStation->trainStationType]);

		printf("[available station %d and %d are active] ,", pTrainStation->numOfPlatforms, pTrainStation->numOfActiveTrains);
		printf("[Number of daily passengers %d]\n", pTrainStation->expectedNumOfPassengers);

		printf("and there are %d trains\n", pTrainStation->numOfActiveTrains);
		for (int i = 0; i < pTrainStation->numOfActiveTrains; i++)
		{
			printTrain(pTrainStation->platforms[i]);
		}
}


int compareTrainSerial(const void* a, const void* b) {
	const Train* trainA = *(const Train**)a;
	const Train* trainB = *(const Train**)b;

	// Compare serial numbers of two trains
	if (trainA->serialNumber < trainB->serialNumber) {
		return -1; // trainA comes before trainB
	}
	else if (trainA->serialNumber > trainB->serialNumber) {
		return 1; // trainA comes after trainB
	}
	else {
		return 0; // trainA and trainB have equal serial numbers
	}

}


int compareCityTrainSerial(const void* key, const void* element)
{
	const int searchCode = *(const int*)key;
	const Train* train = *(const Train**)element;


	if (train->serialNumber < searchCode)
	{
		return -1;
	}
	else if (train->serialNumber > searchCode)
	{
		return 1;
	}
	return 0;

}


void sortCityTrainStation(TrainStation* station)
{
	// Sort the platforms within the train station based on train serial number
	qsort(station->platforms, station->numOfActiveTrains, sizeof(Train*), compareTrainSerial);
}



int searchTrainInCity(TrainStation** trainStations, const int trainSerial, int numTrainStation)
{
	
	for (int i = 0; i < numTrainStation; i++)
	{
		if (trainStations[i]->numOfActiveTrains != 0)
		{
			sortCityTrainStation(trainStations[i]);
			Train* temptrain =(Train*) bsearch(&trainSerial, trainStations[i]->platforms, trainStations[i]->numOfActiveTrains, sizeof(Train*), compareCityTrainSerial);
			
			if (temptrain != NULL)
			{
				return 1;
			}
		}
	}

	return 0; // Train not found in any station
}


int searchTrainInTrainStation(const TrainStation* pTrainStation, const int serialNum)
{

	for (int i = 0; i < pTrainStation->numOfActiveTrains; i++)
	{
		if (pTrainStation->platforms[i]->serialNumber == serialNum)
		{
			printf("The train %d is already at the train station\n", serialNum);
			return 0;
		}

	}

	return 1;
}

void freeTrainStation(TrainStation* pTrainStation)
{	
	for (int i = 0; i < pTrainStation->numOfActiveTrains; i++)
	{
		freeTrain(pTrainStation->platforms[i]);
	}
	free(pTrainStation->platforms);
}

