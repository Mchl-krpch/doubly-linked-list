#include <stdio.h>
#include <stdlib.h>

#include "doubly-linked-list.h"

int main () {
	list *Tokens = newList (25);

	drowCell ();
	return 0;
}
// ################################################
struct list *newList (unsigned capacity) {
	struct list *List = (list *)calloc (1, sizeof (list));
	List->cells = (Token *)calloc (capacity, sizeof (Token));

	for (int el = 0; el < capacity; el++) {
		List->cells[el].data = {.lexem = (char *)calloc (100, sizeof (char))};
	}
	return List;
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