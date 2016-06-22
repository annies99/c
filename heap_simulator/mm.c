#include <stdio.h>
#include <stdlib.h>

#include "memory.h"

extern mem_ptr Heap;

/*
	Simulation of malloc, free, and realloc
	Alec Webb
*/

mem_ptr makenode(mem_ptr track, int new_size){
	mem_ptr temp = (mem_ptr)malloc(sizeof(mem_rec));						//make the ptr
	temp->status = PACK((GET_SIZE(track->status) - ALIGN(new_size)),FREE);	//create status of this pointer
	track->status = PACK(ALIGN(new_size),ALLOCATED);						//update status of previous pointer
	temp->address = (track->address + ALIGN(new_size));						//update the address
	temp->next = NULL;
	temp->previous = NULL;
	
	if(track->next != NULL){//placement inside of list
		temp->previous = track;
		temp->next = track->next;
		temp->next->previous = temp;
		track->next = temp;
	}
	else if(track->next == NULL){//placement at the end of list
		track->next = temp;
		temp->previous = track;	
	}
	return temp;
}

mem_ptr mm_malloc(int size) {
	int new_size = ALIGN(size);//declare variables
	mem_ptr track = Heap;
	int sizeaccum = 0;
	
	if(ALIGN(new_size)>10000){//catch if trying to malloc a size greater than the heap itself
		printf("ERROR: Insufficient heap space for desired allocation\n");
		return NULL;
	}
	while(track->next != NULL && (GET_ALLOC(track->status)!=0 || GET_SIZE(track->status)<=ALIGN(new_size))) {//cycle w/ size constraint
		sizeaccum += GET_SIZE(track->status);//update accumulator
		if(sizeaccum+ALIGN(new_size)==10000){//if equal no need for split
			track->next->status=PACK(ALIGN(new_size),ALLOCATED);
			return;
		}
		if(sizeaccum+ALIGN(new_size)>10000){//if greater print error
			printf("ERROR: Insufficient heap space for desired allocation\n");
			return NULL;
		}
		if((GET_SIZE(track->status) == ALIGN(new_size)) && (GET_ALLOC(track->status)==0)){//if equal no need for split
			track->status=PACK(ALIGN(new_size),ALLOCATED);
			return;
		}
	track = track->next; 	
	}
	makenode(track,new_size);//if there was a need to create more free space
	return track;
}

void mm_free(mem_ptr m) {	
	if(m == NULL){ //in the event the pointer is null
		printf("ERROR: Cannot free empty node\n");
		return;
	}
	if(GET_ALLOC(m->status) == 0){ //in the event the node is already free
		printf("ERROR: Node already free\n");
		return;
	}
	if(m->next != NULL && m->previous !=NULL){//in the event the node is surrounded by nodes
		mem_ptr before = m->previous;
		mem_ptr after = m->next;
		if((GET_ALLOC(before->status) != 0) && (GET_ALLOC(after->status) != 0)){//in the event the node is surrounded by allocated nodes
			m->status = PACK(GET_SIZE(m->status),FREE);
			return;
		}
		if((GET_ALLOC(before->status) != 0) && (GET_ALLOC(after->status) == 0)){//in the event the node after is free
			m->status = PACK(GET_SIZE(after->status)+GET_SIZE(m->status),FREE);
			m->next = after->next;
			free(after);
			return;
		}
		if((GET_ALLOC(before->status) == 0) && (GET_ALLOC(after->status) != 0)){//in the event the node before is free
			before->status = PACK(GET_SIZE(before->status)+GET_SIZE(m->status),FREE);
			before->next = after;
			after->previous = before;
			free(m);
			return;
		}
		if((GET_ALLOC(before->status) == 0) && (GET_ALLOC(after->status) == 0)){//in the event the node is surrounded by free nodes
			before->status = PACK(GET_SIZE(before->status)+GET_SIZE(after->status)+GET_SIZE(m->status),FREE);
			before->next = after->next;
			if(after->next != NULL){//if there exists a connected node
				after->next->previous = before;
			}
			free(after);
			free(m);
			return;
		}
	}
	else if (m->next!=NULL && m->previous == NULL){//in the event the node before is NULL
		mem_ptr after = m->next;
		if((GET_ALLOC(after->status) == 0)){//in the event the node after is free, and m is at beginning.
			m->status = PACK(GET_SIZE(after->status)+GET_SIZE(m->status),FREE);
			m->next = after->next;
			free(after);
			return;
		}
		if((GET_ALLOC(after->status) != 0)){//in the event the node after is allocated, and m is at beginning
			m->status = PACK(GET_SIZE(m->status),FREE);
			return;
		}
	}
	else if (m->previous != NULL && m->next == NULL){//in the event the node after is NULL
		mem_ptr before = m->previous;
		if((GET_ALLOC(before->status) == 0)){//in the event the node before is free
			before->status = PACK(GET_SIZE(before->status)+GET_SIZE(m->status),FREE);
			free(m);
			return;
		}
		if((GET_ALLOC(before->status) != 0)){//in the event the node before is allocated
			m->status = PACK(GET_SIZE(m->status),FREE);
			return;
		}
	}
	else if (m->previous == NULL && m->next == NULL){//everything surrounding is null
		m->status = PACK(GET_SIZE(m->status),FREE);
		return;
	}	
}

mem_ptr mm_realloc(mem_ptr m, int size) {
    int new_size = ALIGN(size);
	
	if(m == NULL){//print error when NULL
		printf("ERROR: Cannot free empty node\n");
		return;
	}
	if(ALIGN(new_size) == GET_SIZE(m->status)){//do nothing when reallocating the same size
		return m;
	}
	if(ALIGN(new_size) < GET_SIZE(m->status)){//in the event the node can be split
		mem_ptr split = (mem_ptr)malloc(sizeof(mem_rec));
		int splitsize = GET_SIZE(m->status) - ALIGN(new_size);
		
		m->status = PACK(ALIGN(new_size),ALLOCATED);	//set properties of nodes
		split->status = PACK(ALIGN(splitsize),FREE);
		split->address = (m->address + ALIGN(new_size));
		
		split->next = m->next;//adjust for position
		m->next = split;
		split->previous = m;
		
		if(split->next != NULL){ //if there is a node after the split node
			mem_ptr aftersplit = split->next;
			if(GET_ALLOC(aftersplit->status) == 0){ //if that node is free, coalesce it
				split->status = PACK(GET_SIZE(aftersplit->status) + GET_SIZE(split->status),FREE);
				split->next = aftersplit->next;
				if(aftersplit->next != NULL){ //make sure the pointers are correct
					aftersplit->previous = split;
				}
				free(aftersplit);
			}
			if(GET_ALLOC(aftersplit->status) != 0){ //if that node is allocated
				aftersplit->previous = split;
			}
		}
		return m;
	}
	if(ALIGN(new_size) > GET_SIZE(m->status)){//in the event the size is bigger than the current node
		if(m->next != NULL){//check if there is a free space after to expand into
		mem_ptr after = m->next;
			if(GET_ALLOC(after->status)==0){//expand that mammerjammer
				if(GET_SIZE(after->status) + GET_SIZE(m->status) > ALIGN(new_size)){ //in the event there is enough room to expand
					int m_size = GET_SIZE(m->status); //store the size
					m->status = PACK(ALIGN(new_size),ALLOCATED);//allocate the new size
					after->status = PACK(GET_SIZE(after->status) - (ALIGN(new_size)-m_size),FREE); //determine the size
					after->address = after->address + (ALIGN(new_size)-m_size);	//reset the address
					return m;
				}
				else if(GET_SIZE(after->status) + GET_SIZE(m->status) == ALIGN(new_size)){ //in the event it is the same size as both blocks
					m->status = PACK(ALIGN(new_size),ALLOCATED);//allocate the new size
					if(after->next !=NULL){//in the event there is a node following
						m->next = after->next;
						after->next->previous = m;
						free(after);
						return m;
					}
					if(after->next == NULL){//in the event there is no node following
						m->next = after->next;
						free(after);
						return m;
					}
				}
				else{//in the event there is not enough space in the free node following
					mm_free(m);
					mm_malloc(ALIGN(new_size));
					return;
				}
			}
			if(GET_ALLOC(after->status) !=0){//if cannot expand, free this block and run a malloc on it
				mm_free(m);
				mm_malloc(ALIGN(new_size));
				return;
			}
		}
		else if(m->next == NULL){//if there does not exist a following block, free this block and run a malloc on it
			if(m->previous != NULL){//in the event there is a block previous
				m->previous->next = m->next;
			}
			mm_free(m);
			mm_malloc(ALIGN(new_size));
			return;
		}
	}  
   return NULL;//if everything fails
}