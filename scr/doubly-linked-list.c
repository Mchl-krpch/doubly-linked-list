#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "doubly-linked-list.h"

int main () {
	list *Tokens = newList (25);


	printList (Tokens);
	for (unsigned newEl = 0; newEl < 10; newEl++) {
		InsertAfter (newEl, Tokens, 7);
		getchar ();
		printList (Tokens);
	}

	drowCell ();
	printList (Tokens);


	return 0;
}






// ################################################

static inline unsigned listNext (list *list, unsigned index) {
	return list->cells[index].next;
}


static inline unsigned listPrev (list *list, unsigned index) {
	return list->cells[index].prev;
}

// #want: to make function ...{After/before} as function-toggle
void InsertAfter (int index, list *list, int value) {
	assert (list  != nullptr);

	// #if the user enters the index of
	// #a free cell, then the program will
	// #insert the token at the first free
	// #index after the tail
	// if (list->cells[index].prev == -1) {
	// 	index = free;
	// }

	int freeIndex = FindEmpty (list);

	list->cells[freeIndex].data.num_d = value;

	list->cells[freeIndex].prev = index;
	list->cells[listNext (list, index)].prev = freeIndex;

	list->cells[freeIndex].next = list->cells[index].next;
	list->cells[index].next = freeIndex;

	list->size++;

	// if (list->cells[freeIndex].next == 0 && list->cells[freeIndex].prev != -1) {
	// 	list->tail = freeIndex;
	// }

	// if (list->cells[freeIndex].prev == 0) {
	// 	list->head = freeIndex;
	// }

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
			List->cells[el].next = 0;
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
	if (el == list->head) {printf ("<head ");}
	if (el == list->tail) {printf ("<tail ");}
	if (el == list->free) {printf ("<free ");}
	printf ("\n");
	}
	return;
}


void drowCell () {
	FILE *viz = fopen ("viz.dot", "w");
	fprintf (viz, "graph G {\n");
	fprintf (viz, "size=\"8.2, 8.2\"\n");

	// fprintf (viz, "a->b\n");
	fprintf (viz, FILL_CELL());

	fprintf (viz, "}\n");

	fclose (viz);
	system ("dot viz.dot -T png -o viz.png");
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