/* Train Struct */

#include "Train.h"

int	initTrain(Train* pTrain, Train* trainArr, int trainCount) 
{
	pTrain->type = eTrain;
	
	// Loop that sets the train's serial number:
	boolean badSerialNumber = True; 
	int tempSerialNumber;
	while (badSerialNumber)
	{
		badSerialNumber = False;
		srand((unsigned int)time(NULL));
		tempSerialNumber = rand() % 9999 + 1;
		for (int i = 0; i < trainCount; i++)// Checks if there is already a train with the same serial number
			if (trainArr[i].serialNumber == tempSerialNumber)
				badSerialNumber = True;
	}
	pTrain->serialNumber = tempSerialNumber;
	
	// Loop that sets the train's type:
	boolean badTrainType = True;
	int trainType = -1;
	while (badTrainType)
	{
		printf("Please select the type of train,\n");
		printf("0 - %s, 1 - %s, 2 - %s, 3 - %s:\n", TrainTypeStr[eFastPassenger], TrainTypeStr[eLightPassenger], TrainTypeStr[eMetro], TrainTypeStr[eCargo]);
		if (scanf("%d", &trainType) != 1)
		{
			printf("Bad input.\n");
			continue;
		}
		if (trainType < eFastPassenger || trainType > eCargo)
		{
			printf("Invalid train type choice, try again.\n");
			continue;
		}
		else
			badTrainType = False;
	}
	pTrain->trainType = trainType;
	
	// Function that sets the train's number of cars
	if (setNumberOfCars(pTrain) == False)
		return 0;
	
	// Function that sets the train's license validity date:
	if (updateValidityLicense(pTrain) == False)
		return 0;
	
	return 1;
}

int	setNumberOfCars(Train* pTrain)
{
	boolean badNumberOfCarts = True;
	int numberOfCars = -1;
	while (badNumberOfCarts)
	{
		printf("Please select how many carts you would like to be attached to this train:\n");
		if (scanf("%d", &numberOfCars) != 1)
		{
			printf("Bad input.\n");
			continue;
		}
		if (numberOfCars < MIN_CARS || numberOfCars > MAX_CARS)
		{
			printf("Invalid cart number choice, try again.\n");
			continue;
		}
		else
			badNumberOfCarts = False;
	}
	pTrain->numOfRailroadCars = numberOfCars;
	if (pTrain->numOfRailroadCars == -1)
		return 0;

	return 1;
}

int	updateValidityLicense(Train* pTrain) 
{
	Time tempTime;
	printf("Please choose the train's license validity date:\n");
	if (initTravelTime(&tempTime) == False)// Initiates a time structure
		return 0;
	pTrain->trainValidityLicenseDate = tempTime;
	


	return 1;
}

void printTrain(const Train* pTrain) 
{
	printf("Train number: %d, Type: %s, Number of attached cars: %d, Validity: ", pTrain->serialNumber, TrainTypeStr[pTrain->trainType], pTrain->numOfRailroadCars);
	printTravelTime(&pTrain->trainValidityLicenseDate);
}


void freeTrain(Train* pTrain) 
{
	// Nothing to dynamically free here...
}
