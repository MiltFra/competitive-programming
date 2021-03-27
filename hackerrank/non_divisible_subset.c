#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define u32_t unsigned int
#define u64_t unsigned long int
#define i32_t int
#define i64_t long int

#define int_t  i64_t
#define uint_t u64_t

void next_signed(int_t *number) {
  register int_t c;
  *number = 0;
  do {
    c = getchar();
  } while (c == '\n' || c == '\r' || c == ' ');

  char negative = c == '-';

  for (; (c > 47 && c < 58); c = getchar())
    *number = *number * 10 + c - 48;
  if (negative) {
    *number *= -1;
  }
}

void next_unsigned(uint_t *number) {
  register int_t c;
  *number = 0;
  do {
    c = getchar();
  } while (c == '\n' || c == '\r' || c == ' ');
  for (; (c > 47 && c < 58); c = getchar())
    *number = *number * 10 + c - 48;
}

void next_lower_letter(char *c) {
  do {
    *c = getchar();
  } while (*c < 97 || *c > 122);
}

void next_upper_letter(char *c) {
  do {
    *c = getchar();
  } while (*c < 65 || *c > 90);
}

int main(void) {
  uint_t n, k;
  next_unsigned(&n);
  next_unsigned(&k);
  uint_t mods[k];
  for (uint_t i = 0; i < k; i++) {
    mods[i] = 0;
  }
  uint_t input[n];
  for (uint_t i = 0; i < n; i++) {
    next_unsigned(input + i);
    mods[input[i] % k]++;
    fprintf(stderr, "%lu\n", input[i] % k);
  }
  register uint_t i, len_out = 0, lower, upper;
  for (i = 1; i < (k + 1) / 2; i++) {  // we can do integer division because we
    lower = mods[i];
    upper = mods[k - i];
    if (lower > upper) {
      len_out += lower;
    } else {
      len_out += upper;
    }
  }
  if (mods[0]) {  // We can always afford to have one element
    len_out++;    // that's already 0 mod k
  }
  if (!(k % 2) && mods[k / 2]) {
    len_out++;
  }
  printf("%lu\n", len_out);
}