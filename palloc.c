#include "palloc.h"

struct freeblock {
	uint64_t size;
	struct freeblock *next;
};

struct allocblock {
	uint64_t size;
	uint64_t magic;
};

static struct freeblock *free_list;
static void *head;

void init_list(){
	if (!free_list){
		free_list = mmap(NULL, 4096, PROT_READ|PROT_WRITE, MAP_ANON|MAP_PRIVATE,-1,0);
		free_list->size = 4096; //- sizeof(struct freeblock);
		free_list->next = NULL;
		head = free_list;
	}
}

void coalesce(void *ptr){
	struct freeblock *pt = (struct freeblock *)ptr;
	if ((uint64_t)pt+pt->size ==  (uint64_t) pt->next){ //if pt and the next item border, coalesce
		pt->size += pt->next->size; //modify the size of the pointer
		pt->next = pt->next->next; //set the one after next to be the new next
	}
}

void * palloc(int size){
	double ru = ((double)size)/8;
	int sizem = 8*(ceil(ru)+2); //Establish minimum size: Head + min of 8 byte groups
	if (!free_list) //If there's no actual free_list, initialize that actually.
		init_list();
	struct freeblock *worst = NULL;
	struct freeblock *prev = NULL;
	struct freeblock *current = free_list; //init worst, prev, and current, beginning at the start of the free_list;
	if (current->size >= sizem) //If the head is actually valid, use it
		worst = current;
	for (current; current->next; current = current->next){ //for all in the linked list
		if (current->next->size >= sizem && (!worst || current->next->size > worst->size)){ //if it's worse than the current candidate and big enough to be valid, use
			prev = current;
			worst = current->next;
		}
	}
	if (!worst) 
		return NULL;
	if (worst->size < sizem+24){ //If we don't have enough space for a new freeblock
		sizem = worst->size; //allocate all of it
		if (prev) //if not at the beginning of free list
			prev->next = worst->next; //skip us
		else 
			free_list = worst->next;
	} else {
		struct freeblock *newFree; //Generate a new freeblock
		newFree = (struct freeblock *) (sizem + ((uint64_t) worst)); //Place it after the allocated block
		newFree->size = worst->size - sizem; //init new size
		newFree->next = worst->next; //pass it the worst's next
		if (prev) //if not at beginning
			prev->next = newFree; //skip over
		else
			free_list = newFree; //move beginning of free list.}
	}
	struct allocblock *new = (struct allocblock *) worst; //init new block
	new->size = sizem; //set size
	new->magic = 0xBEEF1DAD; //set magic number
	return new+1; 
}

void free(void *pt) {
	pt-=16;
	struct freeblock *newFree; //generate a new freeblock
	newFree = (struct freeblock *) pt;
	newFree->size = ((struct freeblock *)pt)->size;
	if (newFree < free_list){ //If the freeblock is before the list head
		newFree->next = free_list; //put it at the beginning
		coalesce(newFree);
		free_list = newFree;
	} else { //Else go looking for it
		for (struct freeblock *current = free_list; current < newFree; current = current->next){
			if (newFree < current->next||!current->next){ //if newFree lies between current and next, insert it in between
				newFree->next = current->next;
				if (newFree->next)
					coalesce(newFree);
				current->next = newFree;
				coalesce(current);
				return;
			}
		}
	}
}


void walk(){
	struct freeblock *list = free_list;
	for (void *cursor = head; cursor < head+4096; cursor += ((struct allocblock *)cursor)->size){	
		if (cursor != list) {
			struct allocblock *ct = (struct allocblock *)cursor;
			printf("+------------Alloc: %p\n", ct);
			printf("|\t\t\tSize: %ld\n", ct->size);
			printf("|\t\t\tMagic: %lx\n", ct->magic);
		} else {
			printf("+------------Free: %p\n", list);
			printf("|\t\t\tSize: %ld\n", list->size);
			printf("|\t\t\tNext: %p\n", list->next);
			list = list->next;
		}
	}
}
