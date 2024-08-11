#define _CRT_SECURE_NO_WARNINGS

#include "Functions.h"
#include "TrainCompany.h"
#include "City.h"


#define COMPANY_FILE_TXTDST "TrainCompanyT.txt"

#define COMPANY_FILE_BINDST "TrainCompanyB.bin"

int main()
{
	TrainCompany	company;
	int opt;
	int res = 0;
	int flag = 1;
	printf("### Welcome to our train management system ###\n");

	int readChoice = 0;
	int read = 0;

	printf("\nWould you like to read data from a file?(0-no,1-yes)\n");
	if (scanf("%d", &readChoice) != 1)
	{
		printf("Bad input.\n");
	}
	if (readChoice == 1)
	{
		printf("Do you want to read from a text file or a binary file?(0-text,1-binary)\n");
		if (scanf("%d", &read) != 1)
		{
			printf("Bad input.\n");
		}
		if (read == 0)
		{
			res = ReadInfoFromT(&company, COMPANY_FILE_TXTDST);
			if (res == 0)
			{
				printf("Can't read file so init one.\n");
				res = initTrainCompany(&company);
			}

		}
		else
		{
			res = readInfoFromBinary(&company, COMPANY_FILE_BINDST);
			if (res == 0)
			{
				printf("Can't read file so init one.\n");
				res = initTrainCompany(&company);
			}
		}
	}
	else if (readChoice == 0)
	{
		res = initTrainCompany(&company);
		if (res == 0)
		{
			printf("Error init train Company\n");
			return 0;
		}
	}

	while (flag) {
		printAsciiTrain();
		printf("\nCompany %s \nmain menu\n", company.companyName);
		PRINT_MAIN_MENU();
		if (scanf("%d", &opt) != 1)
		{
			printf("Bad input.\n");
			break;
		}

		switch (opt)
		{
		case -1:
			flag = 0;

			saveInfoToFileB(&company, COMPANY_FILE_BINDST);
			saveInfoToFileT(&company, COMPANY_FILE_TXTDST);

			//need to free the company
			freeCompany(&company);
			break;
		case 0:
			changeCompanyName(&company);
			break;

		case 1:
			printMenuCase1();
			if (scanf("%d", &opt) != 1)
			{
				printf("Bad input.\n");
				break;
			}
			if (opt == 1)
			{
				boolean flagForLoop = True;
				int finish;
				while (flagForLoop)
				{
					addTrain(&company);

					printf("Do you wish to continue adding a train? (1-yes/0-no)\n");

					if (scanf("%d", &finish) != 1)
					{
						printf("Bad input.\n");
						break;
					}
					if (finish == 1)
					{
						//nothing
					}
					else if (finish == 0)
					{
						flagForLoop = False;
					}
					else
					{
						printf("Bad input.\n");
					}
				}
			}
			else if (opt == 2)
			{
				boolean flagForLoop = True;
				int finish;
				int serialNum;
				int choise = 1;
				while (flagForLoop)
				{
					if (company.numOfTrains == 0)
					{
						printf("There are no trains!\n");
						break;
					}
					printTrains(&company);

					printf("Choose which train serial Number you want to update:\n");

					if (scanf("%d", &serialNum) != 1)
					{
						printf("Bad input.\n");
						break;
					}

					updateTrain(&company, serialNum, choise);

					printf("Do you wish to continue updating trains? (1-yes/0-no)\n");

					if (scanf("%d", &finish) != 1)
					{
						printf("Bad input.\n");
						break;
					}
					if (finish == 1)
					{
						//nothing
					}
					else if (finish == 0)
					{
						flagForLoop = False;
					}
					else
					{
						printf("Bad input.\n");
					}
				}
			}
			else if (opt == 3)
			{
				boolean flagForLoop = True;
				int finish;
				int serialNum;
				int choise = 2;
				while (flagForLoop)
				{
					if (company.numOfTrains == 0)
					{
						printf("There are no trains!\n");
						break;
					}

					printTrains(&company);

					printf("Choose which train serial Number you want to remove:\n");

					if (scanf("%d", &serialNum) != 1)
					{
						printf("Bad input.\n");
						break;
					}

					updateTrain(&company, serialNum, choise);
					if (company.numOfTrains == 0)
					{
						break;
					}

					printf("Do you wish to continue removing trains? (1-yes/0-no)\n");

					if (scanf("%d", &finish) != 1)
					{
						printf("Bad input.\n");
						break;
					}
					if (finish == 1)
					{
						//nothing
					}
					else if (finish == 0)
					{
						flagForLoop = False;
					}
					else
					{
						printf("Bad input.\n");
					}
				}
			}
			else if (opt == -1)
			{
				break;
			}
			else
			{
				printf("Bad input, Please try again.\n");
				cleanbuffer();
			}
			break;

		case 2:

			printMenuCase2();
			if (scanf("%d", &opt) != 1)
			{
				printf("Bad input.\n");
				break;
			}
			if (opt == 1)
			{
				boolean flagForLoop = True;
				int finish;
				while (flagForLoop)
				{
					addDriver(&company);

					printf("Do you wish to continue adding drivers? (1-yes/0-no)\n");

					if (scanf("%d", &finish) != 1)
					{
						printf("Bad input.\n");
						break;
					}
					if (finish == 1)
					{
						//nothing
					}
					else if (finish == 0)
					{
						flagForLoop = False;
					}
					else
					{
						printf("Bad input.\n");
						break;
					}
				}
			}
			else if (opt == 2)
			{
				boolean flagForLoop = True;
				int finish;

				while (flagForLoop)
				{
					addInspector(&company);

					printf("Do you wish to continue adding inspectors? (1-yes/0-no)\n");

					if (scanf("%d", &finish) != 1)
					{
						printf("Bad input.\n");
						break;
					}
					if (finish == 1)
					{
						//nothing

					}
					else if (finish == 0)
					{
						flagForLoop = False;
					}
					else
					{
						printf("Bad input.\n");
					}
				}
			}
			else if (opt == 3)
			{
				boolean flagForLoop = True;
				int idForChange;
				int finish;

				while (flagForLoop)
				{
					if (company.numOfDrivers == 0)
					{
						printf("There are no drivers!\n");
						break;
					}

					printDriverArray(&company);
					printf("Choose what licenseNumber you want to change:\n");
					if (scanf("%d", &idForChange) != 1)
					{
						printf("Bad input.\n");
						break;
					}

					chagneDriverLicense(&company, idForChange);
					printf("Do you wish to continue changing? (1-yes/0-no)\n");

					if (scanf("%d", &finish) != 1)
					{
						printf("Bad input.\n");
						break;
					}
					if (finish == 1)
					{
						//nothing
					}
					else if (finish == 0)
					{
						flagForLoop = False;
					}
					else
					{
						printf("Bad input.\n");
					}
				}
			}

			else if (opt == 4)
			{
				boolean flagForLoop = True;
				int idForRemove;
				int finish;
				while (flagForLoop) {
					if (company.numOfDrivers == 0 && company.numOfInspectors == 0)
					{
						printf("There are no workers!\n");
						break;
					}
					printWorkerArray(&company);
					printf("Choose which license Number you want to remove:\n");

					if (scanf("%d", &idForRemove) != 1)
					{
						printf("Bad input.\n");
						break;
					}

					removeWorker(&company, idForRemove);
					if (company.numOfDrivers == 0 && company.numOfInspectors == 0)
					{
						break;
					}
					printf("Do you wish to continue removing? (1-yes/0-no)\n");

					if (scanf("%d", &finish) != 1)
					{
						printf("Bad input.\n");
						break;
					}
					if (finish == 1)
					{
						//nothing
					}
					else if (finish == 0)
					{
						flagForLoop = False;
					}
					else
					{
						printf("Bad input.\n");
					}
				}
			}

			else if (opt == -1)
			{
				break;
			}
			else
			{
				printf("Bad input, Please try again.\n");
				cleanbuffer();
			}
			break;

		case 3:
			printMenuCase3();
			if (scanf("%d", &opt) != 1)
			{
				printf("Bad input.\n");
				break;
			}
			if (opt == 1)
			{

				boolean flagForLoop = True;
				int finish;
				while (flagForLoop) {

					addCityToCompany(&company);
					printf("Do you wish to continue adding cities? (1-yes/0-no)\n");

					if (scanf("%d", &finish) != 1)
					{
						printf("Bad input.\n");
						break;
					}
					if (finish == 1)
					{
						//nothing

					}
					else if (finish == 0)
					{
						flagForLoop = False;
					}
					else
					{
						printf("Bad input.\n");

					}
				}
			}
			else if (opt == 2)
			{
				if (company.numOfActiveCities == 0)
				{
					printf("There are no cities!\n");
					break;
				}
				boolean flagForLoop = True;
				int finish;
				int choice = 1;
				char cTemp[CITYCODE + 1];
				char* pchar = cTemp;
				while (flagForLoop) {

					cleanbuffer();
					printCities(&company);
					printf("Enter city code to change the rank of the city\n");

					getCityCode(pchar);

					updateCity(&company, pchar, choice);
					printf("Do you wish to continue to updating cities? (1-yes/0-no)\n");

					if (scanf("%d", &finish) != 1)
					{
						printf("Bad input.\n");
						break;
					}
					if (finish == 1)
					{
						//nothing
					}
					else if (finish == 0)
					{
						flagForLoop = False;
					}
					else
					{
						printf("Bad input.\n");

					}
				}
			}
			else if (opt == 3)
			{
				if (company.numOfActiveCities == 0)
				{
					printf("There are no cities!\n");
					break;
				}
				boolean flagForLoop = True;

				int choice = 2;
				char cTemp[CITYCODE + 1];
				char* pchar = cTemp;
				cleanbuffer();
				int finish;
				while (flagForLoop)
				{
					printCities(&company);
					printf("Enter city code to remove the city\n");
					getCityCode(pchar);
					updateCity(&company, pchar, choice);

					printf("Do you wish to continue to removing cities? (1-yes/0-no)\n");

					if (scanf("%d", &finish) != 1)
					{
						printf("Bad input.\n");
						break;
					}
					if (finish == 1)
					{
						//nothing
					}
					else if (finish == 0)
					{
						flagForLoop = False;
					}
					else
					{
						printf("Bad input.\n");
					}
				}
			}
			else if (opt == -1)
			{
				break;
			}
			else
			{
				printf("Bad input, Please try again.\n");
				cleanbuffer();
			}
			break;

		case 4:
			printMenuCase4();
			if (scanf("%d", &opt) != 1)
			{
				printf("Bad input.\n");
				break;
			}
			if (opt == 1)
			{
				if (company.numOfActiveCities == 0)
				{
					printf("There are no active cities!\n");
					break;
				}
				char cTemp[CITYCODE + 1];
				char* pchar = cTemp;
				boolean flagForLoop = True;
				int finish;
				while (flagForLoop)
				{
					PRINT_INFORMATION_TRAIN_STATION();
					printCities(&company);
					printf("Choose a city code to connect a station\n");
					cleanbuffer();
					getCityCode(pchar);
					int choice = 0;
					updateCityTrainStation(&company, pchar, choice);

					printf("Do you wish to continue to adding train stations to a city? (1-yes/0-no)\n");
					if (scanf("%d", &finish) != 1)
					{
						printf("Bad input.\n");
						break;
					}
					if (finish == 1)
					{
						//nothing
					}
					else if (finish == 0)
					{
						flagForLoop = False;
					}
					else
					{
						printf("Bad input.\n");
					}
				}
			}

			else if (opt == 2)
			{
				if (company.numOfActiveCities == 0)
				{
					printf("there is no active cities!\n");
					break;
				}
				char cTemp[CITYCODE + 1];
				char* pchar = cTemp;
				boolean flagForLoop = True;
				PRINT_INFORMATION_TRAIN_STATION();
				int finish;
				while (flagForLoop)
				{
					printCities(&company);
					printf("Choose the city code to update:\n");
					cleanbuffer();
					getCityCode(pchar);
					updateTrainStationInCity(&company, pchar);
					printf("Do you wish to update platforms in train stations?(1-yes/0-no)\n");

					if (scanf("%d", &finish) != 1)
					{
						printf("Bad input.\n");
						break;
					}
					if (finish == 1)
					{
						//nothing
					}
					else if (finish == 0)
					{
						flagForLoop = False;
					}
					else
					{
						printf("Bad input.\n");
					}
				}
			}
			else if (opt == 3)
			{
				if (company.numOfActiveCities == 0)
				{
					printf("There are no active cities!\n");
					break;
				}
				int finish;
				boolean flagForLoop = True;
				while (flagForLoop)
				{
					selectTrainToAddToTrainStation(&company);
					printf("Do you wish to continue adding trains to a train station? (1-yes/0-no)\n");

					if (scanf("%d", &finish) != 1)
					{
						printf("Bad input.\n");
						break;
					}
					if (finish == 1)
					{
						//nothing
					}
					else if (finish == 0)
					{
						flagForLoop = False;
					}
					else
					{
						printf("Bad input.\n");
					}
				}
			}
			else if (opt == 4)
			{
				if (company.numOfActiveCities == 0)
				{
					printf("There are no active cities!\n");
					break;
				}
				char cTemp[CITYCODE + 1];
				char* pchar = cTemp;
				int finish;
				boolean flagForLoop = True;
				while (flagForLoop)
				{
					printCities(&company);
					printf("Choose the city code to update:\n");
					cleanbuffer();
					getCityCode(pchar);
					int choice = 1;
					updateCityTrainStation(&company, pchar, choice);

					printf("Do you wish to continue removing train stations from a city? (1-yes/0-no)\n");
					if (scanf("%d", &finish) != 1)
					{
						printf("Bad input.\n");
						break;
					}
					if (finish == 1)
					{
						//nothing
					}
					else if (finish == 0)
					{
						flagForLoop = False;
					}
					else
					{
						printf("Bad input.\n");
					}

				}
			}
			else if (opt == -1)
			{
				break;
			}
			else
			{
				printf("Bad input, Please try again.\n");
				cleanbuffer();
			}
			break;

		case 5:
			printMenuCase5();
			int result = 0;
			boolean flagForLoop = 1;
			int opt = 0;
			int finish;
			while (flagForLoop)
			{
				result = addRoute(&company);
				if (result == 0)
				{
					printf("Do you want to try again?(1-yes/0-no)\n");
					if (scanf("%d", &opt) != 1)
					{
						printf("Bad input.\n");
						break;
					}
					if (opt == 1)
						continue;
					else
						break;
				}

				printf("Do you want to add another route?(1-yes/0-no)\n");
				if (scanf("%d", &finish) != 1)
				{
					printf("Bad input.\n");
					break;
				}
				if (finish == 1)
				{
					//nothing
				}
				else if (finish == 0)
				{
					flagForLoop = False;
				}
				else
				{
					printf("Bad input.\n");
				}
			}
			break;

		case 6:
			printMenuCase6();
			if (scanf("%d", &opt) != 1)
			{
				printf("Bad input.\n");
				break;
			}
			if (opt == 1)
			{
				printf("\nYou have selected to update a train route.\nPlease choose one of the following options:\n");
				printMenuCase6_1();
				if (scanf("%d", &opt) != 1)
				{
					printf("Bad input.\n");
					break;
				}
				if (opt == 1)
				{
					Route* route = selectRoute(&company);
					addTrainStopToRoute(&company, route);
				}
				else if (opt == 2)
				{
					Route* route = selectRoute(&company);
					removeTrainStopFromRoute(&company, route);
				}
				else if (opt == 3)
				{
					updateRouteDriver(&company);
				}
				else if (opt == 4)
				{
					updateRouteInspector(&company);
				}
				else if (opt == -1)
				{
					break;
				}
			}
			else if (opt == 2)
			{
				printf("\nYou have selected to remove a train route.\n");
				Route* route = selectRoute(&company);
				if (route != NULL)
				{
					freeTrainRoute(route);
					company.numOfRoutes--;
					printf("\nThe route has been successfully removed.\n");
				}
			}
			else if (opt == -1)
			{
				break;
			}
			else
			{
				printf("Bad input, Please try again.\n");
				cleanbuffer();
			}
			break;

		case 7:
			printMenuCase7();
			if (scanf("%d", &opt) != 1)
			{
				printf("Bad input.\n");
				break;
			}
			if (opt == 1)
			{
				printCompany(&company);
			}
			else if (opt == 2)
			{
				printTrainRouteInCompany(&company);

			}
			else if (opt == 3)
			{
				char cTemp[CITYCODE + 1];
				char* pchar = cTemp;
				if (company.numOfActiveCities == 0)
				{
					printf("There are no active cities!\n");
					break;
				}

				printCities(&company);
				printf("Choose the city code you wish print it's details\n");
				cleanbuffer();
				getCityCode(pchar);
				printCityChoice(&company, pchar);
			}
			else if (opt == 4)
			{
				printTrainStationArray(&company);
			}
			else if (opt == 5)
			{
				printTrains(&company);

			}
			else if (opt == 6)
			{
				printDriverArray(&company);
			}
			else if (opt == 7)
			{
				printInspectorArray(&company);
			}
			else if (opt == -1)
			{
				break;
			}
			else
			{
				printf("Bad input, Please try again.\n");
				cleanbuffer();
			}
			break;

		case 8:
			printMenuCase8();
			if (scanf("%d", &opt) != 1)
			{
				printf("Bad input.\n");
				break;
			}
			if (opt == 1)
			{
				PRINT_INFORMATION_SORT();
				int optionSort = 0;
				if (scanf("%d", &optionSort) != 1)
				{
					printf("Bad input.\n");
					break;
				}
				if (optionSort == 1)
				{
					if (company.numOfDrivers < 2)
					{
						printf("There are not enough drivers\n");
						break;
					}
					printf("Before sort:\n");
					printDriverArray(&company);
					sortDriversByLicenseType(company.driversArray, company.numOfDrivers);
					printf("After sort:\n");
					printDriverArray(&company);
				}
				else if (optionSort == 2)
				{
					if (company.numOfActiveCities < 2)
					{
						printf("There are not enough cities\n");
						break;
					}
					printf("Before sort:\n");
					printCities(&company);
					sortCitiesByPassengers(company.citiesArray, company.numOfActiveCities);
					printf("After sort:\n");
					printCities(&company);
				}
				else if (optionSort == 3)
				{
					if (company.numOfActiveCities < 2)
					{
						printf("There is not enough cities\n");
						break;
					}
					printf("Before sort:\n");
					printCities(&company);
					sortCitiesByTrains(company.citiesArray, company.numOfActiveCities);
					printf("After sort:\n");
					printCities(&company);
				}
				else
				{
					printf("Bad input, Please try again.\n");
					cleanbuffer();
				}
			}
			else if (opt == 2)
			{
				PRINT_INFORMATION_BSEARCH();
				int optionBsearch = 0;

				if (scanf("%d", &optionBsearch) != 1)
				{
					printf("Bad input.\n");
					break;
				}
				if (optionBsearch == 1)
				{
					if (company.numOfDrivers == 0)
					{
						printf("There are no drivers\n");
						break;
					}
					int LicenseSearch = 0;
					Driver* driver = NULL;
					printf("Enter driver's license number you wish to search search:\n");
					if (scanf("%d", &LicenseSearch) != 1)
					{
						printf("Bad input.\n");
						break;
					}

					sortDriversByLicenseNumber(company.driversArray, company.numOfDrivers);
					driver = searchDriverBylicenseNumber(LicenseSearch, company.driversArray, company.numOfDrivers);
					if (driver != NULL)
					{
						printf("Driver with licenseNumber %d have been found.\n", LicenseSearch);
						printDriver(driver);
					}
					else
					{
						printf("Driver with licenseNumber %d have not been found.\n", LicenseSearch);
					}
				}
				else if (optionBsearch == 2)
				{
					if (company.numOfActiveCities == 0)
					{
						printf("There are no cities.\n");
						break;
					}

					printf("Enter city code to search:\n");
					char cTemp[CITYCODE + 1];
					char* cityCode = cTemp;
					cleanbuffer();
					getCityCode(cityCode);


					City* city = searchCityByCode(company.citiesArray, cityCode, company.numOfActiveCities);

					if (city != NULL)
					{
						printf("City code %s has been found.\n", cityCode);
						printCity(city);
					}
					else
					{
						printf("City code %s has not been found.\n", cityCode);
					}
				}
				else if (optionBsearch == 3)
				{
					if (company.numOfActiveCities == 0)
					{
						printf("There are no cities\n");
						break;
					}
					boolean flagForLoop = 0;
					int trainSerial = 0;
					printTrains(&company);
					printf("Enter train serial to search:\n");
					int check;
					if (scanf("%d", &trainSerial) != 1)
					{
						printf("Bad input.\n");
						break;
					}
					for (int i = 0; i < company.numOfActiveCities; i++)
					{
						check = searchTrainInCity(company.citiesArray[i]->trainStations, trainSerial, company.citiesArray[i]->numOfStations);

						if (check != 0)
						{
							TrainStation* stationTemp = findTrainserial(&company, trainSerial);
							printf("train number %d have been found in city [%s] and in station %s\n", trainSerial, stationTemp->locatedInCity, stationTemp->stationName);
							flagForLoop = 1;
							break;
						}
					}

					if (!flagForLoop)
					{
						printf("Train number %d has not been found\n", trainSerial);
					}
				}
				else
				{
					printf("Bad input, Please try again.\n");
					cleanbuffer();
				}
			}
			else if (opt == -1)
			{
				break;
			}
			else
			{
				printf("Bad input, Please try again.\n");
				cleanbuffer();
			}
			break;

		case 9:
			printMenuCase9();
			if (scanf("%d", &opt) != 1)
			{
				printf("Bad input.\n");
				break;
			}
			if (opt == 1)
			{
				printExpectedPassengers(&company);
			}
			else if (opt == 2)
			{
				printf("choose city to copy from.\n");
				City* cityTemp = selectACity(&company);
				if (cityTemp == NULL) {
					printf("Invalid source city.\n");
					break; // Exit with error
				}
				printf("choose station to copy from.\n");
				TrainStation* tempStation = selectAStation(cityTemp);
				if (tempStation == NULL) {
					printf("Invalid source station.\n");
					free(cityTemp); // Free memory allocated for the city
					break; // Exit with error
				}
				if (!copyTrainStationToCity(&company, tempStation)) {
					printf("Failed to copy train station.\n");
				}
			}
			else if (opt == -1)
			{
				break;
			}
			else
			{
				printf("Bad input, Please try again.\n");
				cleanbuffer();
			}
			break;

		default:
		{
			printf("Bad input, Please try again.\n");
			cleanbuffer();
		}
		}
	}
	return 1;
}