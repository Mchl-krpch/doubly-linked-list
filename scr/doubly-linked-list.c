#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "doubly-linked-list.h"

int main () {
	list *Tokens = newList (25);

	printList (Tokens);

	// printList (Tokens);
	for (unsigned newEl = 3; newEl < 8; newEl++) {
		printf ("\n\nINSERTING AFTER: %d\n", newEl);
		InsertAfter (newEl, Tokens, 7);
		// getchar ();
		printList (Tokens);
	}

	printf ("\n\nINSERTING AFTER: %d\n", 3);
	InsertAfter (2, Tokens, 666);
	printList (Tokens);
	InsertAfter (2, Tokens, 666);
	printList (Tokens);
	InsertAfter (2, Tokens, 666);
	printList (Tokens);
	InsertAfter (2, Tokens, 666);
	printList (Tokens);

	drowCell ();
	return 0;
}






// ################################################

static inline unsigned listNext (list *list, unsigned index) {
	return list->cells[index].next;
}


static inline unsigned listPrev (list *list, unsigned index) {
	return list->cells[index].prev;
}


int FindEmpty (list *list) {
	assert (list != nullptr);

	// #change capacity to find new empty cells
	if (list->cells[list->free].next == -2) {
		ChangeCapacity (list, list->capacity * INCREASE_COEF);
	}

	int save_free = list->free;
	list->free = list->cells[list->free].next;
	return save_free;
}


// #want: to make function ...{After/before} as function-toggle
void InsertAfter (int index, list *list, int value) {
	assert (list  != nullptr);

	int freeIndex = FindEmpty (list);
	list->cells[freeIndex].data.num_d = value;
		
	if (list->cells[index].prev < 0) {							// if we insert by position of free 
		printf ("index is out of range of list\n");
		printf ("empty: %u, index: %u\n", list->free, index);
		printf ("freeIndex: %u\n", freeIndex);
		list->cells[freeIndex].next = list->free;

		if (freeIndex == list->tail) {
			list->cells[freeIndex].next = -2;
		}

		if (list->cells[freeIndex].prev > -2) {
			list->cells[list->tail].next = freeIndex;
			list->cells[freeIndex].prev = list->tail;
			list->tail = freeIndex;
			list->cells[freeIndex].next = -2;
		}
	}
	else {														// insert after index in list
		printf ("[IN] empty: %u, index: %u\n", list->free, index);
		printf ("[IN] freeIndex: %u\n", freeIndex);

		list->cells[freeIndex].data.num_d = value;

		list->cells[freeIndex].prev = index;
		list->cells[listNext (list, index)].prev = freeIndex;

		list->cells[freeIndex].next = list->cells[index].next;
		list->cells[index].next = freeIndex;
	}

	list->size++;
	return;
}


struct list *newList (unsigned capacity) {
	struct list *List = (list *)calloc (1, sizeof (list));
	List->cells = (Token *)calloc (capacity, sizeof (Token));

	List->head     = 0;
	List->tail     = 0;
	List->free     = 0;

	List->capacity = capacity;

	for (int el = 0; el < capacity; el++) {
		List->cells[el].prev = (el == 0) ? -2 : - 1;
		List->cells[el].data = {.lexem = (char *)calloc (100, sizeof (char))};
		List->cells[el].data.num_d = 0;
		if (el == capacity - 1) {
			List->cells[el].next = -2;
		}
		else if (el == 0) {
			List->cells[el].next = 1;
		}
		else {
			List->cells[el].next = el + 1;
		}
	}
	return List;
}



void ChangeCapacity (list *list, unsigned capacity) {
	assert (list != nullptr);

	list->cells = (Token *)realloc (list->cells, capacity * sizeof (Token));

	for (unsigned el = list->capacity; el < capacity; el++) {
		list->cells[el].prev = -1;
		list->cells[el].data.lexem = (char *)calloc (100, sizeof (char));
		list->cells[el].data.num_d = 0;
		list->cells[el].next = (el == capacity - 1) ? -2 : el + 1;
	}

	list->capacity *= INCREASE_COEF;

	return;
}


void printList (list *list) {
	assert (list != nullptr);

	printf ("\n%-5s| %5s %5s %5s\n\n", "out", "prev", "data", "next");

	// #outputting list
	for (int el = 0; el < list->capacity; el++) {
	printf ("%-5d| %5d %5d %5d",
		el,
		list->cells[el].prev,
		list->cells[el].data.num_d,
		list->cells[el].next);

	// #drow pointers {head, tail, free} 
	if (el == list->head) {printf (" <head");}
	if (el == list->tail) {printf (" <tail");}
	if (el == list->free) {printf (" <free");}
	printf ("\n");
	}
	return;
}


void drowCell () {
	FILE *viz = fopen ("viz/viz.dot", "w");
	fprintf (viz, "graph G {\n");
	fprintf (viz, "size=\"8.2, 8.2\"\n");

	// fprintf (viz, "a->b\n");
	fprintf (viz, FILL_CELL());

	fprintf (viz, "}\n");

	fclose (viz);
	system ("dot viz/viz.dot -T png -o viz/viz.png");
}


void listDtor (list *list) {
	assert (list != nullptr);

	list->head     = 0;
	list->tail     = 0;
	list->free     = 0;
	list->size     = 0;
	list->capacity = 0;

	for (unsigned el = 0; el < list->capacity; el++) {
		free (list->cells[el].data.lexem);
	}

	free (list->cells);
	return;
}

// #vizualisation of list
void drowList (list *list) {
	return;
}