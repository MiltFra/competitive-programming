#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define u32_t unsigned int
#define u64_t unsigned long int
#define i32_t int
#define i64_t long int

#define int_t i32_t
#define uint_t u32_t

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
  uint_t T, K;
  next_unsigned(&T);
  while (T--) {
    next_unsigned(&K);
    putchar('O');
    for (uint_t i = 1; i < K; i++) {
      if (!(i & 0x7)) {
        putchar('\n');
      }
      putchar('.');
    }
    for (uint_t i = K; i < 64; i++) {
      if (!(i & 0x7)) {
        putchar('\n');
      }
      putchar('X');
    }
    putchar('\n');
    if (T) {
      putchar('\n');
    }
  }
}