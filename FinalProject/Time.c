#define _CRT_SECURE_NO_WARNINGS

#include "Time.h"

const int DAY_MONTHS[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

int initTravelTime(Time* pTime)
{
	pTime->type = eTime;
	if (getCorrectDate(pTime) == 0)
	{
		printf("Error with updating the date!\n");
		return 0;
	}
	if (getCorrectTime(pTime) == 0)
	{
		printf("Error with updating the time!\n");
		return 0;
	}

	return 1;
}

boolean getCorrectDate(Time* pTime)
{
	char time[MAX_STR_LEN];
	int ok = True;

	do {
		printf("\nPlease enter the route's date in the format dd%cmm%cyyyy here: (minimum possible year %d)\t",
			SPECIAL_CHAR1, SPECIAL_CHAR1, MIN_YEAR);
		myGets(time, MAX_STR_LEN);
		ok = checkDate(time, pTime);
		if (!ok)
			printf("Error, try again.\n");
	} while (!ok);

	return True;
}

boolean	checkDate(char* time, Time* pTime)
{
	int day, month, year;
	if (strlen(time) != 10)
		return False;
	if ((time[2] != SPECIAL_CHAR1) || (time[5] != SPECIAL_CHAR1))
		return False;
	if (sscanf(time, "%d%*c%d%*c%d", &day, &month, &year) == EOF)
		return False;
	if (day < 1 || month < 1 || month > 12 || year < MIN_YEAR)
		return False;

	if (day > DAY_MONTHS[month - 1])
		return False;

	pTime->day = day;
	pTime->month = month;
	pTime->year = year;

	return True;
}


boolean getCorrectTime(Time* pTime) {
	char time[MAX_STR_LEN];
	int ok = True;

	do {
		printf("Please enter the route's time in the format hh:mm here:\t");
		fgets(time, MAX_STR_LEN, stdin);
		time[strcspn(time, "\n")] = '\0'; // Remove newline character if present
		ok = checkTime(time, pTime);
		if (!ok)
			printf("Error, try again.\n");
	} while (!ok);

	return True;
}

boolean	 checkTime(char* time, Time* pTime)
{
	int minute, hour;
	if (strlen(time) != 5)
		return False;
	if ((time[2] != SPECIAL_CHAR2))
		return False;
	if (sscanf(time, "%d%*c%d", &hour, &minute) == EOF)
		return False;
	if (minute < 0 || minute > 60 || hour < 0 || hour > 23)
		return False;

	pTime->minute = minute;
	pTime->hour = hour;

	return True;
}

void printTravelTime(const Time* pTime)
{
	printf("Date: ");
	if (pTime->day < 10)
		printf("0%d/", pTime->day);
	else
		printf("%d/", pTime->day);

	if (pTime->month < 10)
		printf("0%d/", pTime->month);
	else
		printf("%d/", pTime->month);

	printf("%d, At: ", pTime->year);

	if (pTime->hour < 10)
		printf("0%d:", pTime->hour);
	else
		printf("%d:", pTime->hour);

	if (pTime->minute < 10)
		printf("0%d\n", pTime->minute);
	else
		printf("%d\n", pTime->minute);
}

void freeTravelTime()
{
	// Nothing to dynamically free here...
}


