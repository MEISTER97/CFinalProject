#define _CRT_SECURE_NO_WARNINGS

#include "City.h"



int initCity(City* city)
{
    boolean flag = True;
    city->type = 0;
    char temp[MAX_STR_LEN] = { 0 };

    while (flag)
    {
        flag = False;
        printf("Enter city Code(3 Upper Letters):\n");
        myGets(temp, MAX_STR_LEN);

        if (strlen(temp) != CITYCODE) {
            // Check if input length matches CITYCODE
            printf("Error: City code must be exactly 3 characters.\n");
            flag = True;
            continue;
        }
        for (int i = 0; i < CITYCODE; i++)
        {
            if (isupper(temp[i]) == 0)
            {
                printf("Need to be upper case letter\n");
                flag = True;
                break;
            }
        }


        strncpy(city->cityCode, temp, CITYCODE);
        city->cityCode[CITYCODE] = '\0';

    }

    printf("Enter City name:\n");

    myGets(temp, MAX_STR_LEN);

    city->name = malloc((sizeof(char)+1) * strlen(temp));
    if (city->name == NULL) {
        free(city->name);
    return 0;
}
    strncpy(city->name, temp, strlen(temp));
    city->name[strlen(temp)] = '\0';



    int answer = -1;
    flag = True;
    while (flag) {
        printf("Enter City Rank:\n");
        printf("1)AlphaPlus\n2)Alpha\n3)BetaPlus\n4)Beta\n");
        if (scanf("%d", &answer) != 1)
        {
            printf("Bad input.\n");
            return 0;
        }

        if (answer > 4 || answer < 1)
        {
            printf("You have entered wrong input try again\n");
            flag = True;
        }
        else {
            flag = False;

        }
    }
    city->rank = answer - 1;
    city->trainStations = NULL;

    city->numOfStations = 0;

    return 1;
}

int changeCityRank(City* city)
{
    int answer = -1;
    boolean flag = True;
    printf("The city's currently rank is: [%s]\n", CityRankType[city->rank]);


    while (flag) {
        printf("Enter City Rank:\n");
        printf("1)AlphaPlus\n2)Alpha\n3)BetaPlus\n4)Beta\n");
        if (scanf("%d", &answer) != 1)
        {
            printf("Bad input.\n");
            return 0;
        }

        if (answer > 4 || answer < 1)
        {
            printf("You have entered wrong input try again\n");
            flag = True;
        }
        else {
            flag = False;

        }
    }
    city->rank = answer - 1;
    printf("The city Rank have change to [%s]\n", CityRankType[city->rank]);

    return 1;
}

void initTrainStations(City* city, TrainStation* trainStation, const int numOfStations)// trainStation is a pointer to a train station
{

    if (trainStation == NULL)
    {
        printf("Error: trainStation pointer is NULL.\n");
        return;
    }

    // Initialize trainStation properties
    trainStation->type = eTrainStation;

    // Loop that sets a serial number:
    boolean badSerialNumber = True;
    int tempSerialNumber;
    while (badSerialNumber)
    {
        badSerialNumber = False;
        srand((unsigned int)time(NULL));
        // generate random 1-9999
        tempSerialNumber = rand() % 9999 + 1;
        // Check if there is already a train with the same serial number
        for (int i = 0; i < numOfStations; i++)
        {
            if (city->trainStations[i]->stationSerialNumber == tempSerialNumber)
            {
                badSerialNumber = True;
                break;
            }
        }
    }
    trainStation->stationSerialNumber = tempSerialNumber;

    // Get train station name:
    char tempName[MAX_STR_LEN] = { 0 };
    printf("Enter the station's name: \n");
    myGets(tempName, MAX_STR_LEN);
    trainStation->stationName = malloc(strlen(tempName) + 1);
    if (trainStation->stationName == NULL) {
        printf("Error allocating memory for train station name.\n");
        return; // Indicate failure
    }
    strncpy(trainStation->stationName, tempName, strlen(tempName));
    trainStation->stationName[strlen(tempName)] = '\0';

    // Set train station type:
    boolean flag = True;
    int answer;
    while (flag) {
        printf("Please choose one of the following options: 0 - FastPassenger, 1 - LightPassenger, 2 - Metro, 3 - Cargo\n");
        if (scanf("%d", &answer) != 1)
        {
            printf("Bad input.\n");
            return;
        }
        if (answer < 0 || answer > 3)
        {
            printf("You have selected a wrong choice, try again.\n");
            continue;
        }
        else
            flag = False;
    }
    trainStation->trainStationType = answer;

    // Set the expected number of passengers
    switch (city->rank)
    {
    case AlphaPlus:
    {
        trainStation->expectedNumOfPassengers = rand() % MAX_ALPHAPLUS + MIN_ALPHAPLUS;
        break;
    }
    case Alpha:
    {
        trainStation->expectedNumOfPassengers = rand() % MAX_ALPHA + MIN_ALPHA;
        break;
    }
    case BetaPlus:
    {
        trainStation->expectedNumOfPassengers = rand() % MAX_BETAPLUS + MIN_BETAPLUS;
        break;
    }
    case Beta:
    {
        trainStation->expectedNumOfPassengers = rand() % MAX_BETA + MIN_BETA;
        break;
    }
    }

    printf("expected passenger in train station:%d\n", trainStation->expectedNumOfPassengers);

    // Set in which city the station is located in:
    trainStation->locatedInCity = city->name;

    trainStation->numOfPlatforms = 0;
    trainStation->platforms = NULL;
    // Set the number of platforms
    trainStation->numOfActiveTrains = 0;
    city->trainStations[numOfStations] = trainStation;
}

int addTrainStation(City* city)
 {
    if (city->rank==0&&city->numOfStations== MAX_STATIONSALPHAPLUS)
    {
        printf("Error, city is already with 5 stations.\n");
        return 0;
    }
    if (city->rank == 1 && city->numOfStations == MAX_STATIONSALPHA)
    {
        printf("Error, city is already with 3 stations.\n");
        return 0;
    }
    if (city->rank == 2 && city->numOfStations == MAX_STATIONSBETAPLUS)
    {
        printf("Error, city is already with 2 stations.\n");
        return 0;
    }
    if (city->rank == 3 && city->numOfStations == MAX_STATIONSBETA)
    {
        printf("Error, city is already with 1 station.\n");
        return 0;
    }

    // Reallocate memory for the train station pointer array
    TrainStation** tempTrainStationArray = (TrainStation**)realloc(city->trainStations, (city->numOfStations + 1) * sizeof(TrainStation*));
    if (tempTrainStationArray == NULL) {
        printf("Error reallocating memory for train stations.\n");
        free(tempTrainStationArray);
        return 0;
    }
    city->trainStations = tempTrainStationArray;

    // Allocate memory for the new train station structure
    TrainStation* tempTrainStation = (TrainStation*)malloc(sizeof(TrainStation));
    if (tempTrainStation == NULL) {
        printf("Error allocating memory for train station.\n");
        return 0;
    }

    initTrainStations(city, tempTrainStation, city->numOfStations);

    city->trainStations[city->numOfStations] = tempTrainStation;

    // Increment the number of stations
    city->numOfStations++;

    return 1;
}

int removeTrainStation(City* city)
{
    printTrainStationInCity(city);
    if (city->numOfStations == 0)
        return 0;
    printf("Choose a train station to remove:\n");
    int choice;
    if (scanf("%d", &choice) != 1)
    {
        printf("Bad input.\n");
        return 0; // Return an error code
    }

    for (int i = 0; i < city->numOfStations; i++)
    {
        if (city->trainStations[i]->stationSerialNumber == choice)
        {
            // Free the active trains in the train station
            for (int j = 0; j < city->trainStations[i]->numOfActiveTrains; j++)
            {
                freeTrain(city->trainStations[i]->platforms[j]);
            }

            // Free the train station itself
            freeTrainStation(city->trainStations[i]);

            // Shift the remaining train stations to fill the gap
            for (int k = i; k < city->numOfStations - 1; k++)
            {
                city->trainStations[k] = city->trainStations[k + 1];
            }

            // Decrease the count of train stations
            city->numOfStations--;

            // Resize the train station array
            TrainStation** temp = realloc(city->trainStations, city->numOfStations * sizeof(TrainStation*));
            if (temp == NULL)
            {
                printf("error allocating memory");
                return 0;
            }
            city->trainStations = temp;
            
            return 1; // Successfully removed the train station
        }
    }

    printf("Train station with serial number %d not found.\n", choice);
    return 0; // Train station not found
}


int compareCityCode(const void* a, const void* b)
{
    const City* cityA = *(const City**)a;
    const City* cityB = *(const City**)b;

   return strcmp(cityA->cityCode, cityB->cityCode);
}


int compareCityByCodeSearch(const void* key, const void* element)
{
    const char* searchCode = (const char*)key;
    const City* city = *(const City**)element;

    return strcmp(searchCode, city->cityCode);
}


City* searchCityByCode(City** cityArray, const char* cityCode, const int numOfCities)
{
    // Sort the array of City pointers by city code
    qsort(cityArray, numOfCities, sizeof(City*), compareCityCode);
        
    // Search for the dummy City object in the sorted array
    City** foundCityPtr = (City**)bsearch(cityCode, cityArray, numOfCities, sizeof(City*), compareCityByCodeSearch);

    if (foundCityPtr == NULL) {
        printf("City with code %s not found.\n", cityCode);
        return NULL; // Or any other error code indicating that the city was not found
    }

    return *foundCityPtr;

}



void printCity(const City* city)
{
    if (city->numOfStations == 0)
    {
        printf("[City % s - % s]\t(rank: % s)\t\n", city->name, city->cityCode, CityRankType[city->rank]);
        printf("there is no stations at the city!\n");

    }
    else
    {
    
    printf("[City %s - %s]\t(rank: %s)\tnumber of stations in city: %d\n", city->name, city->cityCode, CityRankType[city->rank], city->numOfStations);

    }

    
}

void printTrainStationInCity(const City* city)
{
    if (city->numOfStations == 0)
    {
        printf("[City % s - % s]\t(rank: % s)\t\n", city->name, city->cityCode, CityRankType[city->rank]);
        printf("there is no stations at the city!\n");
    }
    else
    {
        for (int i = 0; i < city->numOfStations; i++)
        {
            printTrainStation(city->trainStations[i]);

        }
    }

}

void printCityDetail(const City* city)
{

    for (int i = 0; i < city->numOfStations; i++)
    {
        printTrainStation(city->trainStations[i]);
        for (int j = 0; j < city->trainStations[i]->numOfActiveTrains; j++)
            printTrain(city->trainStations[i]->platforms[j]);
       
    }

}

void freeCity(City* city)
{
    free(city->name);
    // Free memory for each TrainStation
    for (int i = 0; i < city->numOfStations; i++)
    {
        freeTrainStation(city->trainStations[i]);
    }

    // Free memory for the array of TrainStation pointers
    free(city->trainStations);
}

void getCityCode(char* cityCode)
{
    char temp[MAX_STR_LEN];
    int validInput;

    do {
        printf("Enter city code (3 Upper Letters): ");
        fgets(temp, sizeof(temp), stdin);
        temp[strcspn(temp, "\n")] = '\0'; // Remove trailing newline if present

        // Check input length
        if (strlen(temp) != CITYCODE) {
            printf("Error: City code must be exactly 3 characters.\n");
            validInput = 0;
            continue;
        }

        // Check if all characters are uppercase letters
        validInput = 1;
        for (int i = 0; i < CITYCODE; i++) {
            if (!isupper(temp[i])) {
                printf("Error: City code must consist of uppercase letters only.\n");
                validInput = 0;
                break;
            }
        }
    } while (!validInput);

    // Copy the validated city code to the output parameter
    strncpy(cityCode, temp, CITYCODE);
    cityCode[CITYCODE] = '\0';
}

TrainStation* searchTrainIntrainstation(City* pCity, const int serial)
{
    for (int i = 0; i < pCity->numOfStations; i++)
    {

        for (int j = 0; j < pCity->trainStations[i]->numOfActiveTrains; j++)
            if (pCity->trainStations[i]->platforms[j]->serialNumber == serial)
                return pCity->trainStations[i];

    }

    return NULL;
}

