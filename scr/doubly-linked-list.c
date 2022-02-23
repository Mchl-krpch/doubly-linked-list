#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define meow printf("meeeeeeeeow\n");

#include "doubly-linked-list.h"

int main () {
	list *Tokens = newList (8);
	printList_str (Tokens);

	// ChangeCapacity (Tokens, Tokens->capacity * 2);

	// printList (Tokens);
	for (unsigned newEl = 1; newEl < 4; newEl++) {
		printf ("\n\nINSERTING AFTER: %u\n", newEl);
		InsertAfter_str (newEl, Tokens, "MEOW");
		printList (Tokens);
	}

	removeElem (3, Tokens);
	printList_str (Tokens);
	drowList (Tokens);
	return 0;
}

static inline unsigned listNext (list *list, unsigned index) {
	return list->cells[index].next;
}

static inline unsigned listPrev (list *list, unsigned index) {
	return list->cells[index].prev;
}

struct list *newList (unsigned capacity) {
	struct list *List = (list *)calloc (1, sizeof (list));
	List->cells = (Token *)calloc (capacity, sizeof (Token));

	List->head = 0;
	List->tail = 0;
	List->free = 0;

	List->capacity = capacity;

	for (unsigned el = 0; el < capacity; el++) {
		List->cells[el].prev = (el == 0) ? -2 : - 1;
		List->cells[el].data = {.lexem = (char *)calloc (100, sizeof (char))};
		List->cells[el].data.num_d = 0;
		if (el == capacity - 1) {List->cells[el].next = -2;}
		else if (el == 0) {List->cells[el].next = 1;}
		else {List->cells[el].next = el + 1;}
	}
	return List;
}

void ChangeCapacity (list *list, unsigned capacity) {
	assert (list != nullptr);

	list->cells[list->capacity - 1].next = list->capacity;
	list->cells = (Token *)realloc (list->cells, capacity * sizeof (Token));

	for (unsigned el = list->capacity; el < capacity; el++) {
		list->cells[el].prev = -1;
		list->cells[el].data = {.lexem = (char *)calloc (100, sizeof (char))};
		list->cells[el].data.num_d = 0;
		list->cells[el].next = (el == capacity - 1) ? -2 : el + 1;
	}

	list->capacity *= INCREASE_COEF;
	printList (list);
	return;
}

void listDtor (list *list) {
	assert (list != nullptr);

	list->head = 0;
	list->tail = 0;
	list->free = 0;
	list->size = 0;
	list->capacity = 0;

	for (unsigned el = 0; el < list->capacity; el++) {free (list->cells[el].data.lexem);}
	free (list->cells);
	return;
}

int FindEmpty (list *list) {
	assert (list != nullptr);

	// #change capacity to find new empty cells
	if (list->cells[list->free].next == -2) {
		ChangeCapacity (list, list->capacity * INCREASE_COEF);
	}

	unsigned save_free = list->free;
	list->free = list->cells[list->free].next;
	return save_free;
}

void InsertAfter (unsigned index, list *list, int value) {
	assert (list  != nullptr);

	int freeIndex = FindEmpty (list);
	list->cells[freeIndex].data.num_d = value;
		
	// if we insert by position of free 
	if (list->cells[index].prev < 0) {
		printf ("index is out of range of list\n");
		printf ("empty: %d, index: %u\n", list->free, index);
		printf ("freeIndex: %d\n", freeIndex);
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
	// insert after index in list
	else {
		printf ("[IN] empty: %d, index: %u\n", list->free, index);
		printf ("[IN] freeIndex: %d\n", freeIndex);

		list->cells[freeIndex].data.num_d = value;

		list->cells[freeIndex].prev = index;
		list->cells[listNext (list, index)].prev = freeIndex;

		list->cells[freeIndex].next = list->cells[index].next;
		list->cells[index].next = freeIndex;
	}

	list->size++;
	return;
}

void InsertAfter_str (unsigned index, list *list, const char *lexem) {
	assert (list  != nullptr);

	int freeIndex = FindEmpty (list);
	list->cells[freeIndex].data.lexem = (char *)calloc (100, sizeof (char));
	strcpy (list->cells[freeIndex].data.lexem, lexem);
		
	// if we insert by position of free 
	if (list->cells[index].prev < 0) {
		printf ("index is out of range of list\n");
		printf ("empty: %d, index: %u\n", list->free, index);
		printf ("freeIndex: %d\n", freeIndex);
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
	// insert after index in list
	else {
		printf ("[IN] empty: %d, index: %u\n", list->free, index);
		printf ("[IN] freeIndex: %d\n", freeIndex);

		strcpy (list->cells[freeIndex].data.lexem, lexem);

		list->cells[freeIndex].prev = index;
		list->cells[listNext (list, index)].prev = freeIndex;

		list->cells[freeIndex].next = list->cells[index].next;
		list->cells[index].next = freeIndex;
	}

	list->size++;
	return;
}

void removeElem (unsigned el, list *list) {
	assert (list);

	if (list->cells[el].prev == -1) {
		printf ("This element is already empty");
	}
	else {
		if (list->cells[el].prev == 0) {
			list->head = list->cells[el].next;
		}

		if (list->cells[el].next == 0 && list->cells[el].prev != -1) {
			list->tail = list->cells[el].prev;
		}

		list->cells[el].data.num_d = 0;

		list->cells[list->cells[el].next].prev = list->cells[el].prev;
		list->cells[list->cells[el].prev].next = list->cells[el].next;

		list->cells[el].next = list->free;
		list->cells[el].prev = -1;

		list->free = el;

		list->size--;
	}

	return;
}

void printList (list *list) {
	assert (list != nullptr);

	printf ("________________________________________________\n");
	printf ("%-5s| %5s\t %15s  %5s\n", "out", "prev", "data", "next");
	printf ("%-5s  %5s\t %15s  %5s\n", "--", "--", "--", "--");

	// #outputting list
	for (int el = 0; el < (int)list->capacity; el++) {
		printf ("%-5d| %5d\t{%15d} %5d", el, list->cells[el].prev, list->cells[el].data.num_d, list->cells[el].next);
		// #drow pointers {head, tail, free} 
		if (el == list->head) {printf ("   <head");}
		if (el == list->tail) {printf ("   <tail");}
		if (el == list->free) {printf ("   <free");}
		printf ("\n");
	}
	return;
}

void printList_str (list *list) {
	assert (list != nullptr);

	printf ("________________________________________________\n");
	printf ("%-5s| %5s\t %15s  %5s\n", "out", "prev", "data", "next");
	printf ("%-5s  %5s\t %15s  %5s\n", "--", "--", "--", "--");

	// #outputting list
	for (int el = 0; el < (int)list->capacity; el++) {
		if (el < (int)list->size) {
			printf ("%-5d| %5d\t{%15s} %5d", el, list->cells[el].prev, list->cells[el].data.lexem, list->cells[el].next);
		}
		else {
			printf ("%-5d| %5d\t{%15s} %5d", el, list->cells[el].prev, "", list->cells[el].next);
		}
		// #drow pointers {head, tail, free} 
		if (el == list->head) {printf ("   <head");}
		if (el == list->tail) {printf ("   <tail");}
		if (el == list->free) {printf ("   <free");}
		printf ("\n");
	}
	return;
}

void drowList (list *list) {
	assert (list);
	FILE *IR_TOKENS = fopen ("viz/ir-tokens.dot", "w");

	fprintf (IR_TOKENS, "digraph G {\n\tbgcolor=\"#0D1117\"\n\n\t# the design of the nodes themselves\n");
	for (unsigned el = 0; el < list->capacity; el++) {
		printf ("print list[%u]\n", el);
		if (el < list->size) {
			fprintf (IR_TOKENS, FILL_CELL2, el, typeColor[el], types[el], list->cells[el].data.lexem, "INCL", el, el);
		}
		else {
			fprintf (IR_TOKENS, FILL_CELL2, el, typeColor[el], types[el], "include", "INCL", el, el);
		}
	}
	fprintf (IR_TOKENS, "\t# connection of these nodes\n");
	for (unsigned el = 0; el < list->capacity; el++) {
		if (list->cells[el].next >= 0) {
			fprintf (IR_TOKENS, "\tL%u:\"n%u\" -> L%d[color=\"%s\"];\n", el, el, list->cells[el].next, "white");
		}
		if (list->cells[el].prev >= 0) {
			fprintf (IR_TOKENS, "\tL%u:\"p%u\" -> L%d[color=\"%s\" arrowhead = box];\n", el, el, list->cells[el].prev, "#32383F");
		}
	}

	fprintf (IR_TOKENS, "}\n");

	fclose (IR_TOKENS);
	system ("dot viz/ir-tokens.dot -T jpg -o viz/ir-tokens.jpg");
	return;
}
