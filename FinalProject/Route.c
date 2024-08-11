#include "Route.h"



void printTrainRoute(const Route* route)
{
	printf("\nRoute number %d details:\n", route->routeId);
	printf("Route's train serial number: %d\n", route->train->serialNumber);
	printf("Route's driver name: %s, license number: %d\n", route->driver->DriverName, route->driver->licenseNumber);
	printf("Route's inspector name: %s, license number: %d\n", route->inspector->InspectorName, route->inspector->licenseNumber);
	TrainStation* tempTrainStation = (TrainStation*)route->trainStationsList->head.next->key;
	printf("The route departures from %s station at: ", tempTrainStation->stationName); printTravelTime(route->departureTime);
	tempTrainStation = (TrainStation*)(Find_last_Node(route->trainStationsList)->key);
	printf("And arrives at %s station,", tempTrainStation->stationName);

	printf("List of all the stations in this route: \n");
	L_print(route->trainStationsList);
	printf("\n");
}

void freeTrainRoute(Route* route)
{
	freeTrain(route->train);
	freeDriver(route->driver);
	freeInspector(route->inspector);
	L_free(route->trainStationsList);
	freeTravelTime(route->departureTime);
	free(route);
}