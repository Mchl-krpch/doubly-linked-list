#ifndef _LIST_H_
#define _LIST_H_

#include <stdio.h>

#define INCREASE_COEF 2
#define FILL_CELL() 	\
"L0[shape=none label = <\n\
\t<table cellborder=\"0\" cellspacing=\"18\" bgcolor=\"#0D1117\" border=\"1\" color=\"#79C0FF\">\n\
\t\t<tr>\n\
\t\t\t<td colspan=\"2\" width=\"80px\" height=\"35px\" bgcolor=\"#000697\">\
<font color=\"white\">TOKEN #133 | type:</font></td>\n\
\t\t</tr>\n\
\t\t<tr>\n\
\t\t\t<td align=\"left\" colspan=\"2\"><font point-size=\"23\" color=\"#C9D1D9\">Token:</font></td>\n\
\t\t</tr>\n\
\t\t<tr>\n\
\t\t\t<td align=\"left\" colspan=\"2\"><font point-size=\"23\" color=\"#C9D1D9\">Translate:</font><br align=\"left\"/></td>\n\
\t\t</tr>\n\
\t\t<tr>\n\
\t\t\t<td bgcolor=\"#000697\" width=\"80px\" border=\"1\" color=\"#30363D\">\
<font color =\"#79C0FF\">Previous<br align=\"left\"/>cell<br align=\"left\"/>\
</font></td>\n\
\t\t\t<td bgcolor=\"#000697\" width=\"80px\" border=\"1\" color=\"#30363D\">\
<font color =\"#79C0FF\">next<br/>cell \
</font></td>\n\
\t\t</tr>\n	\
</table>>];\n"

// - - - - - - - - - - -
// lexem 
enum class lexemType{
	nil = 0,
	num_c,
	num_d,
	num_f,
	num_lg,
	opt,
	hashKey,
};

enum class variability {
	none,
	rvalue,
	lvalue,
};

struct preferences {
	lexemType type = {};
	variability varClass = variability::none;
};
// - - - - - - - - - - -
// #operator code
enum class Operator {
	nil = 0,
	plus,
	mul,
};

union tokenData {
	void *nil;

	char   num_c;
	int    num_d;
	float  num_f;
	double num_lg;

	Operator op;
	char *lexem = nullptr;
};
// - - - - - - - - - - -
struct Token {
	int index = 0;
	// #ptrs to another cells
	int prev = 0;
	int next = 0;

	// #node content
	tokenData data = {};
	preferences pref = {};
	char *test = nullptr;
};

struct list {
	size_t size = 0;
	size_t capacity = 0;
	Token *cells = nullptr;

	int head = 0;
	int tail = 0;
	int free = 0;
};

struct list *newList (unsigned capacity);
void drowCell ();
void drowList (list *list);
void printList (list *list);
int FindEmpty (list *list);
void ChangeCapacity (list *list, unsigned capacity);
void listDtor (list *list);
void InsertAfter (int index, list *list, int value);

#endif