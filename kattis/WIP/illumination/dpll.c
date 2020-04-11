#include "dpll.h"

#include <stdlib.h>

int dpll(const signed int* f, signed int* r) {
  int L, C;
  L = f[0], C = f[1];
  if (L < 0 || C < 0) {
    return -1;
  }
  if (C == 0) {  // No clauses, trivially satisfied.
    for (int i = 0; i < L; i++) {
      r[i] = 0;
    }
    return 1;
  }
  if (L == 0) {  // No literals but at least one (empty) clause.
    return 0;
  }
  if (f == NULL || r == NULL) {  // Test function arguments.
    return -1;
  }
  signed int* clauses[C];
  if (getClauses(f, clauses)) {  // If getClauses doesn't return 0, it failed.
    return -2;
  }
}

int sort(signed int** clauses, int C, int A) {
  if (C < 0) {
    return -1;
  }
  int remaining[A + 1][2];
  for (int i = 0; i < A; i++) {
    remaining[i + 1][0] = remaining[i + 1][1] = 1;
  }
  int newAtoms[A * 2];
  int newA = 0;
  // Find single-literal clauses
  for (int i = 0; i < C && newA < A; i++) {
    if (*clauses[i] == 1) {
      if (clauses[i][1] > 0 && remaining[clauses[i][1]][0]) {
        remaining[clauses[i][1]][0] = 0;
        newAtoms[newA++] = clauses[i][0];
      } else if (clauses[i][1] < 0 && remaining[-clauses[i][1]][1]) {
        remaining[-clauses[i][1]][1] = 0;
      }
      newAtoms[newA++] = clauses[i][1];
    }
  }
  return 0;
}

int getClauses(const signed int* f, signed int** t) {
  if (f == NULL || t == NULL) {
    return -1;
  }
  int C = f[0];
  while (C > 0) {
    *(t++) = f;  // Write the current beginning of a clause into t and increment
                 // the pointer.
    f += *f;     // Move f right by the length of the clause.
    C--;         // Decrement clause count.
  }
  return 0;
}

void frmcpy(signed int* t, const signed int* f) {
  size_t l = 0;
  int C = f[1];
  signed int* p = &f[2];
  while (C > 0) {
    l += *p;
    p += *p;
    C--;
  }
  memcpy(t, f, l);
}
