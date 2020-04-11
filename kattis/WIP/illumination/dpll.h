#ifndef H_DPLL
#define H_DPLL

void frmcpy(signed int* t, const signed int* f);

// dpll finds a valuation r for the form f where r -> f;
// a form is a string of signed integers where the value indicates
// the label of the literal and the sign stands for the negation value.
// encoding: number of literals L | C | C * [X | X * (-){1..L}] where
// - L is the number of possible literals
// - C is the number of clauses
// - X is the number of literals in a particular clause
// - (-){1..L} is a literal with an atom from [1..L]
int dpll(const signed int* f, signed int* r);

// getClauses writes all the pointers to beginnings of clauses in f to t.
int getClauses(const signed int* f, signed int** t);
#endif