/********************************************/
/*   list.h                                 */
/*   a dynamic linked list with a header   */
/********************************************/


#ifndef _LIST_
#define _LIST_

#include "Definitions.h"
#include "TrainStation.h"


/*** Definitions ***/


// List
typedef struct {
	NODE head;
}LIST;


/*** Function prototypes ***/

boolean L_init(LIST* pList);					// create new list

NODE* L_insert(NODE* pNode, TrainStation* Value);	// add new node after *pNode

boolean L_delete(NODE* pNode);					// erase node after *pNode

NODE* L_find(NODE* pNode, Data Value);		// return a pointer to the node 

TrainStation* L_find_by_serial_number(NODE* pNode, int serialNumber); // return a pointer to the node

boolean L_free(LIST* pList);					// free list memory

int L_print(const LIST* pList);					// print the list content

int L_short_print(LIST* pList);				// print a short version of the data

NODE* Find_last_Node(LIST* pList);			// returns the last node of the list

#endif
