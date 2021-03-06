#ifndef _LIST_H_
#define _LIST_H_

#include <stdio.h>

#define INCREASE_COEF 2

#define FILL_CELL2 \
"\tL%u [shape=none label = <<table cellborder=\"0\" cellspacing=\"18\" bgcolor=\"#0D1117\" border=\"10\" color=\"%s\">\n\
\t\t<tr><td colspan=\"2\" width=\"80px\" height=\"35px\" color=\"#32383F\" border=\"1\">\t\t<font color=\"white\">TOKEN #133     |    type: %s</font></td></tr>\n\
\t\t<tr><td align=\"left\" colspan=\"2\">\t\t<font point-size=\"23\" color=\"#C9D1D9\">Token:      <b>%s</b></font></td></tr>\n\
\t\t<tr><td align=\"left\" colspan=\"2\">\t\t<font point-size=\"23\" color=\"#C9D1D9\">Translate:  <b>%s</b></font><br align=\"left\"/></td></tr>\n\
\t\t<tr><td PORT=\"p%u\" width=\"80px\" border=\"1\" color=\"#32383F\"><font color =\"white\">Previous<br align=\"left\"/>cell<br align=\"left\"/></font></td>\n\
\t\t\t\t<td PORT=\"n%u\" width=\"80px\" border=\"1\" color=\"#32383F\">\t\t<font color =\"white\">next<br/>cell</font></td></tr>\n\
\t\t\t\t</table>>];\n\n\n"

const char typeColor[][100] {
	"lightslategrey",
	"red4",
	"orangered4",
	"sienna2",
	"peru",
	"#000697",
	"skyblue"
};

const char types[][100] {
	"NONE",
	"CHAR",
	"INT",
	"FLOAT",
	"DOUBLE",
	"OPERATOR",
	"VARIABLE"
};

// - - - - - - - - - - -
// lexem 
enum class lexemType {
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
	unsigned size = 0;
	unsigned capacity = 0;
	Token *cells = nullptr;

	int head = 0;
	int tail = 0;
	int free = 0;
};

struct list *newList (unsigned capacity);
void ChangeCapacity (list *list, unsigned capacity);
void listDtor (list *list);
int FindEmpty (list *list);
void InsertAfter (unsigned index, list *list, int value);
void InsertAfter_str (unsigned index, list *list, const char *lexem);
void removeElem (unsigned el, list *list);
void printList (list *list);
void printList_str (list *list);

void drowList (list *list);

#endif