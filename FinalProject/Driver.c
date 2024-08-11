#include "Driver.h"
#include "TrainCompany.h"


int initDriver(Driver* driver)
{
	driver->type = eDriver;
	srand((unsigned int)time(NULL));

	printf("Enter the name of the driver:\n");
	char temp[MAX_STR_LEN];
	myGets(temp, MAX_STR_LEN);
	driver->DriverName = malloc(strlen(temp) + 1);
	if (driver->DriverName == NULL) 
	{
		printf("Memory allocation failed.\n");
		return 0; // Return 0 to indicate failure
	}
	strcpy(driver->DriverName, temp);
	// generate random number 1-9999
	driver->licenseNumber = rand() % 9999 + 1;


	boolean flag = True;
	int answer = -1;

	while (flag) {
		flag = False;
		printf("Enter what tpye of license:\n");
		printf("1)FastPassenger\n2)LightPassenger\n3)Metro\n4)Cargo\n");
		if (scanf("%d", &answer) != 1)
		{
			printf("Bad input.\n");
			return 0;
		}
		if (answer > 4 || answer < 1)
		{
			flag = True;
			printf("You have entered wrong input try again\n");
		}

	}
	driver->licenseType = answer - 1;


	return 1;
}

int changeLicense(Driver* driver)
{
	boolean flag = True;
	int answer = -1;

	printf("You wish to change the driver's license, the current license is %s\n", TrainTypeStr[driver->licenseType]);
	while (flag) {
		printf("Please choose one of the following options: 0 - FastPassenger, 1 - LightPassenger, 2 - Metro, 3 - Cargo\n");
		if (scanf("%d", &answer) != 1)
		{
			printf("Bad input.\n");
			return 0;
		}
		if (answer > 3 || answer < 0)
		{
			printf("You have selected a wrong choice, try again.\n");
			continue;
		}
		else
			flag = False;
	}
	driver->licenseType = answer;
	printf("The driver license have been changed to [%s]\n", TrainTypeStr[driver->licenseType]);

	return 1;
}




void printDriver(const Driver* driver)
{
	printf("[Driver detail]\tname: %s\tlicenseNumber: %d\tlicenseType: %s\n", driver->DriverName, driver->licenseNumber, TrainTypeStr[driver->licenseType]);

}



void freeDriver(Driver* driver)
{
	free(driver->DriverName);
}

int compareLicense(const void* a, const void* b) {
	if (a == NULL || b == NULL) {
		// Handle the case where one or both pointers are null
		return 0;  
	}

	const Driver* drivera = (const Driver*)a;
	const Driver* driverb = (const Driver*)b;

	// Compare the license types
	if (drivera->licenseType < driverb->licenseType) {
		return -1; // a comes before b
	}
	else if (drivera->licenseType > driverb->licenseType) {
		return 1;  // a comes after b
	}
	else {
		return 0;  // License types are equal
	}
}

int compareDriverBylicenseNumber(const void* key, const void* element) {
	
	int searchID = *(const int*)key;
	const Driver* driver = (const Driver*)element;

	if (searchID < driver->licenseNumber) {
		return -1;  // key comes before element
	}
	else if (searchID > driver->licenseNumber) {
		return 1;   // key comes after element
	}
	else {
		return 0;   // IDs are equal
	}
}


void sortDriversByLicenseType(Driver* driversArray, int numOfDrivers) {
	// Use qsort to sort the driversArray based on licenseType
	qsort(driversArray, numOfDrivers, sizeof(Driver), compareLicense);
}

Driver* searchDriverBylicenseNumber(int licenseNumber, Driver* driversArray, int numOfDrivers) {
	// Use bsearch to search for the driver with the given licenseNumber
	return (Driver*)bsearch(&licenseNumber, driversArray, numOfDrivers, sizeof(Driver), compareDriverBylicenseNumber);
}

// Compare function for sorting drivers by license number
int compareDriverByLicenseNumber(const void* a, const void* b) {
	const Driver* driverA = (const Driver*)a;
	const Driver* driverB = (const Driver*)b;

	if (driverA->licenseNumber < driverB->licenseNumber) {
		return -1;
	}
	else if (driverA->licenseNumber > driverB->licenseNumber) {
		return 1;
	}
	else {
		return 0;
	}
}

// Function to sort drivers by license number
void sortDriversByLicenseNumber(Driver* driversArray, int numOfDrivers) {
	qsort(driversArray, numOfDrivers, sizeof(Driver), compareDriverByLicenseNumber);
}
