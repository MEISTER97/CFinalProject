#define _CRT_SECURE_NO_WARNINGS

#include "Inspector.h"

int initInspector(Inspector* inspector)
{
	srand((unsigned int)time(NULL));
	inspector->type = eInspector;
	printf("Enter the name of the inspector:\n");
	char temp[MAX_STR_LEN] = { 0 };
	myGets(temp, MAX_STR_LEN);
	inspector->InspectorName = malloc(strlen(temp) + 1);
	if (inspector->InspectorName == NULL) {
		printf("Memory allocation failed.\n");
		return 0; // Return 0 to indicate failure
	}
	strcpy(inspector->InspectorName, temp);
	// generate random number 1-9999
	inspector->licenseNumber = rand() % 9999 + 1;

	return 1;
}


void printInspector(const Inspector* inspector)
{
	printf("[Inspector detail]\tname: %s\tlicenseNumber: %d\n", inspector->InspectorName, inspector->licenseNumber);
}

void freeInspector(Inspector* inspector)
{
	free(inspector->InspectorName);
}
