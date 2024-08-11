/**************/
/*   list.c   */
/**************/


#include <stdio.h>
#include <stdlib.h>
#include "list.h"


//////////////////////////////////////////
// Init
// Aim:		create new list
// Input:	pointer to the list structure
// Output:	TRUE if succeeded
//////////////////////////////////////////
boolean L_init(LIST* pList)
{
	if (pList == NULL) return False;	// no list to initialize

	pList->head.next = NULL;
	return True;
}


/////////////////////////////////////////////////////////////////
// Insert
// Aim:		add new node
// Input:	pointer to the node BEFORE the place for the new one
//			a value to be stored in the new node
// Output:	pointer to the new node
/////////////////////////////////////////////////////////////////
NODE* L_insert(NODE* pNode, TrainStation* Value)
{
	NODE* tmp;

	if (!pNode) return NULL;

	tmp = (NODE*)malloc(sizeof(NODE));	// new node

	if (tmp != NULL) {
		tmp->key = Value;
		tmp->next = pNode->next;
		pNode->next = tmp;
	}
	return tmp;
}


//////////////////////////////////////////////////////////////
// Delete
// Aim:		erase node
// Input:	pointer to the node BEFORE the node to be deleted 
// Output:	TRUE if succeeded
//////////////////////////////////////////////////////////////
boolean L_delete(NODE* pNode)
{
	NODE* tmp;

	if (!pNode || !(tmp = pNode->next)) return False;

	pNode->next = tmp->next;
	free(tmp);
	return True;
}


/////////////////////////////////////////////////////////
// Find
// Aim:		search for a value
// Input:	pointer to the node to start with 
//			a value to be found
// Output:	pointer to the node containing the Value
/////////////////////////////////////////////////////////
NODE* L_find(NODE* pNode, Data Value)
{
	NODE* tmp;

	if (!pNode) return NULL;

	for (tmp = pNode; tmp && (tmp->key != Value); tmp = tmp->next);
	return tmp;
}

/////////////////////////////////////////////////////////
// Find by serial number
// Aim:		search for a value
// Input:	pointer to the node to start with 
//			a train station serial number to be found
// Output:	pointer to the node containing the Value
/////////////////////////////////////////////////////////
TrainStation* L_find_by_serial_number(NODE* pNode, int serialNumber)
{
	NODE* tmp;

	if (!pNode) return NULL;

	for (tmp = pNode; tmp; tmp = tmp->next)
	{
		if ((((TrainStation*)(tmp->key))->stationSerialNumber) == serialNumber)
			return tmp->key;
	}
	return NULL;
}


////////////////////////////////////////////////
// Free (additional function)
// Aim:		free the list memory
// Input:	pointer to the list structure
// Output:	TRUE if succeeded
////////////////////////////////////////////////
boolean L_free(LIST* pList)
{
	NODE* tmp;

	if (!pList) return False;

	for (tmp = &(pList->head); L_delete(tmp); );
	return True;
}


////////////////////////////////////////////////
// Print (additional function)
// Aim:		print the list content 
// Input:	pointer to the list structure
// Output:	a number of the printed elements
////////////////////////////////////////////////
int L_print(const LIST* pList)
{
	NODE* tmp;
	int		c = 0;

	if (!pList) return 0;

	printf("\n");
	for (tmp = pList->head.next; tmp; tmp = tmp->next, c++)
		printTrainStation(tmp->key);
	printf("\n");
	return c;
}

////////////////////////////////////////////////
// Print (additional function)
// Aim:		print the list content with short train station information
// Input:	pointer to the list structure
// Output:	a number of the printed elements
////////////////////////////////////////////////
int L_short_print(LIST* pList)
{
	NODE* tmp;
	int		c = 0;

	if (!pList) return 0;

	printf("\n");
	for (tmp = pList->head.next; tmp; tmp = tmp->next, c++)
		printTrainStationInList(tmp->key);
	printf("\n");
	return c;
}

/////////////////////////////////////////////////////////
// Find_last_Node
// Aim:		search for the last node in the list
// Input:	pointer to the list structure
// Output:	pointer to the last node
/////////////////////////////////////////////////////////
NODE* Find_last_Node(LIST* pList)
{
	NODE* tmp = pList->head.next;

	while (tmp->next != NULL)
		tmp = tmp->next;


	return tmp;
}
